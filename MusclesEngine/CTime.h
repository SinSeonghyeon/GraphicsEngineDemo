#pragma once
class ENGINE_API CTime
{
public:
	CTime();
	virtual ~CTime();

private:

	//시간의 단위?
	UINT64 m_Frequency;

	//간격동안 카운트 횟수
	UINT64 m_PrevCount;

	// 이전 프레임에서 현재 프레임까지 경과된 시간
	static float m_DeltaTime;

	// 초당 몇 번의 업데이트가 이루어지는지 체크하기 위한 도구
	UINT32 m_FrameCount;
	float m_FrameTime;

	// 평균 초당 프레임 수
	static float m_FPS;

public:

	void Update();

	static float GetFPS();

	static float GetDeltaTime() { return m_DeltaTime; }
};

