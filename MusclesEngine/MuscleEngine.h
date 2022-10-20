#pragma once

#include "Define.h"

class IGraphicsEngine;
class CTime;
class KeyBoard;
class ObjectManager;
class IMesh;
class Camera;

class ENGINE_API MuscleEngine // �ʴ� �������� �� �������̽��� �ٲ��ٰ�..
{
public:
	MuscleEngine();
	~MuscleEngine();
private:
	IGraphicsEngine* m_GraphicsEngine; //�׷��Ƚ� ����.. ���� �и��� ���� �������̽���.

	CTime* m_Time;
	KeyBoard* m_keyBoard;
	ObjectManager* m_ObjManager;
	static MuscleEngine* m_Instance;
	HWND m_hWnd;
	Camera* m_MainCamera;
public:
	void Initialize(HWND hWnd, int Width, int height);

	void Update();
	void Render();
	void OnResize();
	void SetMainCamera(Camera* _MainCamera);
	Camera* GetMainCamera();
	static MuscleEngine* GetInstance();

	void SetObjManager(ObjectManager* _ObjManager);
	ObjectManager* GetObjManager();
	IGraphicsEngine* GetGraphicsEngine();
	HWND GetHWND();
	IMesh* GetMesh(string _Name);
private:
	void BeginRender();
	void EndRender();
};

extern "C" ENGINE_API MuscleEngine * CreateMuscle(); // �ټ��� ����
extern "C" ENGINE_API void DeleteMuscle(MuscleEngine * _delete); // �ټս� �̤�