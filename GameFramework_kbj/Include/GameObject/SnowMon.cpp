#include "SnowMon.h"
#include "Item.h"
#include "TileMap.h"
#include "Tile.h"
#include "Effect.h"
#include "Bomb.h"
#include "../Collision/ColliderCircle.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"

CSnowMon::CSnowMon()
	: m_ChangeTime(0.5f)
	, m_MonsterDir(1)
{
	SetTypeID<CSnowMon>();
	m_ColliderSize = Vector2(20.f, 20.f);
	//m_OffsetSize = Vector2(0.f, 2.f);
}

CSnowMon::CSnowMon(const CSnowMon& obj)
	:CGameObject(obj)
	, m_ChangeTime(0.5f)
	, m_MonsterDir(obj.m_MonsterDir)
{
}

CSnowMon::~CSnowMon()
{
}

bool CSnowMon::Init()
{
	CGameObject::Init();
	m_moveSpeed = 300.f;
	SetPos(900.f, 100.f);
	SetPivot(0.5f, 0.5f);
	CreateAnimation();
	AddAnimation("SnowMonU");
	AddAnimation("SnowMonD");
	AddAnimation("SnowMonR");
	AddAnimation("SnowMonL");
	AddAnimation("SnowMonDie", false, 0.5f);
	SetEndFunction<CSnowMon>("SnowMonDie", this, &CSnowMon::Die);

	m_vecSequenceKey[0].push_back("SnowMonU");
	m_vecSequenceKey[1].push_back("SnowMonD");
	m_vecSequenceKey[2].push_back("SnowMonL");
	m_vecSequenceKey[3].push_back("SnowMonR");

	// 충돌체 추가
	CColliderCircle* circle = AddCollider<CColliderCircle>("SnowMon");
	circle->SetRadius(m_ColliderSize.x);
	circle->SetCollisionProfile("Monster");
	circle->SetCollisionBeginFunction<CSnowMon>(this, &CSnowMon::CollisionBegin);
	circle->SetCollisionEndFunction<CSnowMon>(this, &CSnowMon::CollisionEnd);

	SetSideWallCheck(true);
	return true;
}

void CSnowMon::Update(float deltaTime)
{
	CGameObject::Update(deltaTime);
	deltaTime *= m_timeScale;
	m_ChangeTime += deltaTime;
	if (CheckCurrentAnimation("SnowMonDie"))
	{
		return;
	}
	m_PlayerPos = m_scene->GetPlayer()->GetPos();
	Vector2 absolutePos = m_PlayerPos - m_pos;
	if (m_ChangeTime >= 0.5f)
	{
		m_ChangeTime = 0;
		if (absolutePos.x > 0)
		{
			if (absolutePos.x < absolutePos.y)
			{
				m_MonsterDir = (int)Direction::Down;
				m_dir = Vector2(0, 1);
			}
			else if (absolutePos.x < -absolutePos.y)
			{
				m_MonsterDir = (int)Direction::Up;
				m_dir = Vector2(0, -1);
			}
			else
			{
				m_MonsterDir = (int)Direction::Right;
				m_dir = Vector2(1, 0);
			}
		}
		else
		{
			if (-absolutePos.x < absolutePos.y)
			{
				m_MonsterDir = (int)Direction::Down;
				m_dir = Vector2(0, 1);
			}
			else if (-absolutePos.x < -absolutePos.y)
			{
				m_MonsterDir = (int)Direction::Up;
				m_dir = Vector2(0, -1);
			}
			else
			{
				m_MonsterDir = (int)Direction::Left;
				m_dir = Vector2(-1, 0);
			}
		}
		ChangeAnimation(m_vecSequenceKey[m_MonsterDir][0]);
	}
	Move(m_dir * 13);
}

void CSnowMon::PostUpdate(float deltaTime)
{
	CGameObject::PostUpdate(deltaTime);
}

void CSnowMon::Render(HDC hDC, float deltaTime)
{
	CGameObject::Render(hDC, deltaTime);
}

void CSnowMon::CollisionBegin(CCollider* src, CCollider* dest)
{
	if (dest->GetProfile()->channel == ECollision_Channel::Default ||
		dest->GetProfile()->channel == ECollision_Channel::PlayerAttack ||
		dest->GetProfile()->channel == ECollision_Channel::MonsterAttack ||
		dest->GetProfile()->channel == ECollision_Channel::Monster)
	{
		m_scene->GetSceneResource()->SoundPlay("EnemyDie");
		ChangeAnimation("SnowMonDie");
	}
}

void CSnowMon::CollisionEnd(CCollider* src, CCollider* dest)
{
}

void CSnowMon::Die()
{
	SetActive(false);
	CBomb* bomb = m_scene->CreateObject<CBomb>("Bomb");
	Vector2 tilePos = m_scene->GetTileMap()->GetTile(m_pos)->GetPos();
	bomb->SetPos(tilePos + TILE * 0.5f);
	bomb->SetDistance(5);
	bomb->Explosion();

	int random = rand() % 11;
	CItem* item = m_scene->CreateObject<CItem>("Item");
	Vector2 monsterPos = m_scene->GetTileMap()->GetTile(m_pos)->GetPos();
	item->SetPos(monsterPos + TILE * 0.5);
	if (random < 3)
	{
		item->SetName("Ballon");
		item->ChangeAnimation("Item_ballon");
	}
	else if (random >= 3 && random < 6)
	{
		item->SetName("Potion");
		item->ChangeAnimation("Item_potion");
	}
	else if (random >= 6 && random < 9)
	{
		item->SetName("Skate");
		item->ChangeAnimation("Item_skate");
	}
	else if (random == 9)
	{
		item->SetName("PotionMax");
		item->ChangeAnimation("Item_potion_max");
	}
	else
	{
		item->SetName("Needle");
		item->ChangeAnimation("Item_needle");
	}
}
