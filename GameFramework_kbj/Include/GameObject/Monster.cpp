#include "Monster.h"
#include "Bullet.h"
#include "Item.h"
#include "TileMap.h"
#include "Tile.h"
#include "../Collision/ColliderBox.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"

CMonster::CMonster()
	: m_fireTime(0.f)
{
	SetTypeID<CMonster>();
	m_ColliderSize = Vector2(40.f, 40.f);
	m_OffsetSize = Vector2(0.f, 2.f);
}

CMonster::CMonster(const CMonster& obj)
	:CGameObject(obj)
	, m_fireTime(obj.m_fireTime)
{
}

CMonster::~CMonster()
{
}

bool CMonster::Init()
{
	CGameObject::Init();
	m_moveSpeed = 300.f;
	SetPos(900.f, 100.f);
	SetPivot(0.5f, 0.5f);
	CreateAnimation();
	AddAnimation("Monster1_1Right");
	AddAnimation("Monster1_1Left");
	AddAnimation("Monster1_1Die", false,0.5f);
	SetEndFunction<CMonster>("Monster1_1Die", this, &CMonster::Die);

	// 충돌체 추가
	CColliderBox* box = AddCollider<CColliderBox>("Monster");
	box->SetExtent(m_ColliderSize.x, m_ColliderSize.y);
	box->SetOffset(m_OffsetSize);
	box->SetCollisionProfile("Monster");
	box->SetCollisionBeginFunction<CMonster>(this, &CMonster::CollisionBegin);
	box->SetCollisionEndFunction<CMonster>(this, &CMonster::CollisionEnd);

	SetSideWallCheck(true);
	return true;
}

void CMonster::Update(float deltaTime)
{
	CGameObject::Update(deltaTime);
	if (CheckCurrentAnimation("Monster1_1Die"))
	{
		return;
	}
	//플레이어의 위치를 쳐다본다
	Vector2 playerPos = m_scene->GetPlayer()->GetPos();
	if (m_pos.x> playerPos.x)
	{
		ChangeAnimation("Monster1_1Left");
		playerPos = Vector2(-1, 0);
	}
	else 
	{
		ChangeAnimation("Monster1_1Right");
		playerPos = Vector2(1, 0);
	}
	//플레이어쪽으로 총알 발사
	m_fireTime += deltaTime;
	if (m_fireTime >= 1.5f)
	{
		m_fireTime -= 1.5f;
		CBullet* bullet = m_scene->CreateObject<CBullet>("MonsterBullet");
		CCollider* bulletCol = bullet->FindCollider("Bullet");
		bulletCol->SetCollisionProfile("MonsterAttack");
		float	bulletx;
		Vector2 bulletSize = bullet->GetSize();
		if(playerPos== Vector2(-1, 0))
		{
			bulletx = m_pos.x - m_pivot.x * m_size.x - (1.f - bullet->GetPivot().x) * bulletSize.x;
		}
		else
		{
			bulletx = m_pos.x + m_pivot.x * m_size.x + (1.f - bullet->GetPivot().x) * bulletSize.x;
		}
		bullet->SetColorKey(255,0,255);
		bullet->SetPos(bulletx, m_pos.y);
		bullet->SetAngle(playerPos);
		bullet->SetDistance(TILE.x*3- bulletSize.x);
	}
}

void CMonster::PostUpdate(float deltaTime)
{
	CGameObject::PostUpdate(deltaTime);
}

void CMonster::Render(HDC hDC, float deltaTime)
{
	CGameObject::Render(hDC, deltaTime);
}

void CMonster::CollisionBegin(CCollider* src, CCollider* dest)
{
	if (dest->GetProfile()->channel == ECollision_Channel::Default||
		dest->GetProfile()->channel == ECollision_Channel::PlayerAttack||
		dest->GetProfile()->channel == ECollision_Channel::MonsterAttack||
		dest->GetProfile()->channel == ECollision_Channel::Monster)
	{
		m_scene->GetSceneResource()->SoundPlay("EnemyDie");
		ChangeAnimation("Monster1_1Die");
	}
}

void CMonster::CollisionEnd(CCollider* src, CCollider* dest)
{

}

void CMonster::Die()
{
	SetActive(false);
	int random = rand() % 11;
	CItem* item = m_scene->CreateObject<CItem>("Item");
	Vector2 monsterPos = m_scene->GetTileMap()->GetTile(m_pos)->GetPos();
	item->SetPos(monsterPos + TILE * 0.5);
	if(random<3)
	{
		item->SetName("Ballon");
		item->ChangeAnimation("Item_ballon");
	}
	else if(random >=3&& random <6)
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
