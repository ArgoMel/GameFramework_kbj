#include "Boss.h"
#include "Bomb.h"
#include "Monster.h"
#include "Item.h"
#include "Explosion.h"
#include "Effect.h"
#include "Marker.h"
#include "BombExplosion.h"
#include "TileMap.h"
#include "Tile.h"
#include "../Collision/ColliderCircle.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"
#include "../Widget/CharacterHUD.h"
#include "../Widget/WidgetComponent.h"
#include "../Widget/Text.h"
#include "../Widget/ProgressBar.h"

CBoss::CBoss()
	: m_InvisibleTime(1.f)
	, m_ChangeTime(0.5f)
	, m_ChargeTime(0.f)
	, m_PatternDelay(0.f)
	, m_fireCount(0)
	, m_HPMax(100)
	, m_BossDir(1)
	, m_IsMarkerBreak(false)
	, m_IsPattern(false)
{
	SetTypeID<CBoss>();
	m_HP = m_HPMax;
	m_ColliderSize = Vector2(30.f, 30.f);
	m_OffsetSize = Vector2(-2.f, 4.f);
}

CBoss::CBoss(const CBoss& obj)
	:CCharacter(obj)
	, m_InvisibleTime(obj.m_InvisibleTime)
	, m_ChangeTime(0.5f)
	, m_ChargeTime(0.f)
	, m_PatternDelay(0.f)
	, m_fireCount(obj.m_fireCount)
	, m_HPMax(obj.m_HPMax)
	, m_HP(obj.m_HPMax)
	, m_BossDir(1)
	, m_IsMarkerBreak(false)
	, m_IsPattern(false)
{
}

CBoss::~CBoss()
{
}

void CBoss::CollisionBegin(CCollider* src, CCollider* dest)
{
}

void CBoss::CollisionEnd(CCollider* src, CCollider* dest)
{
	
}

bool CBoss::Init()
{
	CCharacter::Init();
	m_moveSpeed = 300.f;
	m_dir = Vector2(0.f, 1.f);
	SetPos(START_TILE.x+ TILE.x*7, START_TILE.y + TILE.y);
	SetPivot(0.5f, 0.5f);
	CreateAnimation();
	AddAnimation("Boss_Down");
	AddAnimation("Boss_Up");
	AddAnimation("Boss_Right");
	AddAnimation("Boss_Left");
	AddAnimation("Boss_Die", false,1.5f);
	AddAnimation("Boss_InvisibleU", true, 0.1f);
	AddAnimation("Boss_InvisibleD", true, 0.1f);
	AddAnimation("Boss_InvisibleL", true, 0.1f);
	AddAnimation("Boss_InvisibleR", true, 0.1f);
	AddAnimation("Boss_InvisibleC", true, 0.1f);
	AddAnimation("Boss_InvisibleS", true, 0.1f);
	AddAnimation("Boss_Charge", true, 0.3f);
	AddAnimation("Boss_Stun", true, 0.3f);
	SetEndFunction<CBoss>("Boss_Die", this, &CBoss::Die);
	AddNotify<CBoss>("Boss_Die", 5, this, &CBoss::DieSound);

	m_vecSequenceKey[0].push_back("Boss_Up");
	m_vecSequenceKey[0].push_back("Boss_InvisibleU");
	m_vecSequenceKey[1].push_back("Boss_Down");
	m_vecSequenceKey[1].push_back("Boss_InvisibleD");
	m_vecSequenceKey[2].push_back("Boss_Left");
	m_vecSequenceKey[2].push_back("Boss_InvisibleL");
	m_vecSequenceKey[3].push_back("Boss_Right");
	m_vecSequenceKey[3].push_back("Boss_InvisibleR");

	m_Circle = AddCollider<CColliderCircle>("Octopus");
	m_Circle->SetRadius(m_ColliderSize.x);
	m_Circle->SetOffset(m_OffsetSize);
	m_Circle->SetCollisionProfile("Monster");
	m_Circle->SetCollisionBeginFunction<CBoss>(this, &CBoss::CollisionBegin);
	m_Circle->SetCollisionEndFunction<CBoss>(this, &CBoss::CollisionEnd);

	m_HPBar = CreateWidgetComponent<CProgressBar>("BossHP");
	m_HPBar->GetWidget<CProgressBar>()->SetTexture(EProgressBar_Texture_Type::Bar,"BossHP", TEXT("CharacterHPBar.bmp"));
	m_HPBar->GetWidget<CProgressBar>()->SetSize(75.f, 10.f);
	m_HPBar->SetPos(-40.f, -55.f);

	m_nameBar = CreateWidgetComponent<CText>("NameBar");
	m_nameBar->GetWidget<CText>()->SetText(TEXT("대왕문어"));
	m_nameBar->GetWidget<CText>()->EnableShadow(true);
	m_nameBar->GetWidget<CText>()->SetTextColor(255, 0,0);
	m_nameBar->GetWidget<CText>()->SetTextShadowColor(255, 240,240);
	m_nameBar->GetWidget<CText>()->SetShadowOffset(2.f, 1.5f);
	m_nameBar->SetPos(-42.f, -80.f);

	SetSideWallCheck(true);
	return true;
}

void CBoss::Update(float deltaTime)
{
	CCharacter::Update(deltaTime);
	deltaTime *= m_timeScale;
	if (CheckCurrentAnimation("Boss_Die"))
	{
		return;
	}
	m_PatternDelay += deltaTime;
	m_ChangeTime += deltaTime;
	m_ChargeTime += deltaTime;
	m_InvisibleTime += deltaTime;
	{
		auto	iter = m_listMarker.begin();
		auto	iterEnd = m_listMarker.end();
		for (; iter != iterEnd;)
		{
			if ((*iter)->GetIsBreak())
			{
				iter = m_listMarker.erase(iter);
				m_IsMarkerBreak = true;
				m_PatternDelay = 0;
				m_scene->GetSceneResource()->SoundPlay("BossStun");
				ChangeAnimation("Boss_Stun");
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
	if (CheckCurrentAnimation("Boss_Stun") ||CheckCurrentAnimation("Boss_InvisibleS"))
	{
		if(m_PatternDelay>7.f)
		{
			Recovery();
			return;
		}
		if (m_InvisibleTime < 1.f)
		{
			ChangeAnimation("Boss_InvisibleS");
		}
		else
		{
			ChangeAnimation("Boss_Stun");
		}
		return;
	}
	if (CheckCurrentAnimation("Boss_Charge")||CheckCurrentAnimation("Boss_InvisibleC"))
	{
		if (m_ChargeTime > 5.f&& !m_IsMarkerBreak)
		{
			Recovery();		//얘가 먼저와야 이 코드가 1번만 실행됨
			m_Warning = m_scene->CreateObject<CEffect>("HitEffect");
			m_RealSkillPos = m_pos;
			m_Warning->SetPos(m_RealSkillPos);
			m_Warning->SetEndFunction<CBoss>("Warning", this, &CBoss::EXPattern);
			return;
		}
		if (m_InvisibleTime < 1.f)
		{
			ChangeAnimation("Boss_InvisibleC");
		}
		else
		{
			ChangeAnimation("Boss_Charge");
		}
		return;
	}
	//플레이어의 위치를 쳐다본다
	//x축기준으로 비교한뒤 x,y좌표차이로 1번더 비교해준다.
	m_PlayerPos = m_scene->GetPlayer()->GetPos();
	Vector2 absolutePos = m_PlayerPos -m_pos;
	if (m_ChangeTime >= 0.5f)
	{
		m_ChangeTime = 0;
		if (absolutePos.x > 0)
		{
			if (absolutePos.x < absolutePos.y)
			{
				m_BossDir = 1;
				m_dir = Vector2(0, 1);
			}
			else if (absolutePos.x < -absolutePos.y)
			{
				m_BossDir = 0;
				m_dir = Vector2(0, -1);
			}
			else
			{
				m_BossDir = 3;
				m_dir = Vector2(1, 0);
			}
		}
		else
		{
			if (-absolutePos.x < absolutePos.y)
			{
				m_BossDir = 1;
				m_dir = Vector2(0, 1);
			}
			else if (-absolutePos.x < -absolutePos.y)
			{
				m_BossDir = 0;
				m_dir = Vector2(0, -1);
			}
			else
			{
				m_BossDir = 2;
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
			ChangeAnimation("Boss_Charge");
			CMarker* marker = m_scene->CreateObject<CMarker>("Marker");
			marker->SetPos(m_pos.x,m_pos.y + m_pivot.y * m_size.y);
			marker->SetTime(5.f);
			m_listMarker.push_back(marker);
			return;
		}
		int random = rand() % 3;
		m_Warning = m_scene->CreateObject<CEffect>("HitEffect");
		if(random ==0)
		{
			m_RealSkillDir = m_dir;
			Vector2 tilePos = m_scene->GetTileMap()->GetTile(m_pos + m_dir * m_pivot * m_size)->GetPos();
			m_RealSkillPos = tilePos + TILE * 0.5f;
			m_Warning->SetPos(m_RealSkillPos);
			m_Warning->SetEndFunction<CBoss>("Warning", this, &CBoss::Fire);
		}
		else if (random == 1)
		{
			int playerY=m_scene->GetTileMap()->GetTileIndexY(m_PlayerPos.y);
			Vector2 tilePos = m_scene->GetTileMap()->GetTile(1,playerY)->GetPos();
			m_RealSkillPos = tilePos + TILE * 0.5f;
			m_Warning->SetPos(m_RealSkillPos);
			m_Warning = m_scene->CreateObject<CEffect>("HitEffect");
			m_Warning->SetPos(m_RealSkillPos.x + 728.f, m_RealSkillPos.y);
			m_Warning->SetEndFunction<CBoss>("Warning", this, &CBoss::Summon);
		}
		else
		{
			Vector2 tilePos = m_scene->GetTileMap()->GetTile(m_PlayerPos)->GetPos();
			m_RealSkillPos = tilePos + TILE * 0.5f;
			m_Warning->SetPos(m_RealSkillPos);
			m_Warning->SetEndFunction<CBoss>("Warning", this, &CBoss::Geyser);
		}
		return;
	}
	if(!m_IsPattern)
	{
		Move(m_dir * 13);
	}
}

void CBoss::PostUpdate(float deltaTime)
{
	CCharacter::PostUpdate(deltaTime);
}

void CBoss::Render(HDC hDC, float deltaTime)
{
	CCharacter::Render(hDC, deltaTime);
}

float CBoss::InflictDamage(float damage)
{
	if(m_InvisibleTime<1.f)
	{
		return 0;
	}
	damage = CCharacter::InflictDamage(damage);
	if (CheckCurrentAnimation("Boss_Stun"))
	{
		damage=50.f;
		Recovery();
	}
	m_HP -= (int)damage;
	m_scene->FindWidgetWindow<CCharacterHUD>("CharacterHUD")->SetHP(m_HP / (float)m_HPMax);
	m_HPBar->GetWidget<CProgressBar>()->SetValue(m_HP / (float)m_HPMax);
	if (m_HP <= 0)
	{
		m_Circle->SetActive(false);
		m_scene->GetSceneResource()->SoundPlay("BossDie");
		ChangeAnimation("Boss_Die");
	}
	m_scene->GetSceneResource()->SoundPlay("BossHit");
	m_InvisibleTime = 0;
	return damage;
}

void CBoss::Die()
{
	SetActive(false);
	m_HPBar->SetActive(false);
	m_nameBar->SetActive(false);
	CItem* item = m_scene->CreateObject<CItem>("Shoes");
	Vector2 monsterPos = m_scene->GetTileMap()->GetTile(m_pos)->GetPos();
	item->SetPos(monsterPos + TILE * 0.5);
	item->ChangeAnimation("Item_shoes");
	item->SetCanDelete(false);
}

void CBoss::DieSound()
{
	m_scene->GetSceneResource()->SoundPlay("EnemyDie");
}

void CBoss::Recovery()
{
	ChangeAnimation("Boss_InvisibleD");
	m_InvisibleTime = 0.f;
	m_IsMarkerBreak = false;
	m_PatternDelay = 0.f;
	m_fireCount = 0;
}

void CBoss::Fire()
{
	m_Warning->SetActive(false);
	m_IsPattern = false;
	m_scene->GetSceneResource()->SoundPlay("BossFire");
	CBomb* bomb = m_scene->CreateObject<CBomb>("Bomb");
	bomb->SetPos(m_RealSkillPos);
	bomb->SetDistance(3);
	bomb->SetBombMove(m_RealSkillDir);
	bomb->SetBombSpeed(800.f);
	CCollider* bombCol = bomb->FindCollider("Bomb");
	bombCol->SetCollisionProfile("MonsterAttack");
}

void CBoss::Summon()
{
	m_Warning->SetActive(false);
	m_IsPattern = false;
	bool IsSummon = false;
	auto	iter = m_listMonster.begin();
	auto	iterEnd = m_listMonster.end();
	CMonster* monster;
	Vector2 secondPos = Vector2(m_RealSkillPos.x + 728.f, m_RealSkillPos.y);
	//소환하려는 위치에 오브젝트가 있으면 소환안한다
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
	if(IsSummon)
	{
		m_scene->GetSceneResource()->SoundPlay("EnemySummon");
		monster = m_scene->CreateObject<CMonster>("Monster");
		monster->SetPos(m_RealSkillPos);
		m_listMonster.push_back(monster);
		IsSummon = false;
	}
	else
	{
		m_scene->GetSceneResource()->SoundPlay("EnemySummonError");
	}
	if (!m_scene->GetTileMap()->GetTile(secondPos)->GetSideCollision())
	{
		IsSummon = true;
		for (; iter != iterEnd; ++iter)
		{
			if (m_scene->GetTileMap()->GetTileIndex((*iter)->GetPos()) == m_scene->GetTileMap()->GetTileIndex(secondPos))
			{
				IsSummon = false;
				break;
			}
		}
	}
	if (IsSummon)
	{
		m_scene->GetSceneResource()->SoundPlay("EnemySummon");
		monster = m_scene->CreateObject<CMonster>("Monster");
		monster->SetPos(secondPos);
		m_listMonster.push_back(monster);
	}
	else
	{
		m_scene->GetSceneResource()->SoundPlay("EnemySummonError");
	}
}

void CBoss::Geyser()
{
	m_Warning->SetActive(false);
	m_IsPattern = false;
	m_scene->GetSceneResource()->SoundPlay("Bomb_wave");
	CExplosion* explosion = m_scene->CreateObject<CExplosion>("BossExplosion");
	explosion->SetPos(m_RealSkillPos);
	CCollider* explosionCol = explosion->FindCollider("BossExplosion");
	explosionCol->SetCollisionProfile("MonsterAttack");
}

void CBoss::EXPattern()
{
	m_Warning->SetActive(false);
	m_IsPattern = false;
	m_scene->GetSceneResource()->SoundPlay("Bomb_wave");
	CTileMap* tileMap = m_scene->GetTileMap();
	Vector2 LT = m_pos - m_pivot * m_size;
	Vector2 RB = LT + m_size;
	int startIndexX = tileMap->GetTileIndexX(LT.x) - 1;
	startIndexX = startIndexX < 0 ? 0 : startIndexX;
	int startIndexY = tileMap->GetTileIndexY(LT.y) - 1;
	startIndexY = startIndexY < 0 ? 0 : startIndexY;
	int endIndexX = tileMap->GetTileIndexX(RB.x) + 1;
	endIndexX = endIndexX > tileMap->GetCountX() - 1 ? tileMap->GetCountX() - 1 : endIndexX;
	int endIndexY = tileMap->GetTileIndexY(RB.y) + 1;
	endIndexY = endIndexY > tileMap->GetCountY() - 1 ? tileMap->GetCountY() - 1 : endIndexY;
	for(startIndexY; startIndexY <= endIndexY; ++startIndexY)
	{
		int indexX = startIndexX;
		for(; indexX <= endIndexX;++indexX)
		{
			Vector2 tilePos = tileMap->GetTile(indexX, startIndexY)->GetPos();
			if(tileMap->GetTile(indexX, startIndexY)->GetSideCollision())
			{
				continue;
			}
			CBombExplosion* explosion = m_scene->CreateObject<CBombExplosion>("Explosion");
			explosion->SetPos(tilePos + TILE * 0.5f);
		}
	}
}
