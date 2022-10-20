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
	//���� �� ���ŷ� ����
	memcpy(old, cur, sizeof(cur));

	//���� ��, ���� Ű���� �Է°� �ʱ�ȭ.
	memset(cur, 0, sizeof(cur));
	memset(map, 0, sizeof(cur));

	//���� �� �ҷ�����.
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



//���콺�� ���� ��ġ�� ����.
const XMFLOAT2 KeyBoard::GetPos()
{
	POINT ptMouse;
	GetCursorPos(&ptMouse);
	ScreenToClient(m_hWnd, &ptMouse);
	XMFLOAT2 pos = { (float)ptMouse.x/*+ MyEngine::GetCamera()->GetPos().x*/,(float)ptMouse.y/*+ MyEngine::GetCamera()->GetPos().y*/ };

	return pos;
}

