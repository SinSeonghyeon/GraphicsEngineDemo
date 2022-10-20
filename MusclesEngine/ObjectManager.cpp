#include "GameEnginePCH.h"
#include "ObjectManager.h"

ObjectManager::ObjectManager()
{

}

ObjectManager::~ObjectManager()
{
	DeleteAll();
}


//��ü �߰�
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

//Ư�� ��ü ����
void ObjectManager::DeleteObject(GameObject* obj)
{
	if (!obj) return;
	m_DeleteObjects.push_back(obj);
}

//������Ʈ�� �ݶ��̴� ���� ����
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
	//��� ������Ʈ ������Ʈ ������
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



	// ������Ʈ ����. for�� ���߿� ������ �߰��� ���� �߻�.
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
	// ������Ʈ �߰�.
	for (auto iter : m_InsertObjects)
	{
		InsertObject(iter);
	}
	if (!m_InsertObjects.empty())
		m_InsertObjects.clear();
}

//��� ������Ʈ ����
void ObjectManager::Render()
{
	for (auto iter = m_vectorObjects.begin(); iter != m_vectorObjects.end(); iter++)
	{
		if (!(**iter).m_isRender)
		{
			continue;
		}

		//������Ʈ�� ���� ������
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
