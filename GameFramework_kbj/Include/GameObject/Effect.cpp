#include "Effect.h"

CEffect::CEffect()
	: m_effectType(EEffect_Type::Once)
	, m_duration(0.f)
	, m_time(0.f)
{
	m_renderLayer = ERender_Layer::Effect;
}

CEffect::CEffect(const CEffect& obj)
	:CGameObject(obj)
	,m_effectType(obj.m_effectType)
	,m_duration(obj.m_duration)
	,m_time(obj.m_time)
{
}

CEffect::~CEffect()
{
}

bool CEffect::Init()
{
	SetPivot(0.5f, 0.5f);
	CreateAnimation();
	AddAnimation("Warning", false);
	AddAnimation("Exclamation_mark", false);
	//SetCurrentAnimationEndFunction<CEffect>(this, &CEffect::AnimationEnd);
	return true;
}

void CEffect::Update(float deltaTime)
{
	CGameObject::Update(deltaTime);
	if (m_effectType == EEffect_Type::Duration)
	{
		m_time += deltaTime;
		if (m_time >= m_duration)
		{
			SetActive(false);
		}
	}
}

void CEffect::PostUpdate(float deltaTime)
{
	CGameObject::PostUpdate(deltaTime);
}

void CEffect::Render(HDC hDC, float deltaTime)
{
	CGameObject::Render(hDC, deltaTime);
}

void CEffect::AnimationEnd()
{
	if (m_effectType == EEffect_Type::Once)
	{
		SetActive(false);
	}
}