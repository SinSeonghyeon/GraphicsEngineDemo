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
	virtual void Update(); // ��� Object Udpate���� �� (ObjectManager) ������Ʈ�� Components�� ������ ������ ���� ������Ʈ ���ֱ�.
	virtual void Render(); // ��� Object ���� ���� �� (ObjectManager) ������Ʈ�� Components�� ������ ������ ���� ����

	void Initialize(IMesh* _Mesh);
	IMesh* GetMesh();
private:
	void MakeBoneTM();
	bool m_isBone = false;
	// ���� �־�� �ϴ�..
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

