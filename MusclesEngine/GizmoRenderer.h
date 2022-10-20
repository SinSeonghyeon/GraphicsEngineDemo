#pragma once

class IMesh;
struct GizmoInfo;

class ENGINE_API GizmoRenderer : public IComponents
{
public:
	GizmoRenderer(GameObject* _GameObject);
	~GizmoRenderer();

public:
	virtual void Start();
	virtual void Update(); // ��� Object Udpate���� �� (ObjectManager) ������Ʈ�� Components�� ������ ������ ���� ������Ʈ ���ֱ�.
	virtual void Render(); // ��� Object ���� ���� �� (ObjectManager) ������Ʈ�� Components�� ������ ������ ���� ����
public:
	virtual void OnEnterCollision(Collider* _Other) override;
	virtual void OnStayCollision(Collider* _Other) override;
	virtual void OnExitCollision(Collider* _Other) override;

public:
	void Initialize(GizmoInfo* _GizmoInfo);
	IMesh* GetMesh();
	void SetColor(XMFLOAT4 _Color);
	void finalize();

private:
	IMesh* m_Mesh;
	bool m_isInit;
};

