#include "GameEnginePCH.h"
#include "AABBCollider.h"
AABBCollider::AABBCollider(GameObject* _GameObject) :Collider(_GameObject)
{
}

AABBCollider::~AABBCollider()
{
}

void AABBCollider::initialize(XMFLOAT3* _VertexPos)
{
	m_ColliderType = ColliderType::AABB;


	if (_VertexPos)
	{
		for (int i = 0; i < 8; i++)
		{
			m_VertexPos[i] = _VertexPos[i];
		}
		GizmoInfo _Info =
		{
		Box,
		0,
		m_VertexPos
		};
		m_GameObject->AddComponent<GizmoRenderer>()->Initialize(&_Info);
	}
	else
	{
		MeshRenderer* _Mesh = m_GameObject->GetComponent<MeshRenderer>();
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

	}

}

void AABBCollider::ColliderCheck(Collider* _Other)
{
	switch (_Other->m_ColliderType)
	{
	case ColliderType::Sphere:
	{
		break;
	}
	case ColliderType::AABB:
	{
		AABBCollider* _OtherCollider = dynamic_cast<AABBCollider*>(_Other);
		// x, y 축 부터 계산.
		XMVECTOR _LT = XMVector3Transform(XMLoadFloat3(&m_VertexPos[1]), m_Transform->GetXMWorldTM()); // LeftTop
		XMVECTOR _RB = XMVector3Transform(XMLoadFloat3(&m_VertexPos[4]), m_Transform->GetXMWorldTM()); // RightTop

		XMVECTOR _OtherLT = XMVector3Transform(XMLoadFloat3(&_OtherCollider->m_VertexPos[1]), _OtherCollider->m_Transform->GetXMWorldTM()); // LeftTop
		XMVECTOR _OtherRB = XMVector3Transform(XMLoadFloat3(&_OtherCollider->m_VertexPos[4]), _OtherCollider->m_Transform->GetXMWorldTM()); // RightTop

		if (_RB.m128_f32[0] < _OtherLT.m128_f32[0] ||
			_LT.m128_f32[0] > _OtherRB.m128_f32[0] ||
			_LT.m128_f32[1] < _OtherRB.m128_f32[1] ||
			_RB.m128_f32[1] > _OtherLT.m128_f32[1]) // 충돌 안함
		{
			for (auto iter = m_Colliders.begin(); iter != m_Colliders.end(); iter++)
			{
				m_GameObject->OnExitCollision(_Other);
				m_Colliders.erase(iter);
				break;
			}
		}
		else // 충돌 XY 통과.
		{

			_LT = XMVector3Transform(XMLoadFloat3(&m_VertexPos[2]), m_Transform->GetXMWorldTM()); // LeftTop
			_RB = XMVector3Transform(XMLoadFloat3(&m_VertexPos[5]), m_Transform->GetXMWorldTM()); // RightTop

			_OtherLT = XMVector3Transform(XMLoadFloat3(&_OtherCollider->m_VertexPos[2]), _OtherCollider->m_Transform->GetXMWorldTM()); // LeftTop
			_OtherRB = XMVector3Transform(XMLoadFloat3(&_OtherCollider->m_VertexPos[5]), _OtherCollider->m_Transform->GetXMWorldTM()); // RightTop

			if (_RB.m128_f32[2] < _OtherLT.m128_f32[2] ||
				_LT.m128_f32[2] > _OtherRB.m128_f32[2] ||
				_LT.m128_f32[1] < _OtherRB.m128_f32[1] ||
				_RB.m128_f32[1] > _OtherLT.m128_f32[1]) // 충돌 안함
			{
				for (auto iter = m_Colliders.begin(); iter != m_Colliders.end(); iter++)
				{
					m_GameObject->OnExitCollision(_Other);
					m_Colliders.erase(iter);
					break;
				}
			}
			else// 충돌 ZY 통과.
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
		}

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

void AABBCollider::Start()
{
}

void AABBCollider::Update()
{

	for (auto& iter : m_Colliders)
	{
		m_GameObject->OnStayCollision(iter);
	}
}

void AABBCollider::Render()
{
}
