#include "Gamgyul_E.h"
#include "Item.h"
#include "TileMap.h"
#include "Tile.h"
#include "Effect.h"
//#include "Wall.h"
#include "../Collision/ColliderCircle.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"

CGamgyul_E::CGamgyul_E()
	: m_IsPlayer(false)
	, m_ChangeTime(0.5f)
	, m_GamgyulDir(1)
{
	SetTypeID<CGamgyul_E>();
	m_ColliderSize = Vector2(20.f, 20.f);
	//m_OffsetSize = Vector2(0.f, 2.f);
}

CGamgyul_E::CGamgyul_E(const CGamgyul_E& obj)
	:CGameObject(obj)
	, m_IsPlayer(false)
	, m_ChangeTime(0.5f)
	, m_GamgyulDir(obj.m_GamgyulDir)
{
}

CGamgyul_E::~CGamgyul_E()
{
}

bool CGamgyul_E::Init()
{
	CGameObject::Init();
	m_moveSpeed = 300.f;
	SetPos(900.f, 100.f);
	SetPivot(0.5f, 0.5f);
	CreateAnimation();
	AddAnimation("GamgyulU");
	AddAnimation("GamgyulD");
	AddAnimation("GamgyulR");
	AddAnimation("GamgyulL");
	AddAnimation("GamgyulDie", false, 0.5f);
	SetEndFunction<CGamgyul_E>("GamgyulDie", this, &CGamgyul_E::Die);

	m_vecSequenceKey[0].push_back("GamgyulU");
	m_vecSequenceKey[1].push_back("GamgyulD");
	m_vecSequenceKey[2].push_back("GamgyulL");
	m_vecSequenceKey[3].push_back("GamgyulR");

	// 충돌체 추가
	CColliderCircle* circle = AddCollider<CColliderCircle>("Gamgyul_E");
	circle->SetRadius(m_ColliderSize.x);
	circle->SetCollisionProfile("Monster");
	circle->SetCollisionBeginFunction<CGamgyul_E>(this, &CGamgyul_E::CollisionBegin);
	circle->SetCollisionEndFunction<CGamgyul_E>(this, &CGamgyul_E::CollisionEnd);

	SetSideWallCheck(true);
	return true;
}

void CGamgyul_E::Update(float deltaTime)
{
	CGameObject::Update(deltaTime);
	deltaTime *= m_timeScale;
	m_ChangeTime += deltaTime;
	if (CheckCurrentAnimation("GamgyulDie"))
	{
		return;
	}
	//플레이어의 위치를 쳐다본다
	m_PlayerPos = m_scene->GetPlayer()->GetPos();
	Vector2 absolutePos = m_PlayerPos - m_pos;
	if (m_ChangeTime >= 0.5f)
	{
		m_ChangeTime = 0;
		if (absolutePos.x > 0)
		{
			if (absolutePos.x < absolutePos.y)
			{
				m_GamgyulDir = (int)Direction::Down;
				m_dir = Vector2(0, 1);
			}
			else if (absolutePos.x < -absolutePos.y)
			{
				m_GamgyulDir = (int)Direction::Up;
				m_dir = Vector2(0, -1);
			}
			else
			{
				m_GamgyulDir = (int)Direction::Right;
				m_dir = Vector2(1, 0);
			}
		}
		else
		{
			if (-absolutePos.x < absolutePos.y)
			{
				m_GamgyulDir = (int)Direction::Down;
				m_dir = Vector2(0, 1);
			}
			else if (-absolutePos.x < -absolutePos.y)
			{
				m_GamgyulDir = (int)Direction::Up;
				m_dir = Vector2(0, -1);
			}
			else
			{
				m_GamgyulDir = (int)Direction::Left;
				m_dir = Vector2(-1, 0);
			}
		}
		ChangeAnimation(m_vecSequenceKey[m_GamgyulDir][0]);
	}
	CTileMap* tileMap = m_scene->GetTileMap();
	Vector2 playerTilePos = tileMap->GetTile(m_PlayerPos)->GetPos();
	Vector2 LT = m_pos - m_pivot * m_size;
	Vector2 RB = LT + m_size;
	int startIndexX = tileMap->GetTileIndexX(LT.x) - 3;
	startIndexX = startIndexX < 0 ? 0 : startIndexX;
	int startIndexY = tileMap->GetTileIndexY(LT.y) - 2;
	startIndexY = startIndexY < 0 ? 0 : startIndexY;
	int endIndexX = tileMap->GetTileIndexX(RB.x) + 3;
	endIndexX = endIndexX > tileMap->GetCountX() - 1 ? tileMap->GetCountX() - 1 : endIndexX;
	int endIndexY = tileMap->GetTileIndexY(RB.y) + 2;
	endIndexY = endIndexY > tileMap->GetCountY() - 1 ? tileMap->GetCountY() - 1 : endIndexY;
	for (startIndexY; startIndexY <= endIndexY; ++startIndexY)
	{
		int indexX = startIndexX;
		for (; indexX <= endIndexX; ++indexX)
		{
			Vector2 tilePos = tileMap->GetTile(indexX, startIndexY)->GetPos();
			if(tilePos== playerTilePos)
			{
				if(!m_IsPlayer)
				{
					m_Effect = m_scene->CreateObject<CEffect>("Exclamation_mark");
					m_Effect->ChangeAnimation("Exclamation_mark");
					m_Effect->SetPos(LT);
					m_Effect->SetEndFunction<CGamgyul_E>("Exclamation_mark", this, &CGamgyul_E::DeleteEffect);
				}
				m_IsPlayer = true;
				break;
			}
		}
		if(m_IsPlayer)
		{
			break;
		}
	}
	//보는 방향에 벽이 있으면 방향을 전환한다
	if(tileMap->GetTile(m_pos+m_dir*TILE)->GetSideCollision())
	{
		m_ChangeTime = 0.f;
		float temp= m_dir.x;
		m_dir.x= m_dir.y;
		m_dir.y= temp;
	}
	if (!m_IsPlayer)
	{
		Move(m_dir * 13);
	}
	else
	{
		Move(m_dir * 104);
	}
}

void CGamgyul_E::PostUpdate(float deltaTime)
{
	CGameObject::PostUpdate(deltaTime);
}

void CGamgyul_E::Render(HDC hDC, float deltaTime)
{
	CGameObject::Render(hDC, deltaTime);
}

void CGamgyul_E::CollisionBegin(CCollider* src, CCollider* dest)
{
	if (dest->GetProfile()->channel == ECollision_Channel::Default ||
		dest->GetProfile()->channel == ECollision_Channel::PlayerAttack ||
		dest->GetProfile()->channel == ECollision_Channel::MonsterAttack ||
		dest->GetProfile()->channel == ECollision_Channel::Monster)
	{
		m_scene->GetSceneResource()->SoundPlay("EnemyDie");
		ChangeAnimation("GamgyulDie");
	}
}

void CGamgyul_E::CollisionEnd(CCollider* src, CCollider* dest)
{
}

void CGamgyul_E::Die()
{
	SetActive(false);
	if(m_Effect)
	{
		m_Effect->SetActive(false);
	}
	int random = rand() % 11;
	CItem* item = m_scene->CreateObject<CItem>("Item");
	Vector2 monsterPos = m_scene->GetTileMap()->GetTile(m_pos)->GetPos();
	item->SetPos(monsterPos+TILE*0.5);
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

void CGamgyul_E::DeleteEffect()
{
	m_Effect->SetActive(false);
	m_IsPlayer = false;
}
