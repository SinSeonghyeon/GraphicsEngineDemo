#pragma once
class ENGINE_API AABBCollider : public Collider
{
public:
	AABBCollider(GameObject* _GameObject);
	~AABBCollider();

private:
	XMFLOAT3 m_VertexPos[8];
public:
	void initialize(XMFLOAT3* _VertexPos = nullptr);
public:
	virtual void ColliderCheck(Collider* _Other);
	virtual void Start();
	virtual void Update(); // 모든 Object Udpate돌릴 때 (ObjectManager) 오브젝트가 Components를 가지고 있으면 같이 업데이트 해주기.
	virtual void Render(); // 모든 Object 렌더 돌릴 때 (ObjectManager) 오브젝트가 Components를 가지고 있으면 같이 렌더
};


