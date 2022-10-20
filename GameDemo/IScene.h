#pragma once
class ObjectManager;

/// <summary>
/// �ż���
/// �� ����� ��.
/// ������Ʈ �Ŵ����� ������..
/// 22.04.12
/// </summary>
class IScene
{
public:
	IScene();
	virtual ~IScene();
private:
	//������Ʈ �����ּ���~
	ObjectManager* m_ObjManager; //�����ּ���~!
	//�����ž��մϴ�.
public:
	virtual void Start() abstract; // ī�޶� ���� �־��ּ���~ ������ ���� ī�޶� ���õ� �ϼ���~
	virtual void Update() abstract;

	ObjectManager* GetObjManager();
};

