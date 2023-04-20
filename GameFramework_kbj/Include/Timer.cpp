#include "Timer.h"

CTimer::CTimer()
	:m_second{}
	, m_time{}
	,m_deltatime(0.f)
	,m_FPS(0.f)
	,m_FPStime(0.f)
	,m_tick(0)
{
}

CTimer::~CTimer()
{
}

void CTimer::Init()
{
	QueryPerformanceFrequency(&m_second);
	QueryPerformanceCounter(&m_time);
}

void CTimer::Update()
{
	LARGE_INTEGER	time;
	QueryPerformanceCounter(&time);
	m_deltatime = (time.QuadPart - m_time.QuadPart) / (float)m_second.QuadPart;
	m_time = time;
	m_FPStime += m_deltatime;
	++m_tick;
	if(m_tick==60)
	{
		m_FPS = m_tick / m_FPStime;
		m_FPStime = 0.f;
		m_tick = 0;
	}
}
