#pragma once
#include <vector>

/// <summary>
/// 구조를 단순하게 만들어보자
/// 엔진을 만들자!
/// 2022-03-29 신성현
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
	//객체 생성
	ENGINE_API void InsertObject(GameObject* obj);
	//특정 객체 삭제
	ENGINE_API void DeleteObject(GameObject* obj);

	//전체 삭제
	void DeleteAll();

	void Update();
	void Render();
private:
	std::vector<GameObject*> m_DeleteObjects; //삭제 예정 오브젝트들.
	std::vector<GameObject*> m_InsertObjects; //추가 예정 오브젝트들.

private:
	vector<Collider*> m_Colliders;


};

 
extern "C" ENGINE_API ObjectManager* CreateObjectManager();
extern "C" ENGINE_API void DeleteObjectManager(ObjectManager* _ObjManager);