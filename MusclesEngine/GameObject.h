#pragma once

/// <summary>
/// 구조를 단순하게 만들어보자
/// 엔진을 만들자!
/// 2022-03-29 신성현
/// </summary>
#ifdef MUSCLESENGINE_EXPORTS
#define ENGINE_API __declspec(dllexport)
#else
#define ENGINE_API __declspec(dllimport)
#endif
class IComponents;
class Transform;
class Collider;
class BoxVolume;

class ENGINE_API GameObject
{

public:
	GameObject();
	~GameObject();

public:
	//업데이트
	void Update();
	 Transform* GetTransform();

	 void SetParent(GameObject* _GameObject);
	 GameObject* GetParent() { return m_Parent; }
	 const vector<GameObject*>& GetChildrens() { return m_Childrens; }

	 void SetName(string _Name) { m_Name = _Name; };
	 string GetName() { return m_Name; }

	 GameObject* GetTopParent();

	 GameObject* FindChildren(string _Name);

private:
	string m_Name;
	Transform* m_Transform;
	GameObject* m_Parent;
	vector<GameObject*> m_Childrens;
	bool m_isRender;
public:
	 bool GetisRender() { return m_isRender; }
	 void SetisRender(bool _bool);
	BoxVolume* m_BoxVolume;

public:
	void OnEnterCollision(Collider* _Other);
	void OnStayCollision(Collider* _Other);
	void OnExitCollision(Collider* _Other);


public:
	//컴포넌트 기반 변수 및 함수들
	std::vector<IComponents*> m_Components;
	template  <class  TComponent>
	 TComponent* AddComponent();
	template  <class  TComponent>
	 TComponent* GetComponent();
	friend class ObjectManager;
};

ENGINE_API GameObject* CreateGameObject();

//#ifdef MUSCLESENGINE_EXPORTS
template<class TComponent>
TComponent* GameObject::AddComponent()
{
	TComponent* tempComponent = new TComponent(this);
	m_Components.emplace_back(tempComponent);
	tempComponent->Start();

	return tempComponent;
}

template<class TComponent>
TComponent* GameObject::GetComponent()
{
	for (auto iter : m_Components)
	{
		TComponent* tempComponent = dynamic_cast<TComponent*>(iter);

		if (tempComponent != nullptr)
		{
			return tempComponent;
		}
	}

	return nullptr;
}
//#endif
