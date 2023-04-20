#include "Bomb.h"
#include "BombExplosion.h"
#include "TileMap.h"
#include "Tile.h"
#include "Wall.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"
#include "../Scene/Camera.h"
#include "../Collision/ColliderBox.h"
#include "../Collision/ColliderCircle.h"

CBomb::CBomb()
	: m_distance(1)
	, m_WallCount(0)
	, m_fireTime(0.f)
	, m_maxTime(3.f)
	, m_BombSpeed(500.f)
	, m_isBomb(false)
{
	m_ColliderSize = Vector2(50.f, 50.f);
	m_OffsetSize = Vector2(0.f, 0.f);
}

CBomb::CBomb(const CBomb& obj)
	: CGameObject(obj)
	, m_distance(obj.m_distance)
	, m_WallCount(0)
	, m_fireTime(obj.m_fireTime)
	, m_maxTime(obj.m_maxTime)
	, m_BombSpeed(obj.m_BombSpeed)
	, m_isBomb(obj.m_isBomb)
{
}

CBomb::~CBomb()
{
}

void CBomb::CollisionBegin(CCollider* src, CCollider* dest)
{
	if (dest->GetProfile()->channel == ECollision_Channel::Event)
	{
		return;
	}
	if(src->GetProfile()->channel == ECollision_Channel::MonsterAttack)
	{
		Explosion();
		return;
	}
	//	적,폭발 오브젝트와 부딪이면 바로 터짐
	if (dest->GetProfile()->channel == ECollision_Channel::Monster ||
		dest->GetProfile()->channel == ECollision_Channel::Default ||
		dest->GetProfile()->channel == ECollision_Channel::MonsterAttack ||
		dest->GetOwner()->GetName() == "Dart")
	{
		Explosion();
		return;
	}
	if(dest->GetProfile()->channel == ECollision_Channel::PlayerAttack)
	{
		if(m_move!=0)
		{
			m_bombMove = 0;
			m_move = 0;
			return;
		}
		Vector2 destPos = dest->GetOwner()->GetPos();
		Vector2 destPrevPos = dest->GetOwner()->GetPrevPos();
		CTileMap* tileMap = m_scene->GetTileMap();
		int indexX = tileMap->GetTileIndexX(m_pos.x);
		int indexY = tileMap->GetTileIndexY(m_pos.y);
		Vector2 tilePos;
		//dest가 왼쪽
		if (destPos.x - destPrevPos.x > 0)
		{
			tilePos = tileMap->GetTile(indexX - 1, indexY)->GetPos();
		}
		//dest가 오른쪽
		if (destPos.x - destPrevPos.x < 0)
		{
			tilePos = tileMap->GetTile(indexX+1, indexY)->GetPos();
		}
		//dest가 위쪽
		if (destPos.y - destPrevPos.y > 0)
		{
			tilePos = tileMap->GetTile(indexX, indexY-1)->GetPos();
		}
		//dest가 아래쪽
		if (destPos.y - destPrevPos.y < 0)
		{
			tilePos = tileMap->GetTile(indexX, indexY+1)->GetPos();
		}
		dest->GetOwner()->SetPos(tilePos+TILE*0.5f);
		return;
	}
	//if (dest->GetProfile()->channel == ECollision_Channel::Player)
	//{
	//	Vector2 destPos = dest->GetOwner()->GetPos();
	//	Vector2 destColliderSize = dest->GetOwner()->GetColliderSize();
	//	Vector2 destPivot = dest->GetOwner()->GetPivot();
	//	Vector2 tileDestPos = m_scene->GetTileMap()->GetTile(destPos)->GetPos() + TILE * 0.5f;
	//	Vector2 destPrevPos = dest->GetOwner()->GetPrevPos();
	//	Vector2 tileDestPrevPos = m_scene->GetTileMap()->GetTile(destPrevPos)->GetPos() + TILE * 0.5f;
	//	//플레이어의 위치가 콜라이더 안에 있을때는 풍선을 차지않도록 해야한다.
	//	if (tileDestPrevPos == tileDestPos) 
	//	{
	//		return;
	//	}
	//	//신발이 없으면 플레이어 밀어내기
	//	if (tileDestPrevPos != tileDestPos)
	//	{
	//		//dest가 왼쪽
	//		if (tileDestPos.x - tileDestPrevPos.x > 0)
	//		{
	//			destPrevPos.x = tileDestPrevPos.x + destColliderSize.x * destPivot.x - 1.f;
	//		}
	//		//dest가 오른쪽
	//		if (tileDestPos.x - tileDestPrevPos.x < 0)
	//		{
	//			destPrevPos.x = tileDestPrevPos.x - destColliderSize.x * destPivot.x + 1.f;
	//		}
	//		//dest가 위쪽
	//		if (tileDestPos.y - tileDestPrevPos.y > 0)
	//		{
	//			destPrevPos.y = tileDestPrevPos.y + destColliderSize.y * destPivot.x - 1.f;
	//		}
	//		//dest가 아래쪽
	//		if (tileDestPos.y - tileDestPrevPos.y < 0)
	//		{
	//			destPrevPos.y = tileDestPrevPos.y - destColliderSize.y * destPivot.x + 1.f;
	//		}
	//		dest->GetOwner()->SetPos(destPrevPos);
	//	}
	//	//플레이어가 신발아이템을 가지고 있을때 플레이어가 바라보는 방향으로 이동
	//	if(dest->GetOwner()->GetHaveShoes())
	//	{
	//		m_bombMove = dest->GetOwner()->GetMove();
	//		Nomalize();
	//		auto	iter = m_listWall.begin();
	//		auto	iterEnd = m_listWall.end();
	//		CTileMap* tileMap = m_scene->GetTileMap();
	//		for (; iter != iterEnd; ++iter)
	//		{
	//			if (tileMap->GetTile(m_pos+m_bombDir*TILE)->GetPos() == tileMap->GetTile((*iter)->GetPos())->GetPos())
	//			{
	//				m_bombMove = 0;
	//				break;
	//			}
	//		}
	//		return;
	//	}
	//}
}

void CBomb::CollisionEnd(CCollider* src, CCollider* dest)
{
}

void CBomb::Nomalize()
{
	if (abs(m_bombMove.x) > abs(m_bombMove.y))
	{
		m_bombDir = Vector2(m_bombMove.x / abs(m_bombMove.x), 0);
	}
	else if (abs(m_bombMove.y) > abs(m_bombMove.x))
	{
		m_bombDir = Vector2(0, m_bombMove.y / abs(m_bombMove.y));
	}
}

bool CBomb::Init()
{
	SetPivot(0.5f, 0.5f);
	CreateAnimation();
	AddAnimation("PlayerBomb");
	// 충돌체 추가
	m_box = AddCollider<CColliderBox>("Bomb");
	m_box->SetExtent(m_ColliderSize.x, m_ColliderSize.y);
	m_box->SetCollisionBeginFunction<CBomb>(this, &CBomb::CollisionBegin);
	m_box->SetCollisionEndFunction<CBomb>(this, &CBomb::CollisionEnd);

	char widgetName[64] = {};
	m_WallCount = m_scene->GetWallCount();
	int j = 1;
	for(int i=0;i< m_WallCount;++j)
	{
		sprintf_s(widgetName, "Wall%d", j);
		if(widgetName=="Wall99")
		{
			break;
		}
		if (!m_scene->FindObject<CWall>(widgetName)) 
		{
			continue;
		}
		m_listWall.push_back(m_scene->FindObject<CWall>(widgetName));
		++i;
	}

	SetSideWallCheck(true);
	return true;
}

void CBomb::Update(float deltaTime)
{
	CGameObject::Update(deltaTime);
	auto	iter = m_listWall.begin();
	auto	iterEnd = m_listWall.end();
	for (; iter != iterEnd;)
	{
		if (!(*iter)->GetActive())
		{
			iter = m_listWall.erase(iter);
			continue;
		}
		++iter;
	}
	if(m_move!=0)
	{
		m_bombMove = m_move;
	}
	if(m_bombMove!=0.f)
	{
		Nomalize();
		Move(m_bombDir * m_BombSpeed);
	}
	m_fireTime += deltaTime;
	if (m_fireTime >= m_maxTime)
	{
		Explosion();
	}
}

void CBomb::PostUpdate(float deltaTime)
{
	CGameObject::PostUpdate(deltaTime);
	if(m_bombDir !=0.f)
	{
		Vector2 LT = m_pos - m_pivot * m_ColliderSize+m_OffsetSize;
		Vector2 RB = LT+m_size;
		CTileMap* tileMap = m_scene->GetTileMap();
		if(m_bombDir.x>0.f)
		{	
			RB.x -= 3.f;
			RB.y -= 0.5f* TILE.y;
			m_BombTilePos = tileMap->GetTile(RB)->GetPos();
		}
		else if (m_bombDir.y > 0.f)
		{
			RB.x -= 0.5f * TILE.y;
			m_BombTilePos = tileMap->GetTile(RB)->GetPos();
		}
		else if (m_bombDir.x < 0.f)
		{
			LT.x -= 1.f;
			LT.y += 0.5f * TILE.y;
			m_BombTilePos = tileMap->GetTile(LT)->GetPos();
		}
		else
		{
			LT.x += 0.5f * TILE.y;
			LT.y -= 1.f;
			m_BombTilePos = tileMap->GetTile(LT)->GetPos();
		}
		if (tileMap->GetTile(m_BombTilePos)->GetSideCollision())
		{
			if (m_box->GetProfile()->channel == ECollision_Channel::MonsterAttack)
			{
				Explosion();
				return;
			}
			m_bombMove = 0;
			m_move = 0;
		}
		auto	iter = m_listWall.begin();
		auto	iterEnd = m_listWall.end();
		for (; iter != iterEnd; ++iter)
		{
			if (tileMap->GetTile(m_BombTilePos)->GetPos() == tileMap->GetTile((*iter)->GetPos())->GetPos())
			{
				m_bombMove = 0;
				m_move = 0;
				break;
			}
		}
	}
}

void CBomb::Render(HDC hDC, float deltaTime)
{
	CGameObject::Render(hDC, deltaTime);
}

void CBomb::Explosion()
{
	m_isBomb = true;
	SetActive(false);
	m_scene->GetSceneResource()->SoundPlay("Bomb_wave");
	CBombExplosion* explosion = m_scene->CreateObject<CBombExplosion>("Explosion");
	explosion->SetPos(m_pos);
	CTileMap* tileMap = m_scene->GetTileMap();
	int tileIndexX = tileMap->GetTileIndexX(m_pos.x);
	int tileIndexY = tileMap->GetTileIndexY(m_pos.y);
	int index = 1;
	bool IsWall=false;
	//위쪽 체크
	for(index=1; index<m_distance;++index)
	{
		if(tileMap->GetTile(tileIndexX, tileIndexY- index)->GetSideCollision())
		{
			break;
		}
		auto	iter = m_listWall.begin();
		auto	iterEnd = m_listWall.end();
		for (; iter != iterEnd;	++iter)
		{
			if (tileMap->GetTile(tileIndexX, tileIndexY - index)->GetPos()==tileMap->GetTile((*iter)->GetPos())->GetPos())
			{
				IsWall = true;
				break;
			}
		}
		if(IsWall)
		{
			IsWall = false;
			break;
		}
		explosion = m_scene->CreateObject<CBombExplosion>("Explosion");
		Vector2 tilePos = tileMap->GetTile(m_pos.x, m_pos.y - 52.f * index)->GetPos();
		explosion->SetPos(tilePos + TILE * 0.5f);
		explosion->ChangeAnimation("ExplosionUp2");
	}
	if (!tileMap->GetTile(tileIndexX, tileIndexY - index)->GetSideCollision())
	{
		explosion = m_scene->CreateObject<CBombExplosion>("Explosion");
		Vector2 tilePos = tileMap->GetTile(m_pos.x, m_pos.y - 52.f * index)->GetPos();
		explosion->SetPos(tilePos + TILE * 0.5f);
		explosion->ChangeAnimation("ExplosionUp1");
	}
	//아래쪽 체크
	for (index = 1; index < m_distance; ++index)
	{
		if (tileMap->GetTile(tileIndexX, tileIndexY + index)->GetSideCollision())
		{
			break;
		}
		auto	iter = m_listWall.begin();
		auto	iterEnd = m_listWall.end();
		for (; iter != iterEnd; ++iter)
		{
			if (tileMap->GetTile(tileIndexX, tileIndexY + index)->GetPos() == tileMap->GetTile((*iter)->GetPos())->GetPos())
			{
				IsWall = true;
				break;
			}
		}
		if (IsWall)
		{
			IsWall = false;
			break;
		}
		explosion = m_scene->CreateObject<CBombExplosion>("Explosion");
		Vector2 tilePos = tileMap->GetTile(m_pos.x, m_pos.y + 52.f * index)->GetPos();
		explosion->SetPos(tilePos + TILE * 0.5f);
		explosion->ChangeAnimation("ExplosionDown2");
	}
	if (!tileMap->GetTile(tileIndexX, tileIndexY + index)->GetSideCollision())
	{
		explosion = m_scene->CreateObject<CBombExplosion>("Explosion");
		Vector2 tilePos = tileMap->GetTile(m_pos.x, m_pos.y + 52.f * index)->GetPos();
		explosion->SetPos(tilePos + TILE * 0.5f);
		explosion->ChangeAnimation("ExplosionDown1");
	}
//왼쪽 체크
	for (index = 1; index < m_distance; ++index)
	{
		if (tileMap->GetTile(tileIndexX-index, tileIndexY)->GetSideCollision())
		{
			break;
		}
		auto	iter = m_listWall.begin();
		auto	iterEnd = m_listWall.end();
		for (; iter != iterEnd; ++iter)
		{
			if (tileMap->GetTile(tileIndexX-index, tileIndexY)->GetPos() == tileMap->GetTile((*iter)->GetPos())->GetPos())
			{
				IsWall = true;
				break;
			}
		}
		if (IsWall)
		{
			IsWall = false;
			break;
		}
		explosion = m_scene->CreateObject<CBombExplosion>("Explosion");
		Vector2 tilePos = tileMap->GetTile(m_pos.x - 52.f * index, m_pos.y)->GetPos();
		explosion->SetPos(tilePos + TILE * 0.5f);
		explosion->ChangeAnimation("ExplosionLeft2");
	}
	if (!tileMap->GetTile(tileIndexX-index, tileIndexY)->GetSideCollision())
	{
		explosion = m_scene->CreateObject<CBombExplosion>("Explosion");
		Vector2 tilePos = tileMap->GetTile(m_pos.x - 52.f * index, m_pos.y)->GetPos();
		explosion->SetPos(tilePos + TILE * 0.5f);
		explosion->ChangeAnimation("ExplosionLeft1");
	}
//오른쪽체크
	for (index = 1; index < m_distance; ++index)
	{
		if (tileMap->GetTile(tileIndexX + index, tileIndexY)->GetSideCollision())
		{
			break;
		}
		auto	iter = m_listWall.begin();
		auto	iterEnd = m_listWall.end();
		for (; iter != iterEnd; ++iter)
		{
			if (tileMap->GetTile(tileIndexX+index, tileIndexY)->GetPos() == tileMap->GetTile((*iter)->GetPos())->GetPos())
			{
				IsWall = true;
				break;
			}
		}
		if (IsWall)
		{
			IsWall = false;
			break;
		}
		explosion = m_scene->CreateObject<CBombExplosion>("Explosion");
		Vector2 tilePos = tileMap->GetTile(m_pos.x + 52.f * index, m_pos.y)->GetPos();
		explosion->SetPos(tilePos + TILE * 0.5f);
		explosion->ChangeAnimation("ExplosionRight2");
	}
	if (!tileMap->GetTile(tileIndexX+index, tileIndexY)->GetSideCollision())
	{
		explosion = m_scene->CreateObject<CBombExplosion>("Explosion");
		Vector2 tilePos = tileMap->GetTile(m_pos.x + 52.f * index, m_pos.y)->GetPos();
		explosion->SetPos(tilePos + TILE * 0.5f);
		explosion->ChangeAnimation("ExplosionRight1");
	}
}