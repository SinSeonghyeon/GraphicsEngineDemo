#include "GameEnginePCH.h"
#include "Collider.h"

Collider::Collider(GameObject* _GameObject) : IComponents(_GameObject)
{
	m_Transform = _GameObject->GetTransform();
}

Collider::~Collider()
{
}
