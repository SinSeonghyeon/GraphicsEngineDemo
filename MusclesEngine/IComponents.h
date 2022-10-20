#pragma once

/// <summary>
/// ������ �ܼ��ϰ� ������
/// ������ ������!
/// 2022-03-29 �ż���
/// </summary>
class GameObject;
class Collider;

class ENGINE_API IComponents
{
public:
	IComponents(GameObject* _GameObj); //�θ� ���� ������Ʈ�� ���ڷ� �ް� �ʱ�ȭ
	virtual ~IComponents();
	GameObject* m_GameObject; //�θ�

public:
	virtual void OnEnterCollision(Collider* _Other) {};
	virtual void OnStayCollision(Collider* _Other) {};
	virtual void OnExitCollision(Collider* _Other) {};
public:


	virtual void Start() {};
	virtual void Update() abstract; // ��� Object Udpate���� �� (ObjectManager) ������Ʈ�� Components�� ������ ������ ���� ������Ʈ ���ֱ�.
	virtual void Render() {}; // ��� Object ���� ���� �� (ObjectManager) ������Ʈ�� Components�� ������ ������ ���� ����
};
