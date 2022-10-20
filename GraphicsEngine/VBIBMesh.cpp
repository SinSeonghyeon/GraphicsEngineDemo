#include "pch.h"
#include "VBIBMesh.h"

VBIBMesh::VBIBMesh(Mesh* _MeshObject) : IMeshComponent(_MeshObject), m_Fx(nullptr)
, m_IB(nullptr), m_IndexSize(), m_InputLayout(nullptr), m_NowTech(nullptr), m_OriginalTech(nullptr)
, m_VB(nullptr), m_Color(1.0f, 1.0f, 1.0f, 1.0f)
{
	m_Topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
}

VBIBMesh::~VBIBMesh()
{
	ReleaseCOM(m_VB);
	ReleaseCOM(m_IB);
}

void VBIBMesh::BuildGeometryBuffers(vector<Vertex>& _vertex, vector<index3>& _indices)
{
	//���ؽ� ���ۿ� �ε��� ���� ����..

	if (_vertex.size() <= 0) return;

	ID3D11Device* _d3dDevice = DXEngine::GetInstance()->GetD3dDevice();


	D3D11_BUFFER_DESC vbd; //���ؽ� ���� ����ü
	vbd.Usage = D3D11_USAGE_IMMUTABLE; // ����Ҷ����� å ã�ƺ���
	vbd.ByteWidth = sizeof(Vertex) * _vertex.size(); // ������
	vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;  // ���ؽ� ���� �÷��� ����
	vbd.CPUAccessFlags = 0;
	vbd.MiscFlags = 0;
	vbd.StructureByteStride = 0;

	HRESULT hr;
	D3D11_SUBRESOURCE_DATA vinitData; //���ؽ�
	vinitData.pSysMem = _vertex.data(); //���ؽ� ������ ������ �ִ� �迭�� ������
	HR(_d3dDevice->CreateBuffer(&vbd, &vinitData, &m_VB));


	D3D11_BUFFER_DESC ibd; //�ε���(����) ���� ����ü
	ibd.Usage = D3D11_USAGE_IMMUTABLE; // ����Ҷ����� å ã�ƺ���
	ibd.ByteWidth = sizeof(int) * _indices.size() * 3;  // ������
	ibd.BindFlags = D3D11_BIND_INDEX_BUFFER; // �ε��� ���� �÷��� ����
	ibd.CPUAccessFlags = 0;
	ibd.MiscFlags = 0;
	ibd.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA iinitData; //�ε���
	iinitData.pSysMem = _indices.data(); //�ε��� ������ ������ �ִ� �迭�� ������
	HR(_d3dDevice->CreateBuffer(&ibd, &iinitData, &m_IB));

	m_IndexSize = _indices.size() * 3;
	_vertex.clear();
	_indices.clear();


}

void VBIBMesh::BuildVertexLayout()
{
	if (m_IndexSize <= 0) return;

	Effect* _Light = dynamic_cast<Shader*>(m_Fx);
	if (_Light)
	{
		m_InputLayout = InputLayout::m_Light;
		return;
	}
	Effect* _Wire = dynamic_cast<WireShader*>(m_Fx);
	if (_Wire)
	{
		m_InputLayout = InputLayout::m_Wire;
		m_Topology = D3D11_PRIMITIVE_TOPOLOGY_LINELIST;
		return;
	}
	Effect* _Sky = dynamic_cast<SkyShader*>(m_Fx);
	if (_Sky)
	{
		m_InputLayout = InputLayout::m_Sky;
	}

}

void VBIBMesh::SetConstants()
{

	if (!m_InputLayout) return;


	ID3D11DeviceContext* _d3dImmediateContext = DXEngine::GetInstance()->Getd3dImmediateContext();
	// �Է� ��ġ ��ü ����
	_d3dImmediateContext->IASetInputLayout(m_InputLayout); // �Է� ��ġ/ ���� ����ü�� �����ϰ� direct3d ���� �˷��ִ� �Լ�.
	_d3dImmediateContext->IASetPrimitiveTopology(m_Topology); //�⺻ ������ ���� ������ ������ ������ ��κ� �ﰢ���� ���.
	// �ε������ۿ� ���ؽ����� ����
	UINT stride = sizeof(Vertex);
	UINT offset = 0;
	_d3dImmediateContext->IASetVertexBuffers(0, 1, &m_VB, &stride, &offset); //���ؽ� ����
	_d3dImmediateContext->IASetIndexBuffer(m_IB, DXGI_FORMAT_R32_UINT, 0); //�ε��� ����

	// �ʰ� �Ӻ� �� �ϰ��־��.
	Effects::WireFX->SetColor(m_Color);

	/// WVP TM���� ����
	// Set constants

	XMMATRIX world = m_MeshObject->GetWorldTM(); // ��Ʈ ��Ʈ����
	XMMATRIX _View = DXEngine::GetInstance()->GetCameraView(); // ī�޶�
	XMMATRIX _Proj = DXEngine::GetInstance()->GetCameraProj(); // ī�޶�

	m_Fx->WorldViewProjUpdate(world, _View, _Proj);
	XMMATRIX _Shadow = world * DXEngine::GetInstance()->GetCamera()->GetShadowView() * DXEngine::GetInstance()->GetCamera()->GetShadowProj();
	Effects::LightFX->SetLightWorldViewProj(_Shadow); //test
}

void VBIBMesh::SetColor(XMFLOAT4 _Color)
{
	m_Color = _Color;
}

void VBIBMesh::SetTopology(D3D11_PRIMITIVE_TOPOLOGY _Topology)
{
	m_Topology = _Topology;
}

void VBIBMesh::Darw()
{
	if (!m_InputLayout) return;

	SetConstants();

	ID3D11DeviceContext* _d3dImmediateContext = DXEngine::GetInstance()->Getd3dImmediateContext();
	// ��ũ����... �����ΰ�.. todo :
	D3DX11_TECHNIQUE_DESC techDesc;

	m_NowTech->GetDesc(&techDesc);
	// �����н���... �����ΰ�.. todo :

	//DXEngine::GetInstance()->ResetDepthStencilState();
	for (UINT p = 0; p < techDesc.Passes; ++p)
	{
		DXEngine::GetInstance()->GetDepthStencil()->OnDepthStencil(p);
		DXEngine::GetInstance()->GetRenderTarget()->SetRenderTargetView(p);
		m_NowTech->GetPassByIndex(p)->Apply(0, _d3dImmediateContext);

		// 36���� �ε����� ���ڸ� �׸���.
		_d3dImmediateContext->DrawIndexed(m_IndexSize, 0, 0);
	}

}

void VBIBMesh::Init(vector<Vertex>& _vertex, vector<index3>& _indices, ID3DX11EffectTechnique* _Tech, Effect* _Shader)
{
	m_Fx = _Shader;
	m_OriginalTech = _Tech;
	m_NowTech = m_OriginalTech;

	BuildGeometryBuffers(_vertex, _indices);
	BuildVertexLayout();
}

void VBIBMesh::WakeMesh()
{
}

void VBIBMesh::SleepMesh()
{
}
