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

	// 메시지 핸들러 (윈도 콜백)
	int MessageHandle(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};
