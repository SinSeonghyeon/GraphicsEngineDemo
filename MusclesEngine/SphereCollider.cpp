#include "GameEnginePCH.h"
#include "SphereCollider.h"
SphereCollider::SphereCollider(GameObject* _GameObject) :Collider(_GameObject), m_Radius(0)
{
}

SphereCollider::~SphereCollider()
{
}

void SphereCollider::initialize(float _Radius)
{
	m_ColliderType = ColliderType::Sphere;

	if (_Radius)
	{
		m_Radius = _Radius;
	}
	else
	{
		MeshRenderer* _Mesh = m_GameObject->GetComponent<MeshRenderer>();
		XMFLOAT3 _MaxPos = _Mesh->GetMaxPos();
		XMFLOAT3 _MinPos = _Mesh->GetMinPos();
		float x, y, z;
		x = _MaxPos.x - _MinPos.x;
		y = _MaxPos.y - _MinPos.y;
		z = _MaxPos.z - _MinPos.z;

		x = max(x, y);
		x = max(x, z);

		m_Radius = x / 2;

	}
	GizmoInfo _Info = {
	Shphere,
	m_Radius
	};
	m_GameObject->AddComponent<GizmoRenderer>()->Initialize(&_Info);
}

void SphereCollider::ColliderCheck(Collider* _Other)
{
	switch (_Other->m_ColliderType)
	{
	case ColliderType::Sphere:
	{

		SphereCollider* _OtherSphere = dynamic_cast<SphereCollider*>(_Other);

		XMFLOAT3 _thispos = m_Transform->GetPosition();
		XMFLOAT3 _otherpos = _Other->m_Transform->GetPosition();

		XMVECTOR _ThisPosition = XMLoadFloat3(&_thispos);
		XMVECTOR _OtherPosition = XMLoadFloat3(&_otherpos);

		XMVECTOR _Distance = XMVectorSubtract(_OtherPosition, _ThisPosition);

		_Distance = XMVector3Length(_Distance);


		float _RadiusPlus = (_OtherSphere->m_Radius * _OtherSphere->m_Transform->GetScale().x) + (m_Radius * m_Transform->GetScale().x);




		if (_RadiusPlus > _Distance.m128_f32[0]) // 충돌.
		{

			auto Check = [&]() -> bool
			{
				for (auto& iter : m_Colliders)
				{
					if (iter == _Other)
					{
						return false;
					}
				}
				return true;
			};

			if (Check())
			{
				m_Colliders.push_back(_Other);
				m_GameObject->OnEnterCollision(_Other);
			}

		}
		else // 충돌 안함.
		{
			for (auto iter = m_Colliders.begin(); iter != m_Colliders.end(); iter++)
			{
				m_GameObject->OnExitCollision(_Other);
				m_Colliders.erase(iter);
				break;
			}
		}
		break;
	}
	case ColliderType::AABB:
	{

		break;
	}
	case ColliderType::OBB:
	{

		break;
	}
	default:
		break;
	}
}

void SphereCollider::Start()
{
}

void SphereCollider::Update()
{

	for (auto& iter : m_Colliders)
	{
		m_GameObject->OnStayCollision(iter);
	}
}

void SphereCollider::Render()
{

}