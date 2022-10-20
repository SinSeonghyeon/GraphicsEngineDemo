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
	virtual void Update(); // ��� Object Udpate���� �� (ObjectManager) ������Ʈ�� Components�� ������ ������ ���� ������Ʈ ���ֱ�.
	virtual void Render(); // ��� Object ���� ���� �� (ObjectManager) ������Ʈ�� Components�� ������ ������ ���� ����
};


