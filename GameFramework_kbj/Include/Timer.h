#pragma once
#include "GameInfo.h"
class CTimer
{
private:
	LARGE_INTEGER	m_second;
	LARGE_INTEGER	m_time;
	float			m_deltatime;
	float			m_FPS;
	float			m_FPStime;
	int				m_tick;
public:
	CTimer();
	~CTimer();
	void Init();
	void Update();
	float GetDeltaTime() const
	{
		return m_deltatime;
	}
	float GetFPS() const
	{
		return m_FPS;
	}
};

