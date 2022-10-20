#include "GameEnginePCH.h"
#include "AnimationClip.h"
#include "..\GraphicsEngine\IMesh.h"
AnimationClip::AnimationClip() : m_Speed(0.5f), FrameCount(0), m_isPlay(false), m_isPuase(false)
{

}

AnimationClip::~AnimationClip()
{
}

void AnimationClip::Init(GameObject* _GameObj, int _Index)
{
	for (const auto& iter : _GameObj->GetChildrens())
	{
		if (!iter->GetChildrens().empty())
			Init(iter, _Index);
		MeshRenderer* _MeshRenderer = iter->GetComponent<MeshRenderer>();

		if (!_MeshRenderer) continue;
		if (_MeshRenderer->GetMesh()->GetAnimationKey().empty()) continue;
		auto& _anikey = _MeshRenderer->GetMesh()->GetAnimationKey()[_Index];
		if (!_anikey.m_isAnim) continue;
		m_AnimKeys.push_back(&_anikey);

	}
}

void AnimationClip::Stop()
{
	FrameCount = 0;
	m_isPlay = false;
}

void AnimationClip::Pause()
{
	m_isPuase = !m_isPuase;
}

void AnimationClip::Play()
{
	FrameCount = (float)m_AnimKeys[0]->m_FirstFrame;
	m_isPlay = true;
}

void AnimationClip::Update()
{
	if (!m_isPlay || m_isPuase) return;

	for (const auto& iter : m_AnimKeys)
	{
		for (unsigned int i = 1; i < iter->m_PosKey.size(); i++)
		{
			if (iter->m_PosKey[i].m_Time > FrameCount)
			{
				// 애니메이션 재생 todo : 일단 포지션 값으로만 해보자.

				float Time1 = (float)iter->m_PosKey[i].m_Time;
				float Time2 = (float)iter->m_PosKey[i - 1].m_Time;
				float _t = (float)(FrameCount - Time2) / ((Time1 - Time2));

				XMVECTOR _Pred = XMLoadFloat3(&iter->m_PosKey[i - 1].m_Pos);
				XMVECTOR _Now = XMLoadFloat3(&iter->m_PosKey[i].m_Pos);

				XMVECTOR _interpolRot = XMVectorLerp(_Pred, _Now, _t);

				reinterpret_cast<GameObject*>(iter->m_GameObject)->GetTransform()->SetPosition(_interpolRot);
				break;
			}
			else
			{
				// 다음
			}
		}
		for (unsigned int i = 1; i < iter->m_RotKey.size(); i++)
		{
			if (iter->m_RotKey[i].m_Time > FrameCount)
			{

				float Time1 = (float)iter->m_RotKey[i].m_Time;
				float Time2 = (float)iter->m_RotKey[i - 1].m_Time;
				float _t = (float)(FrameCount - Time2) / ((Time1 - Time2));
				XMVECTOR _interpolRot =
					XMQuaternionSlerp(iter->m_RotKey[i - 1].m_Rot, iter->m_RotKey[i].m_Rot, _t);

				reinterpret_cast<GameObject*>(iter->m_GameObject)->GetTransform()->SetQuaternion(_interpolRot);
				// // 쿼터니언 너무 어려워~
				break;
			}
			else
			{
				// 다음
			}
		}
	}

	if (FrameCount > m_AnimKeys[0]->m_LastFrame)
		Stop();

	FrameCount += 1.0f * m_Speed;
}
