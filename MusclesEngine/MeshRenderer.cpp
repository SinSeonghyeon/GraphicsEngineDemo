#include "GameEnginePCH.h"
#include "MeshRenderer.h"
#include "..\GraphicsEngine\IMesh.h"



MeshRenderer::MeshRenderer(GameObject* _GameObject) :IComponents(_GameObject), m_Mesh(nullptr), m_isInit(false)
{
}

MeshRenderer::~MeshRenderer()
{

}


void MeshRenderer::Initialize(IMesh* _Mesh)
{
	m_Mesh = _Mesh;
	m_isInit = true;
	m_GameObject->SetName(_Mesh->GetName());
	m_isWake = true;
	if (m_Mesh->GetChilrens().empty())
	{
		// 마지막
	}
	else
	{
		//// 첫번째 중간
		for (auto iter : m_Mesh->GetChilrens())
		{
			GameObject* _Child = CreateGameObject();
			_Child->SetParent(m_GameObject);

			MeshRenderer* _Temp = _Child->AddComponent<MeshRenderer>();
			_Temp->Initialize(iter);
			_Child->SetName(iter->GetName());
			_Child->GetTransform()->SetXMLocalTM(_Temp->m_Mesh->GetNodeLocalTM());

			for (auto& iter : _Temp->m_Mesh->GetAnimationKey())
			{
				iter.m_GameObject = _Child;
			}
		}
	}


	if (!m_Mesh->GetParent() && !m_Mesh->GetChilrens().empty())
	{
		for (auto iter : m_Mesh->GetBoneNameList())
		{
			GameObject* _Temp = m_GameObject->FindChildren(iter);
			if (_Temp)
			{
			MeshRenderer* _Mesh = _Temp->GetComponent<MeshRenderer>();
			_Mesh->m_isBone = true;
			m_BoneList.push_back(_Mesh);
			}
				
			// 본 리스트를 만들자!  오늘은 여기까지. todo : 
		}
	}

	m_MaxPos = m_Mesh->GetMaxPos();
	m_MinPos = m_Mesh->GetMinPos();
	float _Sum = m_MaxPos.x + m_MaxPos.y + m_MaxPos.z + m_MinPos.x + m_MinPos.y + m_MinPos.z;
	if (_Sum > 0)
		m_GameObject->AddComponent<BoxVolume>();
	m_GameObject->GetTransform()->MakeTM();
	CopyBone(m_GameObject);
}

IMesh* MeshRenderer::GetMesh()
{
	return m_Mesh;
}




void MeshRenderer::Start()
{

}

void MeshRenderer::Update()
{

	if (m_GameObject->GetisRender() && m_isWake)
	{
		m_Mesh->WakeMesh();
		m_isWake = false;
	}
	else if (!m_GameObject->GetisRender() && !m_isWake)
	{
		m_Mesh->SleepMesh();
		m_isWake = true;
	}
}

void MeshRenderer::Render()
{
	assert(m_Mesh);
	assert(m_isInit);
	XMFLOAT4X4 _Temp = m_GameObject->GetTransform()->GetWorldTM();
	XMMATRIX WorldMt = XMLoadFloat4x4(&_Temp);
	MakeBoneTM();

	m_Mesh->DrawMesh(WorldMt);

}


void MeshRenderer::MakeBoneTM()
{
	if(m_isBone) return;

	m_Mesh->GetFinalBoneList().clear();

	for (auto& iter : m_BoneList)
	{
		XMMATRIX _boneWorldTM = iter->m_GameObject->GetTransform()->GetXMWorldTM(); //본
		XMMATRIX _boneNodeTM = iter->m_Mesh->GetNodeWorldTM(); // 본

		XMMATRIX _skinWorldTM = m_GameObject->GetTransform()->GetXMWorldTM(); // 객체
		XMMATRIX _skinNodeTM = m_Mesh->GetNodeWorldTM(); // 객체

		XMMATRIX _skinWorldTM_inverse = XMMatrixInverse(nullptr, _skinWorldTM);  // 객체

		XMMATRIX _boneNodeTM_inverse = XMMatrixInverse(nullptr, _boneNodeTM);  // 객체

		XMMATRIX _finalboneTM = _skinNodeTM *  _boneNodeTM_inverse * _boneWorldTM  * _skinWorldTM_inverse;

		//XMMATRIX _Indentity = XMMatrixIdentity();
		//m_Mesh->GetFinalBoneList().push_back(_Indentity);
		m_Mesh->GetFinalBoneList().push_back(_finalboneTM);
	}
}

void MeshRenderer::CopyBone(GameObject* _Obj)
{
	for (auto& iter : _Obj->GetChildrens())
	{
		CopyBone(iter);
	}
	_Obj->GetComponent<MeshRenderer>()->m_BoneList = m_BoneList;
}



