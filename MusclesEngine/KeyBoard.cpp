#include "GameEnginePCH.h"
#include "KeyBoard.h"

KeyBoard* KeyBoard::Instance = nullptr;

KeyBoard::KeyBoard(HWND hWnd) : m_hWnd(hWnd)
{
	if (Instance == nullptr)
	{
		Instance = this;
	}
	else
		delete this;
}

KeyBoard::~KeyBoard()
{
}

void KeyBoard::Update()
{
	KeyCheck();
}


void KeyBoard::KeyCheck()
{
	//현재 값 과거로 복사
	memcpy(old, cur, sizeof(cur));

	//현재 값, 현재 키보드 입력값 초기화.
	memset(cur, 0, sizeof(cur));
	memset(map, 0, sizeof(cur));

	//현재 값 불러오기.
	GetKeyboardState(cur);

	for (int i = 0; i < 256; i++)
	{

		unsigned char _cur = cur[i] & 0x80 ? 1 : 0;
		unsigned char _old = old[i] & 0x80 ? 1 : 0;


		//Press
		if (_cur && _old)
			map[i] = PRESS;
		//Down
		else if (_cur && !_old)
			map[i] = DOWN;
		//Up
		else if (!_cur && _old)
			map[i] = UP;
		else
			map[i] = 0;

	}
}



//마우스의 현재 위치를 리턴.
const XMFLOAT2 KeyBoard::GetPos()
{
	POINT ptMouse;
	GetCursorPos(&ptMouse);
	ScreenToClient(m_hWnd, &ptMouse);
	XMFLOAT2 pos = { (float)ptMouse.x/*+ MyEngine::GetCamera()->GetPos().x*/,(float)ptMouse.y/*+ MyEngine::GetCamera()->GetPos().y*/ };

	return pos;
}


