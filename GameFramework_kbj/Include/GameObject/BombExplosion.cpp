#include "BombExplosion.h"
#include "../Collision/ColliderBox.h"

CBombExplosion::CBombExplosion()
	: m_damage(1)
{
}

CBombExplosion::CBombExplosion(const CBombExplosion& obj)
	: CGameObject(obj)
	, m_damage(obj.m_damage)
{
}

CBombExplosion::~CBombExplosion()
{
}

bool CBombExplosion::Init()
{
	SetPivot(0.5f, 0.5f);
	CreateAnimation();
	AddAnimation("ExplosionCenter",false, 0.6f);
	AddAnimation("ExplosionDown1",false,  0.6f);
	AddAnimation("ExplosionDown2",false,  0.6f);
	AddAnimation("ExplosionUp1",false,	  0.6f);
	AddAnimation("ExplosionUp2",false,	  0.6f);
	AddAnimation("ExplosionRight1",false, 0.6f);
	AddAnimation("ExplosionRight2",false, 0.6f);
	AddAnimation("ExplosionLeft1",false,  0.6f);
	AddAnimation("ExplosionLeft2",false,  0.6f);
	SetEndFunction<CBombExplosion>("ExplosionCenter", this, &CBombExplosion::Remove);
	SetEndFunction<CBombExplosion>("ExplosionDown1", this, &CBombExplosion::Remove);
	SetEndFunction<CBombExplosion>("ExplosionDown2", this, &CBombExplosion::Remove);
	SetEndFunction<CBombExplosion>("ExplosionUp1", this, &CBombExplosion::Remove);
	SetEndFunction<CBombExplosion>("ExplosionUp2", this, &CBombExplosion::Remove);
	SetEndFunction<CBombExplosion>("ExplosionRight1", this, &CBombExplosion::Remove);
	SetEndFunction<CBombExplosion>("ExplosionRight2", this, &CBombExplosion::Remove);
	SetEndFunction<CBombExplosion>("ExplosionLeft1", this, &CBombExplosion::Remove);
	SetEndFunction<CBombExplosion>("ExplosionLeft2", this, &CBombExplosion::Remove);
	// 충돌체 추가
	CColliderBox* box = AddCollider<CColliderBox>("Explosion");
	box->SetExtent(50.f, 50.f);
	box->SetCollisionBeginFunction<CBombExplosion>(this, &CBombExplosion::CollisionBegin);
	box->SetCollisionEndFunction<CBombExplosion>(this, &CBombExplosion::CollisionEnd);
	return true;
}

void CBombExplosion::Update(float deltaTime)
{
	CGameObject::Update(deltaTime);
}

void CBombExplosion::PostUpdate(float deltaTime)
{
	CGameObject::PostUpdate(deltaTime);
}

void CBombExplosion::Render(HDC hDC, float deltaTime)
{
	CGameObject::Render(hDC, deltaTime);
}

void CBombExplosion::CollisionBegin(CCollider* src, CCollider* dest)
{
	dest->GetOwner()->InflictDamage(m_damage);
}

void CBombExplosion::CollisionEnd(CCollider* src, CCollider* dest)
{
}

void CBombExplosion::Remove()
{
	SetActive(false);
}
