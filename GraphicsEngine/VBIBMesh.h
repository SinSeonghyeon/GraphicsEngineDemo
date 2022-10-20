#pragma once
class ID3DX11EffectTechnique;
class Effect;

/// <summary>
/// ��� ��� ������Ʈ�� ���������� �׷��� ��.
/// </summary>
class VBIBMesh : public IMeshComponent
{
public:
	VBIBMesh(Mesh* _MeshObject);
	~VBIBMesh();

private:
	D3D11_PRIMITIVE_TOPOLOGY m_Topology; // �ﰢ������ ����?

	ID3D11Buffer* m_VB; // ���ؽ� ����
	ID3D11Buffer* m_IB; // �ε���(����) ����
	Effect* m_Fx;

	ID3DX11EffectTechnique* m_OriginalTech;
	ID3DX11EffectTechnique* m_NowTech;

	ID3D11InputLayout* m_InputLayout; //211p �Է� ��ġ ��ü . ���� ����ü���� �� ������ � �뵵���� DX3D���� �˷��ֱ� ���� /�ż���
	
	XMFLOAT4 m_Color;

	int m_IndexSize;

	void BuildGeometryBuffers(vector<Vertex>& _vertex, vector<index3>& _indices); //���ؽ� ���ۿ� �ε��� ���� �ʱ�ȭ
	void BuildVertexLayout(); // ���� ����ü�� Direct3D���� �˷���. �Է� ��ġ ����
	void SetConstants();

public:	
	void SetColor(XMFLOAT4 _Color);
	void SetTopology(D3D11_PRIMITIVE_TOPOLOGY _Topology);
	virtual void Darw() override;
	void Init(vector<Vertex>& _vertex, vector<index3>& _indices, ID3DX11EffectTechnique* _Tech, Effect* _Shader);
	virtual void WakeMesh() override;
	virtual void SleepMesh() override;
};

