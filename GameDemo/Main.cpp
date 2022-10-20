// D3DEngine.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//
#include "stdafx.h"
#include <crtdbg.h>

const int width = 500;
const int Height = 1000;
GameProcess* _GameProcess = nullptr;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
int WINAPI WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine,
	_In_ int nCmdShow)
{
	//_CrtSetBreakAlloc(84081);

	LPCWSTR szAppName = L"TEST";
	HWND hWnd;
	MSG msg;
	WNDCLASS wndclass;

	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = WndProc;//
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = szAppName;
	// 윈도 클래스 등록
	RegisterClass(&wndclass);


	//윈도 생성
	hWnd = CreateWindow(szAppName, szAppName, WS_OVERLAPPEDWINDOW, 0, 0, width, Height, NULL, NULL, hInstance, NULL);
	//생성된 윈도를 화면에 표시
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	_GameProcess = new GameProcess();
	_GameProcess->Initialize(hWnd, width, Height);
	/// 메세지 루프
	while (true)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) break;
			DispatchMessage(&msg);
		}
		else
		{
			_GameProcess->Update();
			_GameProcess->Render();
		}
	}
	delete _GameProcess;

	_CrtDumpMemoryLeaks();

	return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM IParam)
{
	if (_GameProcess)
		return _GameProcess->MessageHandle(hWnd, message, wParam, IParam);
	else
		return DefWindowProc(hWnd, message, wParam, IParam);
}