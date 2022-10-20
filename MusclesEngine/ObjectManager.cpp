#include "GameEnginePCH.h"
#include "ObjectManager.h"

ObjectManager::ObjectManager()
{

}

ObjectManager::~ObjectManager()
{
	DeleteAll();
}


//객체 추가
void ObjectManager::InsertObject(GameObject* obj)
{
	if (!obj) return;
	m_vectorObjects.push_back(obj);

	Collider* _Collider = obj->GetComponent<Collider>();
	if (_Collider)
		m_Colliders.push_back(_Collider);


	for (auto& GameObjiter : obj->m_Childrens)
	{
		InsertObject(GameObjiter);
	}

}

//특정 객체 삭제
void ObjectManager::DeleteObject(GameObject* obj)
{
	if (!obj) return;
	m_DeleteObjects.push_back(obj);
}

//오브젝트와 콜라이더 전부 삭제
void ObjectManager::DeleteAll()
{
	for (auto iter = m_vectorObjects.begin(); iter != m_vectorObjects.end(); iter++)
	{
		delete (*iter);
	}

	m_vectorObjects.clear();
	m_Colliders.clear();
}

void ObjectManager::Update()
{
	//모든 오브젝트 업데이트 돌리기
	for (auto iter = m_vectorObjects.begin(); iter != m_vectorObjects.end(); iter++)
	{
		(*iter)->Update();
	}

	for (auto& Col1 : m_Colliders)
	{
		for (auto& Col2 : m_Colliders)
		{
			if (Col1 == Col2)
				continue;
			Col1->ColliderCheck(Col2);
		}
	}



	// 오브젝트 삭제. for문 도중에 삭제나 추가시 에러 발생.
	for (auto iter = m_DeleteObjects.begin(); iter != m_DeleteObjects.end(); iter++)
	{

		for (auto iter2 = m_vectorObjects.begin(); iter2 != m_vectorObjects.end(); iter2++)
		{
			if (*iter == *iter2)
			{
				Collider* _Collider = (*iter2)->GetComponent<Collider>();
				if (_Collider)
				{
					for (auto col = m_Colliders.begin(); col != m_Colliders.end(); col++)
					{
						if (*col == _Collider)
						{
							m_Colliders.erase(col);
							break;
						}
					}
				}

				m_vectorObjects.erase(iter2);
				break;
			}
		}

		delete* iter;
		m_DeleteObjects.erase(iter);
		break;
	}
	// 오브젝트 추가.
	for (auto iter : m_InsertObjects)
	{
		InsertObject(iter);
	}
	if (!m_InsertObjects.empty())
		m_InsertObjects.clear();
}

//모든 오브젝트 렌더
void ObjectManager::Render()
{
	for (auto iter = m_vectorObjects.begin(); iter != m_vectorObjects.end(); iter++)
	{
		if (!(**iter).m_isRender)
		{
			continue;
		}

		//컴포넌트의 렌더 돌리기
		for (auto iter2 : (*iter)->m_Components)
		{
			iter2->Render();
		}
	}
}

ENGINE_API ObjectManager* CreateObjectManager()
{
	return new ObjectManager();
}

ENGINE_API void DeleteObjectManager(ObjectManager* _ObjManager)
{
	delete _ObjManager;
}
