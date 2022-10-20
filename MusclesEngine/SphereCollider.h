#pragma once
class ENGINE_API SphereCollider : public Collider
{
public:
	SphereCollider(GameObject* _GameObject);
	~SphereCollider();
	void initialize(float _Radius = 0);
private:
	float m_Radius;
public:
	virtual void ColliderCheck(Collider* _Other);
	virtual void Start();
	virtual void Update(); // 모든 Object Udpate돌릴 때 (ObjectManager) 오브젝트가 Components를 가지고 있으면 같이 업데이트 해주기.
	virtual void Render(); // 모든 Object 렌더 돌릴 때 (ObjectManager) 오브젝트가 Components를 가지고 있으면 같이 렌더
};

