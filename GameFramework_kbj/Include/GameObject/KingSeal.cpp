#include "KingSeal.h"
#include "Tornado.h"
#include "Gamgyul_E.h"
#include "Item.h"
#include "Effect.h"
#include "Marker.h"
#include "FallingBomb.h"
#include "TileMap.h"
#include "Tile.h"
#include "../Collision/ColliderCircle.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"
#include "../Widget/CharacterHUD.h"
#include "../Widget/WidgetComponent.h"
#include "../Widget/Text.h"
#include "../Widget/ProgressBar.h"
constexpr auto CHARGEMAXTIME = 5.f;

CKingSeal::CKingSeal()
	: m_InvisibleTime(1.f)
	, m_ChangeTime(0.5f)
	, m_ChargeTime(0.f)
	, m_PatternDelay(0.f)
	, m_fireCount(0)
	, m_RumbleCount(0)
	, m_HPMax(100)
	, m_BossDir(1)
	, m_MarkerCount(0)
	, m_IsPattern(false)
{
	SetTypeID<CKingSeal>();
	m_HP = m_HPMax;
	m_ColliderSize = Vector2(35.f, 35.f);
	m_OffsetSize = Vector2(0.f, 5.f);
}

CKingSeal::CKingSeal(const CKingSeal& obj)
	:CGameObject(obj)
	, m_InvisibleTime(obj.m_InvisibleTime)
	, m_ChangeTime(0.5f)
	, m_ChargeTime(0.f)
	, m_PatternDelay(0.f)
	, m_fireCount(obj.m_fireCount)
	, m_RumbleCount(0)
	, m_HPMax(obj.m_HPMax)
	, m_HP(obj.m_HPMax)
	, m_BossDir(1)
	, m_MarkerCount(0)
	, m_IsPattern(false)
{
}

CKingSeal::~CKingSeal()
{
}

bool CKingSeal::Init()
{
	CGameObject::Init();
	m_dir = Vector2(0.f, 1.f);
	SetPos(START_TILE.x + TILE.x * 7, START_TILE.y + TILE.y * 1);
	SetPivot(0.5f, 0.5f);
	CreateAnimation();
	AddAnimation("SealD");
	AddAnimation("SealU");
	AddAnimation("SealR");
	AddAnimation("SealL");
	AddAnimation("SealDie", false, 1.5f);
	AddAnimation("SealRumble", false,0.5f);
	AddAnimation("SealUInvisible", true, 0.1f);
	AddAnimation("SealDInvisible", true, 0.1f);
	AddAnimation("SealLInvisible", true, 0.1f);
	AddAnimation("SealRInvisible", true, 0.1f);
	AddAnimation("SealCInvisible", true, 0.1f);
	AddAnimation("SealSInvisible", true, 0.1f);
	AddAnimation("SealCharge", true, 0.3f);
	AddAnimation("SealStun", true, 0.3f);
	SetEndFunction<CKingSeal>("SealDie", this, &CKingSeal::Die);
	SetEndFunction<CKingSeal>("SealRumble", this, &CKingSeal::Again);
	AddNotify<CKingSeal>("SealDie", 3, this, &CKingSeal::DieSound);

	m_vecSequenceKey[0].push_back("SealU");
	m_vecSequenceKey[0].push_back("SealUInvisible");
	m_vecSequenceKey[1].push_back("SealD");
	m_vecSequenceKey[1].push_back("SealDInvisible");
	m_vecSequenceKey[2].push_back("SealL");
	m_vecSequenceKey[2].push_back("SealLInvisibles");
	m_vecSequenceKey[3].push_back("SealR");
	m_vecSequenceKey[3].push_back("SealRInvisible");

	m_Circle = AddCollider<CColliderCircle>("Seal");
	m_Circle->SetRadius(m_ColliderSize.x);
	m_Circle->SetOffset(m_OffsetSize);
	m_Circle->SetCollisionProfile("Monster");
	m_Circle->SetCollisionBeginFunction<CKingSeal>(this, &CKingSeal::CollisionBegin);
	m_Circle->SetCollisionEndFunction<CKingSeal>(this, &CKingSeal::CollisionEnd);

	m_HPBar = CreateWidgetComponent<CProgressBar>("BossHP");
	m_HPBar->GetWidget<CProgressBar>()->SetTexture(EProgressBar_Texture_Type::Bar, "BossHP", TEXT("CharacterHPBar.bmp"));
	m_HPBar->GetWidget<CProgressBar>()->SetSize(75.f, 10.f);
	m_HPBar->SetPos(-40.f, -55.f);

	m_nameBar = CreateWidgetComponent<CText>("NameBar");
	m_nameBar->GetWidget<CText>()->SetText(TEXT("대왕물개"));
	m_nameBar->GetWidget<CText>()->EnableShadow(true);
	m_nameBar->GetWidget<CText>()->SetTextColor(255, 0, 0);
	m_nameBar->GetWidget<CText>()->SetTextShadowColor(255, 240, 240);
	m_nameBar->GetWidget<CText>()->SetShadowOffset(2.f, 1.5f);
	m_nameBar->SetPos(-42.f, -80.f);

	SetSideWallCheck(true);
	return true;
}

void CKingSeal::Update(float deltaTime)
{
	CGameObject::Update(deltaTime);
	deltaTime *= m_timeScale;
	if (CheckCurrentAnimation("SealDie"))
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
				++m_MarkerCount;
				if (m_MarkerCount >= 2) 
				{
					auto iter1 = m_listMarker.begin();
					auto iterEnd1 = m_listMarker.end();
					for (; iter1 != iterEnd1; ++iter1)
					{
						(*iter1)->DeactiveText();
						(*iter1)->SetActive(false);
					}
					m_PatternDelay = 0;
					m_scene->GetSceneResource()->SoundPlay("BossStun");
					ChangeAnimation("SealStun");
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
	if (CheckCurrentAnimation("SealRumble")) 
	{
		Move(m_dir * TILE.x * 6);
		return;
	}
	if (CheckCurrentAnimation("SealStun") || CheckCurrentAnimation("SealSInvisible"))
	{
		if (m_PatternDelay > 4.f)
		{
			Recovery();
			return;
		}
		if (m_InvisibleTime < 1.f)
		{
			ChangeAnimation("SealSInvisible");
		}
		else
		{
			ChangeAnimation("SealStun");
		}
		return;
	}
	if (CheckCurrentAnimation("SealCharge") || CheckCurrentAnimation("SealCInvisible"))
	{
		if (m_ChargeTime > CHARGEMAXTIME && m_MarkerCount<2)
		{
			Recovery();		//얘가 먼저와야 이 코드가 1번만 실행됨
			EXPattern();
			return;
		}
		if (m_InvisibleTime < 1.f)
		{
			ChangeAnimation("SealCInvisible");
		}
		else
		{
			ChangeAnimation("SealCharge");
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
			ChangeAnimation("SealCharge");
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
			m_Warning->SetEndFunction<CKingSeal>("Warning", this, &CKingSeal::Rumble);
		}
		else if (random == 1&& m_listMonster.size() < 2)
		{
			Vector2 tilePos = m_scene->GetTileMap()->GetTile(m_PlayerPos)->GetPos();
			m_RealSkillPos = tilePos + TILE * 0.5f;
			m_Warning->SetPos(m_RealSkillPos);
			m_Warning->SetEndFunction<CKingSeal>("Warning", this, &CKingSeal::Summon);
		}
		else
		{
			Vector2 tilePos = m_scene->GetTileMap()->GetTile(m_PlayerPos)->GetPos();
			m_RealSkillPos = tilePos + TILE * 0.5f;
			m_Warning->SetPos(m_RealSkillPos);
			m_Warning->SetEndFunction<CKingSeal>("Warning", this, &CKingSeal::Falling);
		}
		return;
	}
	if (!m_IsPattern)
	{
		Move(m_dir * 13);
	}
}

void CKingSeal::PostUpdate(float deltaTime)
{
	CGameObject::PostUpdate(deltaTime);
}

void CKingSeal::Render(HDC hDC, float deltaTime)
{
	CGameObject::Render(hDC, deltaTime);
}

float CKingSeal::InflictDamage(float damage)
{
	if (m_InvisibleTime < 1.f)
	{
		return 0;
	}
	damage = CGameObject::InflictDamage(damage);
	if (CheckCurrentAnimation("SealStun"))
	{
		damage = 33.f;
		Recovery();
	}
	m_HP -= (int)damage;
	m_scene->FindWidgetWindow<CCharacterHUD>("CharacterHUD")->SetHP(m_HP / (float)m_HPMax);
	m_HPBar->GetWidget<CProgressBar>()->SetValue(m_HP / (float)m_HPMax);
	if (m_HP <= 0)
	{
		m_Circle->SetActive(false);
		m_scene->GetSceneResource()->SoundPlay("BossDie");
		ChangeAnimation("SealDie");
		return damage;
	}
	m_scene->GetSceneResource()->SoundPlay("SealHit");
	m_InvisibleTime = 0;
	return damage;
}

void CKingSeal::CollisionBegin(CCollider* src, CCollider* dest)
{
}

void CKingSeal::CollisionEnd(CCollider* src, CCollider* dest)
{
}

void CKingSeal::Die()
{
	SetActive(false);
	m_HPBar->SetActive(false);
	m_nameBar->SetActive(false);
	CItem* item = m_scene->CreateObject<CItem>("Dart");
	Vector2 monsterPos = m_scene->GetTileMap()->GetTile(m_pos)->GetPos();
	item->SetPos(monsterPos + TILE * 0.5);
	item->ChangeAnimation("Item_dart");
	item->SetCanDelete(false);
}

void CKingSeal::DieSound()
{
	m_scene->GetSceneResource()->SoundPlay("EnemyDie");
}

void CKingSeal::Recovery()
{
	ChangeAnimation("SealDInvisible");
	m_InvisibleTime = 0.f;
	m_MarkerCount = 0;
	m_PatternDelay = 0.f;
	m_fireCount = 0;
}

void CKingSeal::Again()
{
	ChangeAnimation("SealD");
	if (++m_RumbleCount > 2)
	{
		m_IsPattern = false;
		m_RumbleCount = 0;
		return;
	}
	m_Warning = m_scene->CreateObject<CEffect>("HitEffect");
	m_Warning->SetPos(m_pos);
	m_Warning->SetEndFunction<CKingSeal>("Warning", this, &CKingSeal::Rumble);
}

void CKingSeal::Rumble()
{
	m_Warning->SetActive(false);
	m_PatternDelay = 0.f;
	m_scene->GetSceneResource()->SoundPlay("BossSpin");
	ChangeAnimation("SealRumble");
}

void CKingSeal::Summon()
{
	m_Warning->SetActive(false);
	m_IsPattern = false;
	bool IsSummon = false;
	auto	iter = m_listMonster.begin();
	auto	iterEnd = m_listMonster.end();
	CGamgyul_E* monster;
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
	if (IsSummon)
	{
		m_scene->GetSceneResource()->SoundPlay("EnemySummon");
		monster = m_scene->CreateObject<CGamgyul_E>("Gamgyul_E");
		monster->SetPos(m_RealSkillPos);
		m_listMonster.push_back(monster);
		IsSummon = false;
	}
	else
	{
		m_scene->GetSceneResource()->SoundPlay("EnemySummonError");
	}
}

void CKingSeal::Falling()
{
	m_Warning->SetActive(false);
	m_IsPattern = false;
	m_scene->GetSceneResource()->SoundPlay("FallingBomb");
	CFallingBomb* fallingBomb = m_scene->CreateObject<CFallingBomb>("Falling");
	float Height = fallingBomb->GetHeight();
	fallingBomb->SetPos(m_RealSkillPos.x,m_RealSkillPos.y- Height);
}

void CKingSeal::EXPattern()
{
	m_Warning->SetActive(false);
	m_IsPattern = false;
	m_scene->GetSceneResource()->SoundPlay("BossTornado");
	CTornado* tornado = m_scene->CreateObject<CTornado>("Tornado");
	//0도일때 오른쪽
	float angle = m_pos.Angle(m_scene->GetPlayer()->GetPos());
	tornado->SetAngle(angle);
	tornado->SetPos(m_pos);
}