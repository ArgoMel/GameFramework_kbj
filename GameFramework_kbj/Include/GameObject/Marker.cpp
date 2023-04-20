#include "Marker.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"
#include "../Collision/ColliderCircle.h"
#include "../Widget/WidgetComponent.h"
#include "../Widget/Text.h"

CMarker::CMarker()
	: m_Time(3.9f)
	, m_IsBreak(false)
{
	SetTypeID<CMarker>();
}

CMarker::CMarker(const CMarker& obj) 
	: CGameObject(obj)
	, m_Time(obj.m_Time)
	, m_IsBreak(false)
{
}

CMarker::~CMarker()
{
}

bool CMarker::Init()
{
	SetPivot(0.5f, 0.5f);
	CreateAnimation();
	AddAnimation("Marker");
	AddAnimation("MarkerBreak");
	SetEndFunction<CMarker>("MarkerBreak", this, &CMarker::Die);
	AddNotify<CMarker>("MarkerBreak", 0, this, &CMarker::CheckBreak);

	CColliderCircle* circle = AddCollider<CColliderCircle>("Marker");
	circle->SetRadius(20.f);
	circle->SetCollisionProfile("Event");
	circle->SetCollisionBeginFunction<CMarker>(this, &CMarker::CollisionBegin);
	circle->SetCollisionEndFunction<CMarker>(this, &CMarker::CollisionEnd);

	m_TimeText = CreateWidgetComponent<CText>("MarkerTime");
	m_TimeText->GetWidget<CText>()->SetText(TEXT("4"));
	m_TimeText->GetWidget<CText>()->EnableShadow(true);
	m_TimeText->GetWidget<CText>()->SetTextColor(255, 255, 255);
	m_TimeText->GetWidget<CText>()->SetTextShadowColor(255, 0, 0);
	m_TimeText->GetWidget<CText>()->SetShadowOffset(1.f, 1.f);
	m_TimeText->SetPos(-6.f, -9.f);
	return true;
}

void CMarker::Update(float deltaTime)
{
	CGameObject::Update(deltaTime);
	std::wstring s = std::to_wstring((int)m_Time);
	m_TimeText->GetWidget<CText>()->SetText(s.c_str());
}

void CMarker::PostUpdate(float deltaTime)
{
	CGameObject::PostUpdate(deltaTime);
	m_Time -= deltaTime;
	if (m_Time < 0)
	{
		m_TimeText->SetActive(false);
		SetActive(false);
	}
}

void CMarker::Render(HDC hDC, float deltaTime)
{
	CGameObject::Render(hDC, deltaTime);
}

void CMarker::DeactiveText()
{
	m_TimeText->SetActive(false);
}

void CMarker::CollisionBegin(CCollider* src, CCollider* dest)
{
	if(dest->GetProfile()->channel == ECollision_Channel::Default)
	{
		m_TimeText->SetActive(false);
		m_scene->GetSceneResource()->SoundPlay("MarkerBreak");
		ChangeAnimation("MarkerBreak");
	}
}

void CMarker::CollisionEnd(CCollider* src, CCollider* dest)
{
}

void CMarker::Die()
{
	SetActive(false);
}

void CMarker::CheckBreak()
{
	m_IsBreak = true;
}
