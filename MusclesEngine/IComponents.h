#pragma once

/// <summary>
/// 구조를 단순하게 만들어보자
/// 엔진을 만들자!
/// 2022-03-29 신성현
/// </summary>
class GameObject;
class Collider;

class ENGINE_API IComponents
{
public:
	IComponents(GameObject* _GameObj); //부모를 게임 오브젝트를 인자로 받고 초기화
	virtual ~IComponents();
	GameObject* m_GameObject; //부모

public:
	virtual void OnEnterCollision(Collider* _Other) {};
	virtual void OnStayCollision(Collider* _Other) {};
	virtual void OnExitCollision(Collider* _Other) {};
public:


	virtual void Start() {};
	virtual void Update() abstract; // 모든 Object Udpate돌릴 때 (ObjectManager) 오브젝트가 Components를 가지고 있으면 같이 업데이트 해주기.
	virtual void Render() {}; // 모든 Object 렌더 돌릴 때 (ObjectManager) 오브젝트가 Components를 가지고 있으면 같이 렌더
};
