#include "Bullet.h"
#include "TileMap.h"
#include "Tile.h"
#include "../Scene/Scene.h"
#include "../Scene/Camera.h"
#include "../Collision/ColliderBox.h"
#include "../Collision/ColliderCircle.h"

CBullet::CBullet()
	:m_distance(52.f*3.f)
	,m_damage(0.f)
{
	SetTypeID<CBullet>();
}

CBullet::CBullet(const CBullet& obj)
	:CGameObject(obj)
	, m_distance(obj.m_distance)
	, m_damage(obj.m_damage)
{
}

CBullet::~CBullet()
{
}

void CBullet::CollisionBegin(CCollider* src, CCollider* dest)
{
	if (src->GetProfile()->channel == ECollision_Channel::PlayerAttack)
	{
		if (dest->GetProfile()->channel == ECollision_Channel::Player||
			dest->GetProfile()->channel == ECollision_Channel::Event)
		{
			return;
		}
	}
	SetActive(false);
}

void CBullet::CollisionEnd(CCollider* src, CCollider* dest)
{
}

bool CBullet::Init()
{
	m_moveSpeed = 300.f;
	SetPos(900.f, 100.f);
	SetSize(20.f, 20.f);
	SetPivot(0.5f, 0.5f);
	SetTexture("Bullet", TEXT("Attack/Bullet.bmp"));
	//SetColorKey(255, 0, 255);

	CColliderCircle* circle = AddCollider<CColliderCircle>("Bullet");
	circle->SetRadius(10.f);
	circle->SetCollisionBeginFunction<CBullet>(this, &CBullet::CollisionBegin);
	circle->SetCollisionEndFunction<CBullet>(this, &CBullet::CollisionEnd);
	return true;
}

void CBullet::Update(float deltaTime)
{
	CGameObject::Update(deltaTime);
	MoveDir(m_angle);
	m_distance -= m_moveSpeed * deltaTime;
	if (m_distance <= 0.f)
	{
		SetActive(false);
	}
}

void CBullet::PostUpdate(float deltaTime)
{
	CGameObject::PostUpdate(deltaTime);
	if (m_scene->GetTileMap()->GetTile(m_pos)->GetSideCollision())
	{
		SetActive(false);
	}
}

void CBullet::Render(HDC hDC, float deltaTime)
{
	CGameObject::Render(hDC, deltaTime);
}
