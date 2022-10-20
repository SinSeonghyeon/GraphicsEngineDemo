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
	virtual void Update(); // 모든 Object Udpate돌릴 때 (ObjectManager) 오브젝트가 Components를 가지고 있으면 같이 업데이트 해주기.
	virtual void Render(); // 모든 Object 렌더 돌릴 때 (ObjectManager) 오브젝트가 Components를 가지고 있으면 같이 렌더
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

