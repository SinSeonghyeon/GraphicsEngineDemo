#include "GameEnginePCH.h"
#include "GameObject.h"

GameObject::GameObject() :m_Parent(nullptr), m_BoxVolume(nullptr), m_isRender(true)
{
	m_Transform = AddComponent<Transform>();
}

GameObject::~GameObject()
{
	for (auto iter : m_Components)
	{
		delete iter;
	}
	m_Components.clear();

}

void GameObject::Update()
{
	for (auto iter : m_Components)
	{
		iter->Update();
	}
}

Transform* GameObject::GetTransform()
{
	return m_Transform;
}

void GameObject::SetParent(GameObject* _GameObject)
{
	//부모가 없을때만 사용 가능.
	assert(!m_Parent);
	m_Parent = _GameObject;
	m_Parent->m_Childrens.push_back(this);
}

GameObject* GameObject::GetTopParent()
{
	if (m_Parent)
		return m_Parent->GetTopParent();
	else
		return this;
}

GameObject* GameObject::FindChildren(string _Name)
{
	if (m_Name == _Name)
		return this;

	for (auto iter : m_Childrens)
	{
		if (iter->m_Name == _Name)
			return iter;
		else
		{
			GameObject* Temp = iter->FindChildren(_Name);
			if (Temp)
				return Temp;
		}
	}

	return nullptr;
}

void GameObject::SetisRender(bool _bool)
{
	for (auto& iter : m_Childrens)
	{
		iter->m_isRender = _bool;
		iter->SetisRender(_bool);
	}
	m_isRender = _bool;
}

void GameObject::OnEnterCollision(Collider* _Other)
{
	for (auto& iter : m_Components)
	{
		iter->OnEnterCollision(_Other);
	}
}

void GameObject::OnStayCollision(Collider* _Other)
{
	for (auto& iter : m_Components)
	{
		iter->OnStayCollision(_Other);
	}
}

void GameObject::OnExitCollision(Collider* _Other)
{
	for (auto& iter : m_Components)
	{
		iter->OnExitCollision(_Other);
	}
}

ENGINE_API GameObject* CreateGameObject()
{
	GameObject* _GameObject = new GameObject();
	return _GameObject;
}
