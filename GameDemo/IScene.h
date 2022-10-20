#pragma once
class ObjectManager;

/// <summary>
/// 신성현
/// 씬 만드는 중.
/// 오브젝트 매니저는 씬마다..
/// 22.04.12
/// </summary>
class IScene
{
public:
	IScene();
	virtual ~IScene();
private:
	//업데이트 돌려주세용~
	ObjectManager* m_ObjManager; //돌려주세요~!
	//돌리셔야합니다.
public:
	virtual void Start() abstract; // 카메라 만들어서 넣어주세용~ 엔진에 메인 카메라 셋팅도 하세용~
	virtual void Update() abstract;

	ObjectManager* GetObjManager();
};

