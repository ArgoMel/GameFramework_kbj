#include "Tornado.h"
#include "TileMap.h"
#include "Tile.h"
#include "../Scene/Scene.h"
//#include "../Scene/Camera.h"
//#include "../Collision/ColliderBox.h"
#include "../Collision/ColliderCircle.h"

CTornado::CTornado()
	:m_movespeed(350.f)
	,m_distance(600.f)
	,m_angle(180.f)
	,m_rotationangle(0.f)
	,m_range(100.f)
{
	SetTypeID<CTornado>();
}

CTornado::CTornado(const CTornado& obj)
	:CGameObject(obj)
	, m_movespeed(obj.m_movespeed)
	, m_distance(obj.m_distance)
	, m_angle(obj.m_angle)
	, m_rotationangle(obj.m_rotationangle)
	, m_range(obj.m_range)
{
}

CTornado::~CTornado()
{
}

bool CTornado::Init()
{
	SetPivot(0.5f, 0.5f);
	SetTexture("Tornado", TEXT("Attack/Tornado.bmp"));
	SetColorKey(255, 0, 255);

	CColliderCircle* circle = AddCollider<CColliderCircle>("Tornado");
	circle->SetRadius(10.f);
	circle->SetCollisionProfile("MonsterAttack");
	circle->SetCollisionBeginFunction<CTornado>(this, &CTornado::CollisionBegin);
	circle->SetCollisionEndFunction<CTornado>(this, &CTornado::CollisionEnd);
	return true;
}

void CTornado::Update(float deltaTime)
{
	CGameObject::Update(deltaTime);
	m_linepos.x = m_linepos.x + cosf(DegreeToRadian(m_angle)) * m_movespeed * deltaTime;
	m_linepos.y = m_linepos.y + sinf(DegreeToRadian(m_angle)) * m_movespeed * deltaTime;
	m_rotationangle += 1440.f * deltaTime;
	m_pos.x = m_linepos.x + cosf(DegreeToRadian(m_rotationangle)) * m_range;
	m_pos.y = m_linepos.y + sinf(DegreeToRadian(m_rotationangle)) * m_range;
	m_distance -= m_movespeed * deltaTime;
	if (m_distance <= 0.f)
	{
		SetActive(false);
	}
}

void CTornado::PostUpdate(float deltaTime)
{
	CGameObject::PostUpdate(deltaTime);
}

void CTornado::Render(HDC hDC, float deltaTime)
{
	CGameObject::Render(hDC, deltaTime);
}

void CTornado::CollisionBegin(CCollider* src, CCollider* dest)
{
	if (dest->GetOwner()->GetName() == "Seal"||
		dest->GetOwner()->GetName() == "Marker")
	{
		return;
	}
	SetActive(false);
}

void CTornado::CollisionEnd(CCollider* src, CCollider* dest)
{
}