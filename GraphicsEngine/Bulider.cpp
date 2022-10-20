#include "pch.h"
#include "Bulider.h"
#include "CASEParser.h"
#include "DDSTextureLoader.h"

#include "..\Loader\Loader_Interface.h"


Bulider::Bulider()
{
}

Mesh* Bulider::CreateMesh(BulidInfo& _BulidInfo)
{
	Mesh* _Result = new Mesh();


	char* writable = new char[_BulidInfo.m_Path.size() + 1];
	std::copy(_BulidInfo.m_Path.begin(), _BulidInfo.m_Path.end(), writable);
	writable[_BulidInfo.m_Path.size()] = '\0';

	//MeshData* _MeshData = DXEngine::GetInstance()->GetResourceManager()->m_ASEParser->Load(writable);
	MeshData* _MeshData = DXEngine::GetInstance()->GetResourceManager()->m_ASEParser->Load(writable);
	
	wstring _test;
	_test.assign(_BulidInfo.m_Path.begin() , _BulidInfo.m_Path.end());
	//ASEParsingData _data = ->LoadASE(_test);
	// 파서가 메쉬 데이터를 읽어옴.
	delete[] writable;


	// 읽어온 데이터 따라 다르게 컴포넌트 부착.
	_Result->SetRasterizerState(RasterizerState::m_SolidRS);
	CreateTexture(_Result, _MeshData->m_Path);

	_Result->m_BoneNameList = _MeshData->m_BoneNameList;
	_Result->m_MinPos = _MeshData->m_MinPos;
	_Result->m_MaxPos = _MeshData->m_MaxPos;

	_Result->SetMaterial(_MeshData->m_Mtl);
	_Result->AddMeshComponent<VBIBMesh>()->Init(_MeshData->m_vertices, _MeshData->m_indices, _BulidInfo.m_Tech, _BulidInfo.m_Shader);
	CreateMeshChild(_Result, _MeshData, _BulidInfo);


	delete _MeshData;


	return _Result;
}

void Bulider::CreateMeshChild(Mesh* _TopParent, MeshData* _MeshData, BulidInfo& _BulidInfo)
{

	for (auto& iter : _MeshData->m_Childrens)
	{
		Mesh* _Child = new Mesh();

		_Child->SetName(iter->m_Name);
		_Child->SetParent(_TopParent->FindChildren(iter->m_Parent->m_Name));
		_Child->SetMaterial(_TopParent->m_Mtl);

		_Child->m_AniKeys = iter->m_AniKeys;
		if (_TopParent->m_BoneNameList.size() > 0)
			_Child->AddMeshComponent<SkinningMesh>();


		_Child->SetRasterizerState(RasterizerState::m_SolidRS);

		_Child->m_NodeWorldTM = iter->m_WorldTM;
		_Child->m_NodeLocalTM = iter->m_LocalMT;




		_Child->AddMeshComponent<VBIBMesh>()->Init(iter->m_vertices, iter->m_indices, _BulidInfo.m_Tech, _BulidInfo.m_Shader);

		CreateMeshChild(_TopParent, iter, _BulidInfo);
	}

}

void Bulider::CreateTexture(Mesh* _Mesh, string Path)
{
	ID3D11Resource* texResource = nullptr;
	ID3D11ShaderResourceView* _DiffuseMapSRV;
	ID3D11ShaderResourceView* _NormalMapSRV;


	string _Path = "Resource/Mesh/";
	_Path += Path;
	_Path += ".dds";
	wstring _str;
	_str.assign(_Path.begin(), _Path.end());

	HRESULT hr;
	hr = CreateDDSTextureFromFile(DXEngine::GetInstance()->GetD3dDevice(), _str.c_str(), &texResource, &_DiffuseMapSRV);
	ReleaseCOM(texResource)	// view saves reference
		ReleaseCOM(_DiffuseMapSRV)	// view saves reference
		if (FAILED(hr)) return;
	_Mesh->AddMeshComponent<TextureMesh>()->Init(_Path);



	_str.clear();
	_Path = "Resource/Mesh/";
	_Path += Path;
	_Path += "_n.dds";
	_str;
	_str.assign(_Path.begin(), _Path.end());
	hr = CreateDDSTextureFromFile(DXEngine::GetInstance()->GetD3dDevice(), _str.c_str(), &texResource, &_NormalMapSRV);
	ReleaseCOM(texResource)	// view saves reference
		ReleaseCOM(_NormalMapSRV)	// view saves reference
		if (FAILED(hr)) return;
	_Mesh->AddMeshComponent<NormalMesh>()->Init(_Path);

}

IMesh* Bulider::CreateGizmoMesh(GizmoInfo& _Info)
{
	Mesh* _Result = nullptr;
	switch (_Info.m_Type)
	{
	case Shphere:
		_Result = SphereGizmoCreate(_Info.m_Radius);
		break;
	case Box:
		_Result = BoxGizmoCreate(_Info.m_BoxPos);
		break;
	case Line:
		_Result = LineGizmoCreate(_Info.m_LinePos);
		break;
	default:
		break;
	}
	return _Result;
}

Mesh* Bulider::SphereGizmoCreate(float _Radius)
{
	Mesh* _Result = new Mesh();
	//버텍스 버퍼와 인덱스 버퍼 셋팅..

	GeometryGenerator::MeshData sphere;
	GeometryGenerator geoGen;
	geoGen.CreateSphere(_Radius, 30, 30, sphere);

	std::vector<Vertex> vertices(sphere.Vertices.size());
	std::vector<index3> indices(sphere.Indices.size() / 3);

	ChangeGeometry(&sphere, vertices, indices);

	VBIBMesh* _Temp = _Result->AddMeshComponent<VBIBMesh>();
	_Temp->Init(vertices, indices, Effects::WireFX->m_WireTech, Effects::WireFX);
	_Temp->SetTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	_Result->SetRasterizerState(RasterizerState::m_WireframeRS);
	return _Result;
}

Mesh* Bulider::BoxGizmoCreate(XMFLOAT3 _Pos[8])
{
	Mesh* _Result = new Mesh();
	//버텍스 버퍼와 인덱스 버퍼 셋팅..

	std::vector<Vertex> vertices(8);

	for (int i = 0; i < 8; i++)
	{
		vertices[i].Pos = _Pos[i];
	}

	std::vector<index3> indices(12);

	indices[0] = index3(3, 1, 0);
	indices[1] = index3(3, 2, 1);

	indices[2] = index3(2, 7, 6);
	indices[3] = index3(2, 3, 7);

	indices[4] = index3(3, 4, 7);
	indices[5] = index3(3, 0, 4);

	indices[6] = index3(2, 6, 5);
	indices[7] = index3(1, 2, 5);

	indices[8] = index3(6, 7, 5);
	indices[9] = index3(7, 4, 5);

	indices[10] = index3(1, 5, 4);
	indices[11] = index3(0, 1, 4);


	VBIBMesh* _Temp = _Result->AddMeshComponent<VBIBMesh>();
	_Temp->Init(vertices, indices, Effects::WireFX->m_WireTech, Effects::WireFX);
	_Temp->SetTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	_Result->SetRasterizerState(RasterizerState::m_WireframeRS);
	return _Result;
}

Mesh* Bulider::LineGizmoCreate(XMFLOAT3 _Pos[2])
{
	Mesh* _Result = new Mesh();
	//버텍스 버퍼와 인덱스 버퍼 셋팅..

	std::vector<Vertex> vertices(2);

	for (int i = 0; i < 2; i++)
	{
		vertices[i].Pos = _Pos[i];
	}

	std::vector<index3> indices(1);

	indices[0] = index3(0, 1, 0);

	VBIBMesh* _Temp = _Result->AddMeshComponent<VBIBMesh>();
	_Temp->Init(vertices, indices, Effects::WireFX->m_WireTech, Effects::WireFX);
	_Temp->SetTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
	_Result->SetRasterizerState(RasterizerState::m_WireframeRS);
	return _Result;
}

void Bulider::ChangeGeometry(GeometryGenerator::MeshData* _MeshData, vector<Vertex>& _vertices, vector<index3>& _Indices)
{
	for (size_t i = 0; i < _MeshData->Vertices.size(); ++i)
	{
		_vertices[i].Pos = _MeshData->Vertices[i].Position;
		_vertices[i].Nomal = _MeshData->Vertices[i].Normal;
	}

	for (unsigned int i = 0; i < _Indices.size(); i++)
	{
		_Indices[i].m_Index[0] = _MeshData->Indices[i * 3];
		_Indices[i].m_Index[1] = _MeshData->Indices[i * 3 + 1];
		_Indices[i].m_Index[2] = _MeshData->Indices[i * 3 + 2];
	}

}

void Bulider::CreateGridMesh()
{
	ID3DX11EffectTechnique* _Tech = Effects::WireFX->m_WireTech;
	Mesh* _Grid = new Mesh();

	_Grid->SetName("Grid");
	DXEngine::GetInstance()->GetResourceManager()->GetMeshs().insert(make_pair("Grid", _Grid));

	//버텍스 버퍼와 인덱스 버퍼 셋팅..

	ID3D11Device* _d3dDevice = DXEngine::GetInstance()->GetD3dDevice();

	const int _Size = 120;
	// 버텍스 버퍼 인덱스 버퍼 세팅
	vector<Vertex> vertices;
	vertices.resize(_Size);
	for (int i = 0; i < _Size / 4; i++)
	{
		vertices[i].Pos = XMFLOAT3(5.0f * i, 0, 0);
	}
	for (int i = 0; i < _Size / 4; i++)
	{
		vertices[i + _Size / 4].Pos = XMFLOAT3(5.0f * i, 0, 5.0f * (_Size / 4 - 1));
	}

	for (int i = 0; i < _Size / 4; i++)
	{
		vertices[i + _Size / 2].Pos = XMFLOAT3(0, 0, 5.0f * i);
	}
	for (int i = 0; i < _Size / 4; i++)
	{
		vertices[i + _Size / 4 * 3].Pos = XMFLOAT3(5.0f * (_Size / 4 - 1), 0, 5.0f * i);
	}

	for (int i = 0; i < _Size; i++)
	{
		vertices[i].Pos.x -= 5.0f * (_Size / 8 - 1);
		vertices[i].Pos.z -= 5.0f * (_Size / 8 - 1);
	}


	UINT indices[_Size];

	for (int i = 0; i < _Size / 2; i++, i++)
	{
		indices[i] = i / 2;
		indices[i + 1] = i / 2 + _Size / 4;
	}
	for (int i = 0; i < _Size / 2; i++, i++)
	{
		indices[i + _Size / 2] = i / 2 + _Size / 2;
		indices[i + _Size / 2 + 1] = i / 2 + _Size / 4 * 3;
	}

	vector<index3> _Temp;
	_Temp.resize(_Size / 3);
	for (unsigned int i = 0; i < _Temp.size(); i++)
	{
		_Temp[i].m_Index[0] = indices[i * 3];
		_Temp[i].m_Index[1] = indices[i * 3 + 1];
		_Temp[i].m_Index[2] = indices[i * 3 + 2];
	}
	_Grid->AddMeshComponent<VBIBMesh>()->Init(vertices, _Temp, _Tech, Effects::WireFX);


}

void Bulider::CreateCubeMapMesh()
{
	Mesh* _Result = new Mesh();

	GeometryGenerator::MeshData sphere;
	GeometryGenerator geoGen;
	geoGen.CreateSphere(5000.0f, 30, 30, sphere);

	std::vector<Vertex> vertices(sphere.Vertices.size());
	std::vector<index3> indices(sphere.Indices.size() / 3);

	ChangeGeometry(&sphere, vertices, indices);
	_Result->AddMeshComponent<CubeMapMesh>()->Init("Resource/Mesh/sunsetcube1024.dds");

	VBIBMesh* _Temp = _Result->AddMeshComponent<VBIBMesh>();
	_Temp->Init(vertices, indices, Effects::SkyFX->m_SkyTech, Effects::SkyFX);

	DXEngine::GetInstance()->GetResourceManager()->GetMeshs().insert(make_pair("SkyBox", _Result));

}

void Bulider::CreateSolidBoxMesh()
{
	Mesh* _Result = new Mesh();
	//버텍스 버퍼와 인덱스 버퍼 셋팅..

	GeometryGenerator::MeshData Box;
	GeometryGenerator geoGen;
	geoGen.CreateBox(1.0f, 1.0f, 1.0f, Box);


	_Result->SetName("Box");
	DXEngine::GetInstance()->GetResourceManager()->GetMeshs().insert(make_pair("Box", _Result));

	std::vector<Vertex> vertices(Box.Vertices.size());
	std::vector<index3> indices(Box.Indices.size() / 3);

	ChangeGeometry(&Box, vertices, indices);

	for (auto& iter : vertices)
	{
		iter.Color = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	}
	VBIBMesh* _Temp = _Result->AddMeshComponent<VBIBMesh>();
	_Temp->Init(vertices, indices, Effects::LightFX->m_LightTech, Effects::LightFX);
	_Temp->SetTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	_Result->SetRasterizerState(RasterizerState::m_SolidRS);


	Material* _Mat = new Material();
	_Mat->Ambient = XMFLOAT4(0.5f, 0.5f, 0.5f, 0.5f);
	_Mat->Diffuse = XMFLOAT4(0.8f, 0.8f, 0.8f, 0.8f);
	_Result->SetMaterial(_Mat);
}

void Bulider::CreateSolidSphereMesh()
{

}
