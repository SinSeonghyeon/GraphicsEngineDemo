#pragma once
class ID3DX11EffectTechnique;
class Effect;

/// <summary>
/// 얘는 모든 컴포넌트중 마지막으로 그려야 됨.
/// </summary>
class VBIBMesh : public IMeshComponent
{
public:
	VBIBMesh(Mesh* _MeshObject);
	~VBIBMesh();

private:
	D3D11_PRIMITIVE_TOPOLOGY m_Topology; // 삼각형으로 고정?

	ID3D11Buffer* m_VB; // 버텍스 버퍼
	ID3D11Buffer* m_IB; // 인덱스(색인) 버퍼
	Effect* m_Fx;

	ID3DX11EffectTechnique* m_OriginalTech;
	ID3DX11EffectTechnique* m_NowTech;

	ID3D11InputLayout* m_InputLayout; //211p 입력 배치 객체 . 정점 구조체가의 각 성분이 어떤 용도인지 DX3D에게 알려주기 위함 /신성현
	
	XMFLOAT4 m_Color;

	int m_IndexSize;

	void BuildGeometryBuffers(vector<Vertex>& _vertex, vector<index3>& _indices); //버텍스 버퍼와 인덱스 버퍼 초기화
	void BuildVertexLayout(); // 정점 구조체를 Direct3D에게 알려줌. 입력 배치 생성
	void SetConstants();

public:	
	void SetColor(XMFLOAT4 _Color);
	void SetTopology(D3D11_PRIMITIVE_TOPOLOGY _Topology);
	virtual void Darw() override;
	void Init(vector<Vertex>& _vertex, vector<index3>& _indices, ID3DX11EffectTechnique* _Tech, Effect* _Shader);
	virtual void WakeMesh() override;
	virtual void SleepMesh() override;
};

