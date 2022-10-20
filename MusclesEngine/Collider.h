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
	virtual void Update() abstract; // ��� Object Udpate���� �� (ObjectManager) ������Ʈ�� Components�� ������ ������ ���� ������Ʈ ���ֱ�.
	virtual void Render() abstract; // ��� Object ���� ���� �� (ObjectManager) ������Ʈ�� Components�� ������ ������ ���� ����

};

