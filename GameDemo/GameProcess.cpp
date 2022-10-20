#include "stdafx.h"
#include "GameProcess.h"
#include "TestScene.h"

GameProcess::GameProcess() :m_GameEngine(nullptr),m_SceneManager(nullptr)
{
}

GameProcess::~GameProcess()
{
	DeleteMuscle(m_GameEngine);
	m_SoundManager->Finalize();
	delete m_SceneManager;
}

void GameProcess::Initialize(HWND _Hwnd, int WindowSizeX, int WindowSizeY)
{
	m_SoundManager = ::GetSoundManager();
	m_SoundManager->Initialize();
	m_GameEngine = CreateMuscle();
	m_GameEngine->Initialize(_Hwnd, WindowSizeX, WindowSizeY);

	m_SceneManager = new SceneManager();
	m_SceneManager->ChangeScene<TestScene>();

}

void GameProcess::Update()
{
	m_SoundManager->Update();
	m_SceneManager->GetScene()->Update();
	m_GameEngine->Update();
}

void GameProcess::Render()
{
	m_GameEngine->Render();
}

SceneManager* GameProcess::GetSceneManager()
{
	return m_SceneManager;
}

int GameProcess::MessageHandle(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_SIZE:
		if (wParam == SIZE_MINIMIZED)
		{
			// 해결!
			// width height 0이 들어가면 터진다.
		}
		else
		{
			if (m_GameEngine)
				m_GameEngine->OnResize();
		}

		break;
	case WM_MOUSEMOVE:
		/*if (m_GrapicsEngine)
			m_GrapicsEngine->OnMouseMove(wParam, LOWORD(lParam), HIWORD(lParam));*/
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
