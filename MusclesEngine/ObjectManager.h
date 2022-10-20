#pragma once
#include <vector>

/// <summary>
/// ������ �ܼ��ϰ� ������
/// ������ ������!
/// 2022-03-29 �ż���
/// </summary>
class GameObject;
class Collider;

class  ObjectManager
{

public:
	ObjectManager();
	~ObjectManager();
public:
	std::vector<GameObject*> m_vectorObjects;

public:
	//��ü ����
	ENGINE_API void InsertObject(GameObject* obj);
	//Ư�� ��ü ����
	ENGINE_API void DeleteObject(GameObject* obj);

	//��ü ����
	void DeleteAll();

	void Update();
	void Render();
private:
	std::vector<GameObject*> m_DeleteObjects; //���� ���� ������Ʈ��.
	std::vector<GameObject*> m_InsertObjects; //�߰� ���� ������Ʈ��.

private:
	vector<Collider*> m_Colliders;


};

 
extern "C" ENGINE_API ObjectManager* CreateObjectManager();
extern "C" ENGINE_API void DeleteObjectManager(ObjectManager* _ObjManager);