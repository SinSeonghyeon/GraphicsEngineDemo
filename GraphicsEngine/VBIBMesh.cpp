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
	//버텍스 버퍼와 인덱스 버퍼 셋팅..

	if (_vertex.size() <= 0) return;

	ID3D11Device* _d3dDevice = DXEngine::GetInstance()->GetD3dDevice();


	D3D11_BUFFER_DESC vbd; //버텍스 버퍼 구조체
	vbd.Usage = D3D11_USAGE_IMMUTABLE; // 사용할때마다 책 찾아보기
	vbd.ByteWidth = sizeof(Vertex) * _vertex.size(); // 사이즈
	vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;  // 버텍스 버퍼 플래그 설정
	vbd.CPUAccessFlags = 0;
	vbd.MiscFlags = 0;
	vbd.StructureByteStride = 0;

	HRESULT hr;
	D3D11_SUBRESOURCE_DATA vinitData; //버텍스
	vinitData.pSysMem = _vertex.data(); //버텍스 정보를 가지고 있는 배열의 포인터
	HR(_d3dDevice->CreateBuffer(&vbd, &vinitData, &m_VB));


	D3D11_BUFFER_DESC ibd; //인덱스(색인) 버퍼 구조체
	ibd.Usage = D3D11_USAGE_IMMUTABLE; // 사용할때마다 책 찾아보기
	ibd.ByteWidth = sizeof(int) * _indices.size() * 3;  // 사이즈
	ibd.BindFlags = D3D11_BIND_INDEX_BUFFER; // 인덱스 버퍼 플래그 설정
	ibd.CPUAccessFlags = 0;
	ibd.MiscFlags = 0;
	ibd.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA iinitData; //인덱스
	iinitData.pSysMem = _indices.data(); //인덱스 정보를 가지고 있는 배열의 포인터
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
	// 입력 배치 객체 셋팅
	_d3dImmediateContext->IASetInputLayout(m_InputLayout); // 입력 배치/ 정점 구조체를 정의하고 direct3d 에게 알려주는 함수.
	_d3dImmediateContext->IASetPrimitiveTopology(m_Topology); //기본 도형의 위상 구조를 정의한 열거형 대부분 삼각형을 사용.
	// 인덱스버퍼와 버텍스버퍼 셋팅
	UINT stride = sizeof(Vertex);
	UINT offset = 0;
	_d3dImmediateContext->IASetVertexBuffers(0, 1, &m_VB, &stride, &offset); //버텍스 버퍼
	_d3dImmediateContext->IASetIndexBuffer(m_IB, DXGI_FORMAT_R32_UINT, 0); //인덱스 버퍼

	// 너가 임보 좀 하고있어라.
	Effects::WireFX->SetColor(m_Color);

	/// WVP TM등을 셋팅
	// Set constants

	XMMATRIX world = m_MeshObject->GetWorldTM(); // 월트 메트릭스
	XMMATRIX _View = DXEngine::GetInstance()->GetCameraView(); // 카메라
	XMMATRIX _Proj = DXEngine::GetInstance()->GetCameraProj(); // 카메라

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
	// 테크닉은... 무엇인가.. todo :
	D3DX11_TECHNIQUE_DESC techDesc;

	m_NowTech->GetDesc(&techDesc);
	// 랜더패스는... 무엇인가.. todo :

	//DXEngine::GetInstance()->ResetDepthStencilState();
	for (UINT p = 0; p < techDesc.Passes; ++p)
	{
		DXEngine::GetInstance()->GetDepthStencil()->OnDepthStencil(p);
		DXEngine::GetInstance()->GetRenderTarget()->SetRenderTargetView(p);
		m_NowTech->GetPassByIndex(p)->Apply(0, _d3dImmediateContext);

		// 36개의 인덱스로 상자를 그린다.
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
