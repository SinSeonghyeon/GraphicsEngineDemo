#pragma once
#include "IComponents.h"
class IMesh;

class ENGINE_API MeshRenderer : public IComponents
{
public:
	MeshRenderer(GameObject* _GameObject);
	~MeshRenderer();

public:
	virtual void Start();
	virtual void Update(); // 모든 Object Udpate돌릴 때 (ObjectManager) 오브젝트가 Components를 가지고 있으면 같이 업데이트 해주기.
	virtual void Render(); // 모든 Object 렌더 돌릴 때 (ObjectManager) 오브젝트가 Components를 가지고 있으면 같이 렌더

	void Initialize(IMesh* _Mesh);
	IMesh* GetMesh();
private:
	void MakeBoneTM();
	bool m_isBone = false;
	// 뭐뭐 있어야 하니..
	void CopyBone(GameObject* _Obj);
private:
	bool m_isInit;
	XMFLOAT3 m_MinPos;
	XMFLOAT3 m_MaxPos;
	IMesh* m_Mesh;
	vector<MeshRenderer*> m_BoneList;
	bool m_isWake;

public:
	const XMFLOAT3& GetMinPos() { return m_MinPos; }
	const XMFLOAT3& GetMaxPos() { return m_MaxPos; }
};

