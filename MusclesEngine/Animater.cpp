#include "GameEnginePCH.h"
#include "Animater.h"
#include "..\GraphicsEngine\IMesh.h"
Animater::Animater(GameObject* _GameObj) :IComponents(_GameObj)
{

}

Animater::~Animater()
{
	for (auto& iter : m_AnimClips)
	{
		delete iter.second;
	}
}



void Animater::Play(string _AniName)
{
	if (m_AnimClips.find(_AniName) != m_AnimClips.end())
	{
		m_AnimClips[m_PlayAnimName]->Stop();
		m_PlayAnimName = _AniName;
	}
}

void Animater::Start()
{

	MeshRenderer* _MeshRenderer = nullptr;
	for (const auto& iter : m_GameObject->GetChildrens())
	{
		_MeshRenderer = iter->GetComponent<MeshRenderer>();
		if (!_MeshRenderer->GetMesh()->GetAnimationKey().empty())
			break;
	}
	for (int i = 0; i < _MeshRenderer->GetMesh()->GetAnimationKey().size(); i++)
	{
		const auto& _Temp = _MeshRenderer->GetMesh()->GetAnimationKey();
		m_AnimClips[_Temp[i].m_Name] = new AnimationClip();
		m_AnimClips[_Temp[i].m_Name]->Init(m_GameObject, i);
	}
	m_PlayAnimName = m_AnimClips.begin()->first;

}

void Animater::Update()
{

	m_AnimClips[m_PlayAnimName]->Update();

	if (!m_AnimClips[m_PlayAnimName]->GetisPlaying())
		m_AnimClips[m_PlayAnimName]->Play();
}

void Animater::Render()
{

}
