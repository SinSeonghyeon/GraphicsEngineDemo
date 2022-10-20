///
/// Winmain 디폴트
/// 
/// FMOD 사운드 예제를 위해서 가져왔음
/// 2022.02.18 김주환

#include <windows.h>
//#include "..\SoundTest\CSoundManager.h"	// 이러면 결국 구현을 알게 된다.
#include "..\SoundLib\InstanceGetter.h"		// 둘 다 구현은 SoundLib.Lib (fmod.dll 종속성 있음)
#include "..\SoundLib\ISoundManager.h"		// 둘 다 구현은 SoundLib.Lib (fmod.dll 종속성 있음)

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

/// WinMain 함수 : 윈도즈 프로그램의 최초 진입점 ( Entry Point )
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPTSTR lpCmdLine, _In_ int nCmdShow)
{
	char	  szAppName[] = "Game Academy 2022";
	HWND	  hWnd;
	MSG      msg;
	WNDCLASS wndclass;

	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = WndProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = szAppName;

	/// 윈도 클래스 등록
	RegisterClass(&wndclass);

	/// 윈도 생성
	hWnd = CreateWindow(szAppName,
		szAppName,
		WS_OVERLAPPEDWINDOW,
		100, 100, 800, 600,
		NULL, NULL, hInstance, NULL);

	if (!hWnd) return FALSE;

	/// 생성된 윈도를 화면에 표시
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);


	// 사운드 매니저 테스트
	ISoundManager* _pSoundManager = ::GetSoundManager();
	//CSoundManager* _pSoundManager = new CSoundManager();		// 이러면 결국 구현을 알게 된다.
	_pSoundManager->Initialize();


	/// 메시지 루프
	while (TRUE)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) break;
			DispatchMessage(&msg);
		}
		else
		{
			_pSoundManager->Update();

			if (GetAsyncKeyState(VK_SPACE) & 0x8001)
			{
				//_pSoundManager->
			}
		}
	}

	_pSoundManager->Finalize();

	return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message,
	WPARAM wParam, LPARAM lParam)
{
	HDC			hdc;
	PAINTSTRUCT ps;

	switch (message)
	{
		case WM_PAINT:
			hdc = BeginPaint(hWnd, &ps);
			EndPaint(hWnd, &ps);
			break;

		case WM_DESTROY:
			PostQuitMessage(0);
			break;

		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

