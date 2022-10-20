#pragma once


struct BulidInfo
{
	string m_Name;
	string m_Path;
	ID3DX11EffectTechnique* m_Tech;
	Shader* m_Shader;
};

class Bulider
{
public:
	Bulider();
	~Bulider() = default;
public:
	Mesh* CreateMesh(BulidInfo& _BulidInfo);
	IMesh* CreateGizmoMesh(GizmoInfo& _Info);

	void ChangeGeometry(GeometryGenerator::MeshData* _MeshData, vector<Vertex>& _vertices, vector<index3>& _Indices);
private:
	void CreateMeshChild(Mesh* _TopParent, MeshData* _MeshData, BulidInfo& _BulidInfo);
	void CreateTexture(Mesh* _Mesh, string Path);

	Mesh* SphereGizmoCreate(float _Radius);
	Mesh* BoxGizmoCreate(XMFLOAT3 _Pos[8]);
	Mesh* LineGizmoCreate(XMFLOAT3 _Pos[2]);

public:
	// Ư������? ��׵� ������ �����?
	void CreateGridMesh();
	// Axis�� �׳� ����� �������� �� 3�� ��������~
	void CreateCubeMapMesh();
	void CreateSolidBoxMesh();
	void CreateSolidSphereMesh();
};
