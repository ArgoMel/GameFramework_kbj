#include "Wall.h"
#include "Item.h"
#include "TileMap.h"
#include "Tile.h"
#include "../Collision/ColliderBox.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"

CWall::CWall()
{
	SetTypeID<CWall>();
	m_ColliderSize = Vector2(52, 52);
	//m_OffsetSize = Vector2(0.f, 8.f);
}

CWall::CWall(const CWall& obj) :CGameObject(obj)
{
}

CWall::~CWall()
{
}

bool CWall::Init()
{
	CGameObject::Init();
	m_moveSpeed = 300.f;
	SetPos(277.f, 40.f);
	SetPivot(0.5f, 0.5f);
	CreateAnimation();
	AddAnimation("Block2");
	AddAnimation("Block2_Pop", false, 0.5f);
	AddAnimation("FactoryBlock");
	AddAnimation("FactoryBlock_Pop", false, 0.5f);
	SetEndFunction<CWall>("Block2_Pop", this, &CWall::Die);
	SetEndFunction<CWall>("FactoryBlock_Pop", this, &CWall::Die);

	// 충돌체 추가
	CColliderBox* box = AddCollider<CColliderBox>("Wall");
	box->SetExtent(m_ColliderSize.x, m_ColliderSize.y);
	box->SetOffset(m_OffsetSize);
	box->SetCollisionProfile("Wall");
	box->SetCollisionBeginFunction<CWall>(this, &CWall::CollisionBegin);
	box->SetCollisionEndFunction<CWall>(this, &CWall::CollisionEnd);

	return true;
}

void CWall::Update(float deltaTime)
{
	CGameObject::Update(deltaTime);
}

void CWall::PostUpdate(float deltaTime)
{
	CGameObject::PostUpdate(deltaTime);
	//int indexX=m_scene->GetTileMap()->GetTileIndexX(m_pos.x);
	//int indexY=m_scene->GetTileMap()->GetTileIndexY(m_pos.y);
	//if(!m_scene->GetTileMap()->GetTile(indexX, indexY)->GetSideCollision())
	//{
	//	m_scene->GetTileMap()->GetTile(indexX, indexY)->SetSideCollision(true);
	//}

}

void CWall::Render(HDC hDC, float deltaTime)
{
	CGameObject::Render(hDC, deltaTime);
}

void CWall::CollisionBegin(CCollider* src, CCollider* dest)
{
	if (dest->GetProfile()->channel == ECollision_Channel::Default ||
		dest->GetProfile()->channel == ECollision_Channel::MonsterAttack||
		dest->GetProfile()->name=="Boss"||
		dest->GetProfile()->name=="Seal")
	{
		if (CheckCurrentAnimation("Block2"))
		{
			ChangeAnimation("Block2_Pop");
			return;
		}
		if (CheckCurrentAnimation("FactoryBlock"))
		{
			ChangeAnimation("FactoryBlock_Pop");
			return;
		}
	}
	if(dest->GetProfile()->channel == ECollision_Channel::Monster||
		dest->GetProfile()->channel == ECollision_Channel::Player||
		dest->GetProfile()->channel == ECollision_Channel::PlayerAttack)
	{
		Vector2 destColliderSize = dest->GetOwner()->GetColliderSize();
		Vector2 destPivot = dest->GetOwner()->GetPivot();
		Vector2 destPos = dest->GetOwner()->GetPos();
		Vector2 tileDestPos = m_scene->GetTileMap()->GetTile(destPos)->GetPos()+ TILE*0.5f;
		Vector2 destPrevPos = dest->GetOwner()->GetPrevPos();
		Vector2 tileDestPrevPos = m_scene->GetTileMap()->GetTile(destPrevPos)->GetPos()+ TILE*0.5f;
		if(tileDestPrevPos!= tileDestPos)
		{
			//dest가 왼쪽
			if(tileDestPos.x- tileDestPrevPos.x>0)
			{
				destPrevPos.x = tileDestPrevPos.x + destColliderSize.x* destPivot .x-1.f;
			}
			//dest가 오른쪽
			if (tileDestPos.x - tileDestPrevPos.x < 0)
			{
				destPrevPos.x = tileDestPrevPos.x - destColliderSize.x * destPivot.x + 1.f;
			}
			//dest가 위쪽
			if (tileDestPos.y - tileDestPrevPos.y > 0)
			{
				destPrevPos.y = tileDestPrevPos.y + destColliderSize.y * destPivot.x - 1.f;
			}
			//dest가 아래쪽
			if (tileDestPos.y - tileDestPrevPos.y < 0)
			{
				destPrevPos.y = tileDestPrevPos.y - destColliderSize.y * destPivot.x + 1.f;
			}
			dest->GetOwner()->SetPos(destPrevPos);
		}
		//Vector2 tileLT = m_scene->GetTileMap()->GetTile(m_pos)->GetPos();
		//Vector2 tileRB = tileLT + TILE;
		//Vector2 destOffset = dest->GetOwner()->GetOffsetSize();
		////dest가 왼쪽
		//if (tileLT.x>= destPos.x && tileRB.y - (destPos.y - destColliderSize.y * destPivot.y + destOffset.y) > 1.f &&
		//	tileLT.y - (destPos.y + destColliderSize.y * destPivot.y + destOffset.y) < -1.f)
		//{
		//	destPos.x = tileDestPos.x - destOffset.x-1.f;
		//	dest->GetOwner()->SetPos(destPos.x, destPos.y);
		//}
		////오른쪽
		//else if (tileRB.x<= destPos.x && tileRB.y - (destPos.y - destColliderSize.y * destPivot.y + destOffset.y) > 1.f &&
		//	tileLT.y - (destPos.y + destColliderSize.y * destPivot.y + destOffset.y) < -1.f)
		//{
		//	destPos.x = tileDestPos.x - destOffset.x + 1.f;
		//	dest->GetOwner()->SetPos(destPos.x, destPos.y);
		//}
		////아래
		//else if (tileLT.y >= destPos.y)
		//{
		//	destPos.y = tileDestPos.y - destOffset.y - 1.f;
		//	dest->GetOwner()->SetPos(destPos.x, destPos.y);
		//}
		////위
		//else if (tileRB.y <= destPos.y)
		//{
		//	destPos.y = tileDestPos.y - destOffset.y + 1.f;
		//	dest->GetOwner()->SetPos(destPos.x, destPos.y);
		//}
	}
}

void CWall::CollisionEnd(CCollider* src, CCollider* dest)
{
}

void CWall::Die()
{
	SetActive(false);
	int wallCount= m_scene->GetWallCount() - 1;
	m_scene->SetWallCount(wallCount);
	m_scene->GetTileMap()->SetTileSideCollision(tilePos, false);
	int random = rand() % 20;
	CItem* item = m_scene->CreateObject<CItem>("Item");
	item->SetPos(m_pos);
	CCollider* itemCol = item->FindCollider("Item");
	itemCol->SetCollisionProfile("Item");
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
	else if(random == 10)
	{
		item->SetName("Needle");
		item->ChangeAnimation("Item_needle");
	}
	else
	{
		item->SetActive(false);
	}
}
