#include "Item.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"
#include "../Scene/Camera.h"
#include "../Collision/ColliderBox.h"
#include "../Collision/ColliderCircle.h"

CItem::CItem()
	: m_InvisibleTime(0.f)
	, m_CanDelete(true)
{
}

CItem::CItem(const CItem& obj)
	: CGameObject(obj)
	, m_InvisibleTime(0.f)
	, m_CanDelete(true)
{
}

CItem::~CItem()
{
}

void CItem::CollisionBegin(CCollider* src, CCollider* dest)
{
	if(dest->GetProfile()->channel == ECollision_Channel::Player)
	{
		m_scene->GetSceneResource()->SoundPlay("EatItem");
		SetActive(false);
	}
	if (dest->GetProfile()->channel == ECollision_Channel::Default||
		dest->GetProfile()->channel == ECollision_Channel::PlayerAttack||
		dest->GetProfile()->channel == ECollision_Channel::MonsterAttack)
	{
		if(m_CanDelete&&m_InvisibleTime>2.f)
		{
			SetActive(false);
		}
	}
}

void CItem::CollisionEnd(CCollider* src, CCollider* dest)
{
}

bool CItem::Init()
{
	SetPivot(0.5f, 0.5f);
	CreateAnimation();
	AddAnimation("Item_potion");
	AddAnimation("Item_potionI", true, 0.1f);
	AddAnimation("Item_potion_max");
	AddAnimation("Item_potion_maxI", true, 0.1f);
	AddAnimation("Item_ballon");
	AddAnimation("Item_ballonI", true, 0.1f);
	AddAnimation("Item_skate");
	AddAnimation("Item_skateI", true, 0.1f);
	AddAnimation("Item_needle");
	AddAnimation("Item_needleI", true, 0.1f);
	AddAnimation("Item_shoes");
	AddAnimation("Item_dart");
	AddAnimation("Item_treasure");

	//m_vecSequenceKey[0].push_back("PlayerUp");
	//m_vecSequenceKey[0].push_back("PlayerInvisibleU");
	//m_vecSequenceKey[1].push_back("PlayerDown");
	//m_vecSequenceKey[1].push_back("PlayerInvisibleD");
	//m_vecSequenceKey[2].push_back("PlayerLeft");
	//m_vecSequenceKey[2].push_back("PlayerInvisibleL");
	//m_vecSequenceKey[3].push_back("PlayerRight");
	//m_vecSequenceKey[3].push_back("PlayerInvisibleR");

	// 충돌체 추가
	CColliderBox* box = AddCollider<CColliderBox>("Item");
	box->SetExtent(50.f, 50.f);
	box->SetCollisionBeginFunction<CItem>(this, &CItem::CollisionBegin);
	box->SetCollisionEndFunction<CItem>(this, &CItem::CollisionEnd);
	box->SetCollisionProfile("Item");
	return true;
}

void CItem::Update(float deltaTime)
{
	CGameObject::Update(deltaTime);
	m_InvisibleTime += deltaTime;
	if(m_InvisibleTime<2.f)
	{
		if(CheckCurrentAnimation("Item_potion"))
		{
			ChangeAnimation("Item_potionI");
		}
		else if (CheckCurrentAnimation("Item_potion_max"))
		{
			ChangeAnimation("Item_potion_maxI");
		}
		else if (CheckCurrentAnimation("Item_ballon"))
		{
			ChangeAnimation("Item_ballonI");
		}
		else if (CheckCurrentAnimation("Item_skate"))
		{
			ChangeAnimation("Item_skateI");
		}
		else if (CheckCurrentAnimation("Item_needle"))
		{
			ChangeAnimation("Item_needleI");
		}
	}
}

void CItem::PostUpdate(float deltaTime)
{
	CGameObject::PostUpdate(deltaTime);
	if (m_InvisibleTime > 2.f)
	{
		if (CheckCurrentAnimation("Item_potionI"))
		{
			ChangeAnimation("Item_potion");
		}
		else if (CheckCurrentAnimation("Item_potion_maxI"))
		{
			ChangeAnimation("Item_potion_max");
		}
		else if (CheckCurrentAnimation("Item_ballonI"))
		{
			ChangeAnimation("Item_ballon");
		}
		else if (CheckCurrentAnimation("Item_skateI"))
		{
			ChangeAnimation("Item_skate");
		}
		else if (CheckCurrentAnimation("Item_needleI"))
		{
			ChangeAnimation("Item_needle");
		}
	}
}

void CItem::Render(HDC hDC, float deltaTime)
{
	CGameObject::Render(hDC, deltaTime);
}