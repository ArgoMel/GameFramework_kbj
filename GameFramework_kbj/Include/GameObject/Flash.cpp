#include "Flash.h"

CFlash::CFlash()
	: m_Count(5)
	, m_time(0.f)
{
	m_renderLayer = ERender_Layer::Effect;
}

CFlash::CFlash(const CFlash& obj)
	:CGameObject(obj)
	, m_Count(obj.m_Count)
	, m_time(obj.m_time)
{
}

CFlash::~CFlash()
{
}

bool CFlash::Init()
{
	SetPos(640.f, 360.f);
	SetPivot(0.5f, 0.5f);
	return true;
}

void CFlash::Update(float deltaTime)
{
	CGameObject::Update(deltaTime);
	m_time -= deltaTime;
	if (m_time <= 0)
	{
		m_time = 0.15f;
		if (m_Count%2==1)
		{
			SetTexture("Black", TEXT("black_bg.bmp"));
		}
		else
		{
			SetTexture("Null", TEXT("black_g.bmp"));
		}
		--m_Count;
	}
	if(0==m_Count)
	{
		SetActive(false);
	}
}

void CFlash::PostUpdate(float deltaTime)
{
	CGameObject::PostUpdate(deltaTime);
}

void CFlash::Render(HDC hDC, float deltaTime)
{
	CGameObject::Render(hDC, deltaTime);
}
