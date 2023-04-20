#include "FallingBomb.h"
#include "BombExplosion.h"
#include "TileMap.h"
#include "Tile.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"
#include "../Collision/ColliderBox.h"

CFallingBomb::CFallingBomb()
	: m_Height(200.f)
	, m_FallingSpeed(300.f)
{
	m_renderLayer = ERender_Layer::Effect;
}

CFallingBomb::CFallingBomb(const CFallingBomb& obj)
	:CGameObject(obj)
	, m_Height(obj.m_Height)
	, m_FallingSpeed(obj.m_FallingSpeed)
{
}

CFallingBomb::~CFallingBomb()
{
}

bool CFallingBomb::Init()
{
	SetPos(m_pos.x,m_pos.y- m_Height);
	SetPivot(0.5f, 0.5f);
	SetTexture("Falling", TEXT("Attack/Falling.bmp"));
	SetColorKey(255, 0, 255);
	return true;
}

void CFallingBomb::Update(float deltaTime)
{
	CGameObject::Update(deltaTime);
	m_Height -= deltaTime* m_FallingSpeed;
	m_pos.y += deltaTime* m_FallingSpeed;
	if (m_Height < 0.f)
	{
		SetActive(false);
		m_scene->GetSceneResource()->SoundPlay("Bomb_wave");
		CTileMap* tileMap = m_scene->GetTileMap();
		Vector2 LT = m_pos - m_pivot * m_size;
		Vector2 RB = LT + m_size;
		int startIndexX = tileMap->GetTileIndexX(LT.x);
		startIndexX = startIndexX < 0 ? 0 : startIndexX;
		int startIndexY = tileMap->GetTileIndexY(LT.y);
		startIndexY = startIndexY < 0 ? 0 : startIndexY;
		int endIndexX = tileMap->GetTileIndexX(RB.x);
		endIndexX = endIndexX > tileMap->GetCountX() - 1 ? tileMap->GetCountX() - 1 : endIndexX;
		int endIndexY = tileMap->GetTileIndexY(RB.y);
		endIndexY = endIndexY > tileMap->GetCountY() - 1 ? tileMap->GetCountY() - 1 : endIndexY;
		Vector2 tileSize = tileMap->GetTile(startIndexX)->GetSize();
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
				explosion->SetPos(tilePos + tileSize * 0.5f);
			}
		}
	}
}

void CFallingBomb::PostUpdate(float deltaTime)
{
	CGameObject::PostUpdate(deltaTime);
}

void CFallingBomb::Render(HDC hDC, float deltaTime)
{
	CGameObject::Render(hDC, deltaTime);
}
