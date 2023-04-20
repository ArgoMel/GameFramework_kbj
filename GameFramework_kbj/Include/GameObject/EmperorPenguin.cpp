#include "EmperorPenguin.h"
#include "Item.h"
#include "Effect.h"
#include "Marker.h"
#include "TileMap.h"
#include "Tile.h"
#include "SnowMon.h"
#include "BombExplosion.h"
#include "GuidedExplosion.h"
#include "Flash.h"
#include "../Collision/ColliderCircle.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"
#include "../Widget/CharacterHUD.h"
#include "../Widget/WidgetComponent.h"
#include "../Widget/Text.h"
#include "../Widget/ProgressBar.h"
constexpr auto CHARGEMAXTIME = 3.f;

CEmperorPenguin::CEmperorPenguin()
	: m_InvisibleTime(1.f)
	, m_ChangeTime(0.5f)
	, m_ChargeTime(0.f)
	, m_DuringTime(0.f)
	, m_PatternDelay(0.f)
	, m_fireCount(0)
	, m_HPMax(100)
	, m_BossDir(1)
	, m_MarkerCount(0)
	, m_ExplosionCount(1)
	, m_IsPattern(false)
{
	SetTypeID<CEmperorPenguin>();
	m_HP = m_HPMax;
	m_ColliderSize = Vector2(40.f, 40.f);
	m_OffsetSize = Vector2(0.f, 5.f);
}

CEmperorPenguin::CEmperorPenguin(const CEmperorPenguin& obj)
	:CGameObject(obj)
	, m_InvisibleTime(obj.m_InvisibleTime)
	, m_ChangeTime(0.5f)
	, m_ChargeTime(0.f)
	, m_DuringTime(0.f)
	, m_PatternDelay(0.f)
	, m_fireCount(obj.m_fireCount)
	, m_HPMax(obj.m_HPMax)
	, m_HP(obj.m_HPMax)
	, m_BossDir(1)
	, m_MarkerCount(0)
	, m_ExplosionCount(1)
	, m_IsPattern(false)
{
}

CEmperorPenguin::~CEmperorPenguin()
{
}

bool CEmperorPenguin::Init()
{
	CGameObject::Init();
	m_moveSpeed = 300.f;
	m_dir = Vector2(0.f, 1.f);
	SetPos(START_TILE.x + TILE.x * 7, START_TILE.y + TILE.y * 2);
	SetPivot(0.5f, 0.5f);
	CreateAnimation();
	AddAnimation("PenguinD");
	AddAnimation("PenguinU");
	AddAnimation("PenguinR");
	AddAnimation("PenguinL");
	AddAnimation("PenguinDie", false, 1.5f);
	AddAnimation("PenguinUInvisible", true, 0.1f);
	AddAnimation("PenguinDInvisible", true, 0.1f);
	AddAnimation("PenguinLInvisible", true, 0.1f);
	AddAnimation("PenguinRInvisible", true, 0.1f);
	AddAnimation("PenguinCInvisible", true, 0.1f);
	AddAnimation("PenguinSInvisible", true, 0.1f);
	AddAnimation("PenguinCharge", true, 0.3f);
	AddAnimation("PenguinStun", true, 0.3f);
	SetEndFunction<CEmperorPenguin>("PenguinDie", this, &CEmperorPenguin::Die);
	AddNotify<CEmperorPenguin>("PenguinDie", 3, this, &CEmperorPenguin::DieSound);

	m_vecSequenceKey[0].push_back("PenguinU");
	m_vecSequenceKey[0].push_back("PenguinUInvisible");
	m_vecSequenceKey[1].push_back("PenguinD");
	m_vecSequenceKey[1].push_back("PenguinDInvisible");
	m_vecSequenceKey[2].push_back("PenguinL");
	m_vecSequenceKey[2].push_back("PenguinLInvisibles");
	m_vecSequenceKey[3].push_back("PenguinR");
	m_vecSequenceKey[3].push_back("PenguinRInvisible");

	m_Circle = AddCollider<CColliderCircle>("Penguin");
	m_Circle->SetRadius(m_ColliderSize.x);
	m_Circle->SetOffset(m_OffsetSize);
	m_Circle->SetCollisionProfile("Monster");
	m_Circle->SetCollisionBeginFunction<CEmperorPenguin>(this, &CEmperorPenguin::CollisionBegin);
	m_Circle->SetCollisionEndFunction<CEmperorPenguin>(this, &CEmperorPenguin::CollisionEnd);

	m_HPBar = CreateWidgetComponent<CProgressBar>("BossHP");
	m_HPBar->GetWidget<CProgressBar>()->SetTexture(EProgressBar_Texture_Type::Bar, "BossHP", TEXT("CharacterHPBar.bmp"));
	m_HPBar->GetWidget<CProgressBar>()->SetSize(75.f, 10.f);
	m_HPBar->SetPos(-40.f, -55.f);

	m_nameBar = CreateWidgetComponent<CText>("NameBar");
	m_nameBar->GetWidget<CText>()->SetText(TEXT("È²Á¦Æë±Ï"));
	m_nameBar->GetWidget<CText>()->EnableShadow(true);
	m_nameBar->GetWidget<CText>()->SetTextColor(255, 0, 0);
	m_nameBar->GetWidget<CText>()->SetTextShadowColor(255, 240, 240);
	m_nameBar->GetWidget<CText>()->SetShadowOffset(2.f, 1.5f);
	m_nameBar->SetPos(-42.f, -80.f);

	SetSideWallCheck(true);
	return true;
}

void CEmperorPenguin::Update(float deltaTime)
{
	CGameObject::Update(deltaTime);
	deltaTime *= m_timeScale;
	if (CheckCurrentAnimation("PenguinDie"))
	{
		m_scene->GetPlayer()->SetTimeScale(1.f);
		return;
	}
	m_PatternDelay += deltaTime;
	m_ChangeTime += deltaTime;
	m_ChargeTime += deltaTime;
	m_InvisibleTime += deltaTime;
	m_DuringTime += deltaTime;
	{
		auto	iter = m_listMarker.begin();
		auto	iterEnd = m_listMarker.end();
		for (; iter != iterEnd;)
		{
			if ((*iter)->GetIsBreak())
			{
				iter = m_listMarker.erase(iter);
				++m_MarkerCount;
				if (m_MarkerCount > 3)
				{
					m_PatternDelay = 0;
					m_scene->GetSceneResource()->SoundPlay("BossStun");
					ChangeAnimation("PenguinStun");
				}
				continue;
			}
			++iter;
		}
	}
	auto	iter = m_listMonster.begin();
	auto	iterEnd = m_listMonster.end();
	for (; iter != iterEnd;)
	{
		if (!(*iter)->GetActive())
		{
			iter = m_listMonster.erase(iter);
			continue;
		}
		++iter;
	}
	if(m_DuringTime>=5.f)
	{
		m_scene->GetPlayer()->SetTimeScale(1.f);
	}
	if (CheckCurrentAnimation("PenguinStun") || CheckCurrentAnimation("PenguinSInvisible"))
	{
		if (m_PatternDelay > 4.f)
		{
			Recovery();
			return;
		}
		if (m_InvisibleTime < 1.f)
		{
			ChangeAnimation("PenguinSInvisible");
		}
		else
		{
			ChangeAnimation("PenguinStun");
		}
		return;
	}
	if (CheckCurrentAnimation("PenguinCharge") || CheckCurrentAnimation("PenguinCInvisible"))
	{
		if (m_ChargeTime > CHARGEMAXTIME && m_MarkerCount < 4)
		{
			Recovery();		//¾ê°¡ ¸ÕÀú¿Í¾ß ÀÌ ÄÚµå°¡ 1¹ø¸¸ ½ÇÇàµÊ
			EXPattern();
			return;
		}
		if (m_InvisibleTime < 1.f)
		{
			ChangeAnimation("PenguinCInvisible");
		}
		else
		{
			ChangeAnimation("PenguinCharge");
		}
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
				m_BossDir = (int)Direction::Down;
				m_dir = Vector2(0, 1);
			}
			else if (absolutePos.x < -absolutePos.y)
			{
				m_BossDir = (int)Direction::Up;
				m_dir = Vector2(0, -1);
			}
			else
			{
				m_BossDir = (int)Direction::Right;
				m_dir = Vector2(1, 0);
			}
		}
		else
		{
			if (-absolutePos.x < absolutePos.y)
			{
				m_BossDir = (int)Direction::Down;
				m_dir = Vector2(0, 1);
			}
			else if (-absolutePos.x < -absolutePos.y)
			{
				m_BossDir = (int)Direction::Up;
				m_dir = Vector2(0, -1);
			}
			else
			{
				m_BossDir = (int)Direction::Left;
				m_dir = Vector2(-1, 0);
			}
		}
		if (m_InvisibleTime < 1.f)
		{
			ChangeAnimation(m_vecSequenceKey[m_BossDir][1]);
		}
		else
		{
			ChangeAnimation(m_vecSequenceKey[m_BossDir][0]);
		}
	}
	if (m_PatternDelay >= 4.f)
	{
		m_ChangeTime = -0.5f;
		m_IsPattern = true;
		m_PatternDelay = 0;
		if (++m_fireCount == 4)
		{
			m_ChargeTime = 0;
			ChangeAnimation("PenguinCharge");
			CMarker* marker = m_scene->CreateObject<CMarker>("Marker");
			marker->SetPos(m_pos.x, m_pos.y + m_pivot.y * m_size.y);
			marker->SetTime(CHARGEMAXTIME);
			m_listMarker.push_back(marker);
			marker = m_scene->CreateObject<CMarker>("Marker");
			marker->SetPos(m_pos.x, m_pos.y - m_pivot.y * m_size.y);
			marker->SetTime(CHARGEMAXTIME);
			m_listMarker.push_back(marker);
			marker = m_scene->CreateObject<CMarker>("Marker");
			marker->SetPos(m_pos.x + m_pivot.x * m_size.x, m_pos.y);
			marker->SetTime(CHARGEMAXTIME);
			m_listMarker.push_back(marker);
			marker = m_scene->CreateObject<CMarker>("Marker");
			marker->SetPos(m_pos.x - m_pivot.x * m_size.x, m_pos.y);
			marker->SetTime(CHARGEMAXTIME);
			m_listMarker.push_back(marker);
			return;
		}
		int random = rand() % 3;
		m_Warning = m_scene->CreateObject<CEffect>("HitEffect");
		if (random == 0)
		{
			m_Warning->SetPos(m_pos);
			m_Warning->SetEndFunction<CEmperorPenguin>("Warning", this, &CEmperorPenguin::TrippleExplosion);
		}
		else if (random == 1 && m_listMonster.size() < 4)
		{
			Vector2 tilePos = m_scene->GetTileMap()->GetTile(m_PlayerPos)->GetPos();
			m_RealSkillPos = tilePos + TILE * 0.5f;
			m_Warning->SetPos(m_RealSkillPos);
			m_Warning->SetEndFunction<CEmperorPenguin>("Warning", this, &CEmperorPenguin::Summon);
		}
		else
		{
			Vector2 tilePos = m_scene->GetTileMap()->GetTile(m_PlayerPos)->GetPos();
			m_RealSkillPos = tilePos + TILE * 0.5f;
			m_Warning->SetPos(m_RealSkillPos);
			m_Warning->SetEndFunction<CEmperorPenguin>("Warning", this, &CEmperorPenguin::GuidedExplosion);
		}
		return;
	}
	if (!m_IsPattern)
	{
		Move(m_dir * 13);
	}
}

void CEmperorPenguin::PostUpdate(float deltaTime)
{
	CGameObject::PostUpdate(deltaTime);
}

void CEmperorPenguin::Render(HDC hDC, float deltaTime)
{
	CGameObject::Render(hDC, deltaTime);
}

float CEmperorPenguin::InflictDamage(float damage)
{
	if (m_InvisibleTime < 1.f)
	{
		return 0;
	}
	damage = CGameObject::InflictDamage(damage);
	if (CheckCurrentAnimation("PenguinStun"))
	{
		damage = 25.f;
		Recovery();
	}
	m_HP -= (int)damage;
	m_scene->FindWidgetWindow<CCharacterHUD>("CharacterHUD")->SetHP(m_HP / (float)m_HPMax);
	m_HPBar->GetWidget<CProgressBar>()->SetValue(m_HP / (float)m_HPMax);
	if (m_HP <= 0)
	{
		m_Circle->SetActive(false);
		m_scene->GetSceneResource()->SoundPlay("BossDie");
		ChangeAnimation("PenguinDie");
		return damage;
	}
	m_scene->GetSceneResource()->SoundPlay("PenguinHit");
	m_InvisibleTime = 0;
	return damage;
}

void CEmperorPenguin::CollisionBegin(CCollider* src, CCollider* dest)
{
}

void CEmperorPenguin::CollisionEnd(CCollider* src, CCollider* dest)
{
}

void CEmperorPenguin::Die()
{
	SetActive(false);
	m_HPBar->SetActive(false);
	m_nameBar->SetActive(false);
	CItem* item = m_scene->CreateObject<CItem>("Treasure");
	Vector2 monsterPos = m_scene->GetTileMap()->GetTile(m_pos)->GetPos();
	item->SetPos(monsterPos + TILE * 0.5);
	item->ChangeAnimation("Item_treasure");
	item->SetCanDelete(false);
}

void CEmperorPenguin::DieSound()
{
	m_scene->GetSceneResource()->SoundPlay("EnemyDie");
}

void CEmperorPenguin::Recovery()
{
	ChangeAnimation("PenguinDInvisible");
	m_InvisibleTime = 0.f;
	m_MarkerCount = 0;
	m_PatternDelay = 0.f;
	m_fireCount = 0;
}

void CEmperorPenguin::TrippleExplosion()
{
	m_Warning->SetActive(false);
	m_scene->GetSceneResource()->SoundPlay("Bomb_wave");
	CTileMap* tileMap = m_scene->GetTileMap();
	Vector2 LT = m_pos - m_pivot * m_size;
	Vector2 RB = LT + m_size;
	int startIndexX = tileMap->GetTileIndexX(LT.x)- m_ExplosionCount;
	startIndexX = startIndexX < 1 ? 1 : startIndexX;
	int startIndexY = tileMap->GetTileIndexY(LT.y)- m_ExplosionCount;
	startIndexY = startIndexY < 1 ? 1 : startIndexY;
	int endIndexX = tileMap->GetTileIndexX(RB.x)+ m_ExplosionCount;
	endIndexX = endIndexX > tileMap->GetCountX() - 2 ? tileMap->GetCountX() - 2 : endIndexX;
	int endIndexY = tileMap->GetTileIndexY(RB.y)+ m_ExplosionCount;
	endIndexY = endIndexY > tileMap->GetCountY() - 2 ? tileMap->GetCountY() - 2 : endIndexY;
	int indexY = startIndexY;
	for (; indexY <= endIndexY; ++indexY)
	{
		int indexX = startIndexX;
		for (; indexX <= endIndexX; ++indexX)
		{
			Vector2 tilePos = tileMap->GetTile(indexX, indexY)->GetPos();
			if (tileMap->GetTile(indexX, indexY)->GetSideCollision())
			{
				continue;
			}
			if(indexX== startIndexX|| indexY== startIndexY|| indexX == endIndexX || indexY == endIndexY)
			{
				CBombExplosion* explosion = m_scene->CreateObject<CBombExplosion>("Explosion");
				explosion->SetPos(tilePos + TILE * 0.5f);
			}
		}
	}
	if(m_ExplosionCount<5)
	{
		m_ExplosionCount+=2;
		m_Warning = m_scene->CreateObject<CEffect>("HitEffect");
		m_Warning->SetPos(m_pos);
		m_Warning->SetEndFunction<CEmperorPenguin>("Warning", this, &CEmperorPenguin::TrippleExplosion);
	}
	else
	{
		m_PatternDelay = 1.f;
		m_IsPattern = false;
		m_ExplosionCount = 1;
	}
}

void CEmperorPenguin::Summon()
{
	m_Warning->SetActive(false);
	m_IsPattern = false;
	bool IsSummon = false;
	auto	iter = m_listMonster.begin();
	auto	iterEnd = m_listMonster.end();
	if (!m_scene->GetTileMap()->GetTile(m_RealSkillPos)->GetSideCollision())
	{
		IsSummon = true;
		for (; iter != iterEnd; ++iter)
		{
			if (m_scene->GetTileMap()->GetTileIndex((*iter)->GetPos()) == m_scene->GetTileMap()->GetTileIndex(m_RealSkillPos))
			{
				IsSummon = false;
				break;
			}
		}
	}
	if (IsSummon)
	{
		m_scene->GetSceneResource()->SoundPlay("EnemySummon");
		CSnowMon* monster = m_scene->CreateObject<CSnowMon>("SnowMon");
		monster->SetPos(m_RealSkillPos);
		m_listMonster.push_back(monster);
		IsSummon = false;
	}
	else
	{
		m_scene->GetSceneResource()->SoundPlay("EnemySummonError");
	}
}

void CEmperorPenguin::GuidedExplosion()
{
	m_Warning->SetActive(false);
	m_IsPattern = false;
	CGuidedExplosion* explosion = m_scene->CreateObject<CGuidedExplosion>("GuidedExplosion");
	explosion->SetPos(m_RealSkillPos);
}

void CEmperorPenguin::EXPattern()
{
	m_Warning->SetActive(false);
	m_IsPattern = false;
	m_scene->GetSceneResource()->SoundPlay("Freeze");
	CFlash* flash = m_scene->CreateObject<CFlash>("Flash");
	m_DuringTime = 0;
	m_scene->GetPlayer()->SetTimeScale(0.3f);
}