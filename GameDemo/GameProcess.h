#pragma once

class MuscleEngine;
class SceneManager;

class GameProcess
{
public:
	GameProcess();
	~GameProcess();

private:
	MuscleEngine* m_GameEngine;
	SceneManager* m_SceneManager;
	ISoundManager* m_SoundManager;
public:
	void Initialize(HWND _Hwnd, int WindowSizeX, int WindowSizeY);
	void Update();
	void Render();

	SceneManager* GetSceneManager();

	// �޽��� �ڵ鷯 (���� �ݹ�)
	int MessageHandle(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};
