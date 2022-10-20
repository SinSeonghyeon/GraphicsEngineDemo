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
	virtual void Update(); // ��� Object Udpate���� �� (ObjectManager) ������Ʈ�� Components�� ������ ������ ���� ������Ʈ ���ֱ�.
	virtual void Render(); // ��� Object ���� ���� �� (ObjectManager) ������Ʈ�� Components�� ������ ������ ���� ����
};

