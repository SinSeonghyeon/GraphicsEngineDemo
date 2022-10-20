#pragma once

#define UP 1
#define PRESS 2
#define DOWN 3

class ENGINE_API KeyBoard
{
public:
	KeyBoard(HWND hWnd);
	~KeyBoard();
private:
	HWND m_hWnd;
	static KeyBoard* Instance;

	unsigned char cur[256];//현재 키
	unsigned char old[256];//이전의 키
	unsigned char map[256];//현재 키의 상태. Press, Down, Up
	void KeyCheck();


public:
	static KeyBoard* GetKeyBoard() { return Instance; }
	//마우스 위치 반환
	const XMFLOAT2 GetPos();
	void Update();

	bool KeyDonw(unsigned char _Key) { return map[_Key] == DOWN ? true : false; }
	bool KeyUp(unsigned char _Key) { return map[_Key] == UP ? true : false; }
	bool KeyPress(unsigned char _Key) { return map[_Key] == PRESS ? true : false; }

};

