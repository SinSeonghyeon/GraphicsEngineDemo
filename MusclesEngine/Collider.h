#pragma once

enum class ColliderType
{
	Sphere,
	AABB,
	OBB
};

class ENGINE_API Collider : public IComponents
{
public:
	Collider(GameObject* _GameObject);
	virtual ~Collider();
private:

protected:
	vector<Collider*> m_Colliders;

public:
	ColliderType m_ColliderType;
	Transform* m_Transform;

public:
	virtual void ColliderCheck(Collider* _Other) abstract;
	virtual void Start() abstract;
	virtual void Update() abstract; // 모든 Object Udpate돌릴 때 (ObjectManager) 오브젝트가 Components를 가지고 있으면 같이 업데이트 해주기.
	virtual void Render() abstract; // 모든 Object 렌더 돌릴 때 (ObjectManager) 오브젝트가 Components를 가지고 있으면 같이 렌더

};

