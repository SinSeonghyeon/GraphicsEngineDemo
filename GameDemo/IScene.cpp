#include "stdafx.h"
#include "IScene.h"


IScene::IScene()
{
	m_ObjManager = CreateObjectManager();
}

IScene::~IScene()
{
	DeleteObjectManager(m_ObjManager);
}

ObjectManager* IScene::GetObjManager()
{
	return m_ObjManager;
}
