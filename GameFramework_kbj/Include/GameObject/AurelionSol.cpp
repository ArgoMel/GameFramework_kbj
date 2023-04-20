#include "AurelionSol.h"

CAurelionSol::CAurelionSol()
	: m_duringTime(0.f)
	, m_angle(120.f)
	, m_speed(60.f)
	, m_cooltime(10.f)
	, m_range(100.f)
	, m_rangeMin(100.f)
	, m_rangeMax(200.f)
	, m_skillDir(1.f)
	, m_skillOn(false)
{
	SetTypeID<CAurelionSol>();
}

CAurelionSol::CAurelionSol(const CAurelionSol& obj)
	:CGameObject(obj)
	, m_duringTime(obj.m_duringTime)
	, m_angle(obj.m_angle)
	, m_speed(obj.m_speed)
	, m_cooltime(obj.m_cooltime)
	, m_range(obj.m_range)
	, m_rangeMin(obj.m_rangeMin)
	, m_rangeMax(obj.m_rangeMax)
	, m_skillDir(obj.m_skillDir)
	, m_skillOn(obj.m_skillOn)
{
}

CAurelionSol::~CAurelionSol()
{
}

void CAurelionSol::CelestialExpansion()
{
	m_skillOn = true;
	m_speed = 180.f;
	m_duringTime = 0.f;
	m_skillDir = 1.f;
}

bool CAurelionSol::Init()
{
	SetPos(900.f, 100.f);
	SetSize(30.f, 30.f);
	SetPivot(0.5f, 0.5f);
	SetTexture("AurelionSol", TEXT("satelite.bmp"));
	SetColorKey(255, 0, 255);
	return true;
}

void CAurelionSol::Update(float deltaTime)
{
	if(m_skillOn)
	{
		m_range += m_skillDir * (m_rangeMax - m_rangeMin) / 1.5f * deltaTime;
		if(m_range>=m_rangeMax)
		{
			m_range = m_rangeMax;
		}
		else if(m_range<=m_rangeMin)
		{
			m_speed = 60.f;
			m_range = m_rangeMin;
			m_skillOn = false;
		}
		m_duringTime += deltaTime;
		if(m_duringTime>=4.5f)
		{
			m_skillDir = -1.f;
		}
	}
	//m_angle += m_speed * deltaTime;
	//m_pos.x = m_pos.x + cosf(DegreeToRadian(m_angle)) * m_range;
	//m_pos.y = m_pos.y + sinf(DegreeToRadian(m_angle)) * m_range;
}

void CAurelionSol::Render(HDC hDC, float deltaTime)
{
	CGameObject::Render(hDC, deltaTime);
}
