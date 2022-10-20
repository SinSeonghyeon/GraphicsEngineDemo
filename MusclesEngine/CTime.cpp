#include "GameEnginePCH.h"
#include "CTime.h"

float CTime::m_FPS = 0;
float CTime::m_DeltaTime = 0;
CTime::CTime() :
	m_Frequency(NULL),
	m_PrevCount(NULL),
	m_FrameCount(NULL),
	m_FrameTime(NULL)
{
	//기준 시간을 저장
	::QueryPerformanceFrequency(reinterpret_cast<LARGE_INTEGER*>(&m_Frequency));
	//시간 간격의 카운트
	::QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&m_PrevCount));
}

CTime::~CTime()
{
	// 딱히 할 없다.
}

void CTime::Update()
{
	UINT64 _currentCount;

	::QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&_currentCount));

	// 현재 _currentCount에서 전 m_PrevCount를 뺀 값을
	// m_Frequency로 나누어주면 경과된 시간(초)이 나온다.
	m_DeltaTime = (_currentCount - m_PrevCount) / static_cast<float>(m_Frequency);
	m_PrevCount = _currentCount; // preCount에 currentCount를 저장

	m_FrameCount++;				// Update문이 1초에 몇 번 실행되는지 체크하기 위해서 누적 !
	m_FrameTime += m_DeltaTime; // 1 프레임에 평균 몇 초가 걸리는지 체크하기 위해서 누적 !

	if (m_FrameTime > 1.f)		// 1초를 넘어가는 순간 (우린 초당 몇 번의 업데이트 == 프레임이 진행되었는지 궁금하니까 ..)
	{
		m_FPS = (float)m_FrameCount / m_FrameTime;  // 1초 간 Update문이 몇 번 실행되었는지 계산

		m_FrameTime = 0.f;		// 0으로 초기화
		m_FrameCount = 0;		// 0으로 초기화
	}
}

float CTime::GetFPS()
{
	return m_FPS;
}