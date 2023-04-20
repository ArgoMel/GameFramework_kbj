#include "Explosion.h"
#include "../Collision/ColliderBox.h"

CExplosion::CExplosion()
	: m_damage(1)
{
}

CExplosion::CExplosion(const CExplosion& obj)
	: CGameObject(obj)
	, m_damage(obj.m_damage)
{
}

CExplosion::~CExplosion()
{
}

bool CExplosion::Init()
{
	SetPivot(0.5f, 0.5f);
	CreateAnimation();
	AddAnimation("BossExplosion", false);
	SetEndFunction<CExplosion>("BossExplosion", this, &CExplosion::Remove);
	// 충돌체 추가
	CColliderBox* box = AddCollider<CColliderBox>("BossExplosion");
	box->SetExtent(50.f, 50.f);
	box->SetCollisionBeginFunction<CExplosion>(this, &CExplosion::CollisionBegin);
	box->SetCollisionEndFunction<CExplosion>(this, &CExplosion::CollisionEnd);
	return true;
}

void CExplosion::Update(float deltaTime)
{
	CGameObject::Update(deltaTime);
}

void CExplosion::PostUpdate(float deltaTime)
{
	CGameObject::PostUpdate(deltaTime);
}

void CExplosion::Render(HDC hDC, float deltaTime)
{
	CGameObject::Render(hDC, deltaTime);
}

void CExplosion::CollisionBegin(CCollider* src, CCollider* dest)
{
	dest->GetOwner()->InflictDamage(m_damage);
}

void CExplosion::CollisionEnd(CCollider* src, CCollider* dest)
{
}

void CExplosion::Remove()
{
	SetActive(false);
}