#include "GameEnginePCH.h"
#include "IComponents.h"

IComponents::IComponents(GameObject* _GameObj)
{
	m_GameObject = _GameObj;
}

IComponents::~IComponents()
{
}
