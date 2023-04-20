#include "Sewer.h"
#include "Bomb.h"
#include "TileMap.h"
#include "Tile.h"
#include "../Collision/ColliderBox.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"

CSewer::CSewer()
	: m_CoolTime(1.f)
{
	SetTypeID<CSewer>();
	m_ColliderSize = Vector2(10.f, 10.f);
	m_OffsetSize = Vector2(0.f, 8.f);
	m_renderLayer = ERender_Layer::Event;
}

CSewer::CSewer(const CSewer& obj)
	: CGameObject(obj)
	, m_CoolTime(1.f)
{
}

CSewer::~CSewer()
{
}

bool CSewer::Init()
{
	CGameObject::Init();
	SetPivot(0.5f, 0.5f);
	SetTexture("Sewer", TEXT("Event/map_fact_event.bmp"));
	// 충돌체 추가
	CColliderBox* box = AddCollider<CColliderBox>("Sewer");
	box->SetExtent(m_ColliderSize.x, m_ColliderSize.y);
	box->SetOffset(m_OffsetSize);
	box->SetCollisionProfile("Event");
	box->SetCollisionBeginFunction<CSewer>(this, &CSewer::CollisionBegin);
	box->SetCollisionEndFunction<CSewer>(this, &CSewer::CollisionEnd);
	return true;
}

void CSewer::Update(float deltaTime)
{
	CGameObject::Update(deltaTime);
	m_CoolTime-= deltaTime;
	/*if (m_BombCollider)
	{
		if (!m_BombCollider->GetOwner()->GetActive())
		{
			if (m_BombPos == m_scene->GetTileMap()->GetTile(m_pos)->GetPos())
			{
				if (m_CoolTime > 0)
				{
					return;
				}
				CTileMap* tileMap = m_scene->GetTileMap();
				Vector2 tilePos = tileMap->GetTile(m_pos)->GetPos();
				CBomb* bomb = m_scene->CreateObject<CBomb>("Bomb");
				auto	iterBegin = m_scene->SewerBegin();
				auto	iterEnd = m_scene->SewerEnd();
				for (auto iter = iterBegin; iter != iterEnd; ++iter)
				{
					Vector2 sewerTilePos = tileMap->GetTile((*iter)->GetPos())->GetPos();
					if (tilePos == sewerTilePos)
					{
						++iter;
						if (iter == iterEnd)
						{
							iter = iterBegin;
						}
						sewerTilePos = tileMap->GetTile((*iter)->GetPos())->GetPos();
						bomb->SetPos(sewerTilePos + TILE * 0.5f);
						bomb->SetDistance(2);
						bomb->Explosion();
						break;
					}
				}
				m_CoolTime = 1.0f;
				m_BombCollider = nullptr;
			}
		}
	}*/
}

void CSewer::PostUpdate(float deltaTime)
{
	CGameObject::PostUpdate(deltaTime);
}

void CSewer::Render(HDC hDC, float deltaTime)
{
	CGameObject::Render(hDC, deltaTime);
}

void CSewer::CollisionBegin(CCollider* src, CCollider* dest)
{
	//if(dest->GetOwner()->GetName() == "Bomb")
	//{
	//	m_BombCollider=dest;
	//	Vector2 destPos = dest->GetOwner()->GetPos();
	//	m_BombPos = m_scene->GetTileMap()->GetTile(destPos)->GetPos();
	//}
	if (dest->GetProfile()->channel == ECollision_Channel::Default)
	{
		if (m_CoolTime>0)
		{
			return;
		}
		CTileMap* tileMap = m_scene->GetTileMap();
		Vector2 tilePos = tileMap->GetTile(m_pos)->GetPos();
		CBomb* bomb = m_scene->CreateObject<CBomb>("Bomb");
		CCollider* bombCol = bomb->FindCollider("Bomb");
		bombCol->SetCollisionProfile("MonsterAttack");
		auto	iterBegin = m_scene->SewerBegin();
		auto	iterEnd = m_scene->SewerEnd();
		for (auto iter= iterBegin; iter != iterEnd;	++iter)
		{
			Vector2 sewerTilePos = tileMap->GetTile((*iter)->GetPos())->GetPos();
			if (tilePos == sewerTilePos)
			{
				++iter;
				if(iter== iterEnd)
				{
					iter = iterBegin;
				}
				sewerTilePos = tileMap->GetTile((*iter)->GetPos())->GetPos();
				bomb->SetPos(sewerTilePos + TILE * 0.5f);
				bomb->SetDistance(2);
				bomb->Explosion();
				break;
			}
		}
		m_CoolTime = 1.0f;
	}
}

void CSewer::CollisionEnd(CCollider* src, CCollider* dest)
{
	//if(dest->GetOwner()->GetName() == "Bomb")
	//{
	//	if(!dest->GetOwner()->GetActive()&& m_CoolTime <= 0)
	//	{
	//		CTileMap* tileMap = m_scene->GetTileMap();
	//		Vector2 tilePos = tileMap->GetTile(m_pos)->GetPos();
	//		CBomb* bomb = m_scene->CreateObject<CBomb>("Bomb");
	//		auto	iterBegin = m_scene->SewerBegin();
	//		auto	iterEnd = m_scene->SewerEnd();
	//		for (auto iter = iterBegin; iter != iterEnd; ++iter)
	//		{
	//			Vector2 sewerTilePos = tileMap->GetTile((*iter)->GetPos())->GetPos();
	//			if (tilePos == sewerTilePos)
	//			{
	//				++iter;
	//				if (iter == iterEnd)
	//				{
	//					iter = iterBegin;
	//				}
	//				sewerTilePos = tileMap->GetTile((*iter)->GetPos())->GetPos();
	//				bomb->SetPos(sewerTilePos + TILE * 0.5f);
	//				bomb->SetDistance(2);
	//				bomb->Explosion();
	//				break;
	//			}
	//		}
	//		m_CoolTime = 1.0f;
	//	}
	//}
}