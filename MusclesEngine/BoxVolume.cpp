#include "GameEnginePCH.h"
#include "BoxVolume.h"
#include "..\GraphicsEngine\IMesh.h"
BoxVolume::BoxVolume(GameObject* _GameObj) : IComponents(_GameObj)
{



}

BoxVolume::~BoxVolume()
{
}

void BoxVolume::Start()
{
	m_GameObject->m_BoxVolume = this;
	IMesh* _Mesh = m_GameObject->GetComponent<MeshRenderer>()->GetMesh();

	XMFLOAT3 _MaxPos = _Mesh->GetMaxPos();
	XMFLOAT3 _MinPos = _Mesh->GetMinPos();


	m_VertexPos[0] = XMFLOAT3(_MaxPos.x, _MaxPos.y, _MaxPos.z);
	m_VertexPos[1] = XMFLOAT3(_MinPos.x, _MaxPos.y, _MaxPos.z);
	m_VertexPos[2] = XMFLOAT3(_MinPos.x, _MaxPos.y, _MinPos.z);
	m_VertexPos[3] = XMFLOAT3(_MaxPos.x, _MaxPos.y, _MinPos.z);
	m_VertexPos[4] = XMFLOAT3(_MaxPos.x, _MinPos.y, _MaxPos.z);
	m_VertexPos[5] = XMFLOAT3(_MinPos.x, _MinPos.y, _MaxPos.z);
	m_VertexPos[6] = XMFLOAT3(_MinPos.x, _MinPos.y, _MinPos.z);
	m_VertexPos[7] = XMFLOAT3(_MaxPos.x, _MinPos.y, _MinPos.z);
	// 버텍스 버퍼 인덱스 버퍼 세팅
	XMFLOAT3 XMFLOAT3[] = {
	m_VertexPos[0],
	m_VertexPos[1],
	m_VertexPos[2],
	m_VertexPos[3],
	m_VertexPos[4],
	m_VertexPos[5],
	m_VertexPos[6],
	m_VertexPos[7]
	};
	GizmoInfo _Info =
	{
	Box,
	0,
	XMFLOAT3
	};
	GizmoRenderer* _Gizmo = m_GameObject->AddComponent<GizmoRenderer>();
	_Gizmo->Initialize(&_Info);
	_Gizmo->Start();

}

void BoxVolume::Update()
{

}

void BoxVolume::Render()
{
}
