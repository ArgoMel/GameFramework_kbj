#include "GuidedExplosion.h"
#include "BombExplosion.h"
#include "TileMap.h"
#include "Tile.h"
#include "Wall.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"

CGuidedExplosion::CGuidedExplosion()
	: m_CoolTime(1.f)
	, m_ExplodeCount(10)
	, m_CanExplosion(true)
{
	m_ColliderSize = Vector2(52.f, 52.f);
}

CGuidedExplosion::CGuidedExplosion(const CGuidedExplosion& obj)
	: CGameObject(obj)
	, m_CoolTime(1.f)
	, m_ExplodeCount(10)
	, m_CanExplosion(true)
{
}

CGuidedExplosion::~CGuidedExplosion()
{
}

bool CGuidedExplosion::Init()
{
	SetPivot(0.5f, 0.5f);
	SetSideWallCheck(true);
	return true;
}

void CGuidedExplosion::Update(float deltaTime)
{
	CGameObject::Update(deltaTime);
	m_CoolTime += deltaTime;
	if (m_CoolTime >= 1)
	{
		m_CoolTime = 0.f;
		m_CanExplosion = true;
		Vector2 differ = m_scene->GetPlayer()->GetPos() - m_pos;
		if (differ == 0)
		{
			differ = Vector2(1.f, 0);
		}
		Nomalize(differ);
		m_move += m_ObjectDir * TILE;
	}
}

void CGuidedExplosion::PostUpdate(float deltaTime)
{
	CGameObject::PostUpdate(deltaTime);
	if (m_ObjectDir !=0.f &&m_CanExplosion)
	{
		Nomalize(m_move);
		Explosion();
	}
}

void CGuidedExplosion::Render(HDC hDC, float deltaTime)
{
	CGameObject::Render(hDC, deltaTime);
}

void CGuidedExplosion::Explosion()
{
	m_CanExplosion = false;
	m_scene->GetSceneResource()->SoundPlay("Bomb_wave");
	m_Explosion = m_scene->CreateObject<CBombExplosion>("Explosion");
	m_Explosion->SetPos(m_pos);
	m_Explosion = m_scene->CreateObject<CBombExplosion>("Explosion");
	CTileMap* tileMap = m_scene->GetTileMap();
	m_pos += m_ObjectDir * TILE;
	int tileIndexX = tileMap->GetTileIndexX(m_pos.x);
	int tileIndexY = tileMap->GetTileIndexY(m_pos.y);
	Vector2 tilePos = tileMap->GetTile(tileIndexX, tileIndexY)->GetPos();
	m_Explosion->SetPos(tilePos + TILE * 0.5f);
	if (m_ObjectDir == Vector2(1.f, 0))
	{
		m_Explosion->ChangeAnimation("ExplosionRight1");
	}
	else if (m_ObjectDir == Vector2(-1.f, 0))
	{
		m_Explosion->ChangeAnimation("ExplosionLeft1");
	}
	else if (m_ObjectDir == Vector2(0, 1.f))
	{
		m_Explosion->ChangeAnimation("ExplosionDown1");
	}
	else
	{
		m_Explosion->ChangeAnimation("ExplosionUp1");
	}
	--m_ExplodeCount;
	if (m_ExplodeCount == 0)
	{
		SetActive(false);
	}
}

void CGuidedExplosion::Nomalize(const Vector2& vec)
{
	if (abs(vec.x) > abs(vec.y))
	{
		m_ObjectDir = Vector2(vec.x / abs(vec.x), 0);
	}
	else if (abs(vec.y) > abs(vec.x))
	{
		m_ObjectDir = Vector2(0, vec.y / abs(vec.y));
	}
}
