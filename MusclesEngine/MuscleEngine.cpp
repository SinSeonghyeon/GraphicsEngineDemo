#include "GameEnginePCH.h"
#include "MuscleEngine.h"

#include "..\GraphicsEngine\IGraphicsEngine.h"

MuscleEngine* MuscleEngine::m_Instance = nullptr;

MuscleEngine::MuscleEngine() : m_GraphicsEngine(nullptr), m_Time(nullptr),
m_keyBoard(nullptr), m_ObjManager(nullptr), m_hWnd(), m_MainCamera(nullptr)
{

	if (m_Instance)
		delete m_Instance;

	m_Instance = this;
}

MuscleEngine::~MuscleEngine()
{
	DeleteDXEngine(m_GraphicsEngine);
	delete m_Time;
	delete m_keyBoard;

}

void MuscleEngine::Initialize(HWND hWnd, int Width, int height)
{
	m_hWnd = hWnd;
	m_GraphicsEngine = CreateDXEngine();
	m_GraphicsEngine->Initialize(hWnd, Width, height);

	m_Time = new CTime();
	m_keyBoard = new KeyBoard(hWnd);
}


void MuscleEngine::Update()
{
	m_Time->Update();
	m_keyBoard->Update();
	m_ObjManager->Update();

}

void MuscleEngine::Render()
{
	BeginRender();

	m_ObjManager->Render();
	//여기에 오브젝트 매니저의 렌더를 넣는게 좋을듯.

	EndRender();
}

void MuscleEngine::BeginRender()
{
	m_GraphicsEngine->BeginRender();
}

void MuscleEngine::EndRender()
{
	m_GraphicsEngine->EndRender();
}

void MuscleEngine::OnResize()
{
	m_GraphicsEngine->OnResize();
	m_MainCamera->SetLens();

}

MuscleEngine* MuscleEngine::GetInstance()
{
	return m_Instance;
}

void MuscleEngine::SetObjManager(ObjectManager* _ObjManager)
{
	m_ObjManager = _ObjManager;
}

ObjectManager* MuscleEngine::GetObjManager()
{
	return m_ObjManager;
}

IGraphicsEngine* MuscleEngine::GetGraphicsEngine()
{
	return m_GraphicsEngine;
}

HWND MuscleEngine::GetHWND()
{
	return m_hWnd;
}

IMesh* MuscleEngine::GetMesh(string _Name)
{
	IMesh* _Result = m_GraphicsEngine->GetMeshResource(_Name);
	assert(_Result);
	return _Result;
}

void MuscleEngine::SetMainCamera(Camera* _MainCamera)
{
	if (m_MainCamera)
		m_MainCamera->SetMainCamera(false);

	m_MainCamera = _MainCamera;
	m_MainCamera->SetMainCamera(true);
	m_MainCamera->SetLens();
}

Camera* MuscleEngine::GetMainCamera()
{
	return m_MainCamera;
}

ENGINE_API MuscleEngine* CreateMuscle()
{
	return new MuscleEngine();
	// 나중에는 인터페이스만 제공하는 식으로 변경하자.. 지금은 할게 너무 많다.
}

ENGINE_API void DeleteMuscle(MuscleEngine* _delete)
{
	delete _delete;
}
