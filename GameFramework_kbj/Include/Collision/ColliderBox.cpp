#include "ColliderBox.h"
#include "../GameObject/GameObject.h"
#include "../GameObject/TileMap.h"
#include "../GameObject/Tile.h"
#include "../GameManager.h"
#include "../Scene/Scene.h"
#include "../Scene/Camera.h"
#include "CollisionManager.h"
#include "ColliderCircle.h"

CColliderBox::CColliderBox()
	:m_width(100.f)
	,m_height(100.f)
{
	SetTypeID<CColliderBox>();
	m_colliderType = ECollider_Type::Box;
}

CColliderBox::CColliderBox(const CColliderBox& collider)
	: CCollider(collider)
	,m_width(collider.m_width)
	,m_height(collider.m_height)
	,m_info(collider.m_info)
{
}

CColliderBox::~CColliderBox()
{
}

bool CColliderBox::Init()
{
	if (!CCollider::Init())
	{
		return false;
	}
	return true;
}

void CColliderBox::Update(float deltaTime)
{
	CCollider::Update(deltaTime);
	CTile* tile = m_scene->GetTileMap()->GetTile(m_owner->GetPos());
	if(tile)
	{
		m_pos = tile->GetPos() + TILE * 0.5f;
	}
}

void CColliderBox::PostUpdate(float deltaTime)
{
	CCollider::PostUpdate(deltaTime);
	Vector2	size(m_width, m_height);
	m_info.LT = m_pos  + m_offset - size / 2.f;
	m_info.RB = m_pos + m_offset + size / 2.f;
	m_bottom = m_info.RB.y;
}

void CColliderBox::Render(HDC hDC, float deltaTime)
{
#ifdef _DEBUG
	HBRUSH	brush = CGameManager::GetInst()->GetBrush(EBrush_Type::Green);
	if (!m_collisionList.empty() || m_mouseCollision)
	{
		brush = CGameManager::GetInst()->GetBrush(EBrush_Type::Red);
	}
	CCamera* camera = m_scene->GetCamera();
	RECT	renderRC;
	renderRC.left = (long)(m_info.LT.x - camera->GetPos().x);
	renderRC.top = (long)(m_info.LT.y - camera->GetPos().y);
	renderRC.right = (long)(m_info.RB.x - camera->GetPos().x);
	renderRC.bottom = (long)(m_info.RB.y - camera->GetPos().y);
	FrameRect(hDC, &renderRC, brush);
#endif // _DEBUG
}

bool CColliderBox::Collision(CCollider* dest)
{
	switch (dest->GetColliderType())
	{
	case ECollider_Type::Box:
		return CCollisionManager::GetInst()->CollisionBoxToBox(m_hitPoint, this, (CColliderBox*)dest);
	case ECollider_Type::Circle:
		return CCollisionManager::GetInst()->CollisionBoxToCircle(m_hitPoint, this, (CColliderCircle*)dest);
		break;
	}
	return false;
}

bool CColliderBox::CollisionMouse(const Vector2& mouse)
{
	return CCollisionManager::GetInst()->CollisionPointToBox(m_hitPoint, mouse, m_info);
}
