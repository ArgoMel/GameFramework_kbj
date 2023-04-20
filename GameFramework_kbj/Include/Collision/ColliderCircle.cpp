#include "ColliderCircle.h"
#include "../GameObject/GameObject.h"
#include "../GameManager.h"
#include "../Scene/Scene.h"
#include "../Scene/Camera.h"
#include "CollisionManager.h"
#include "ColliderBox.h"

CColliderCircle::CColliderCircle()
{
    SetTypeID<CColliderCircle>();
    m_colliderType = ECollider_Type::Circle;
    m_info.radius = 30.f;
}

CColliderCircle::CColliderCircle(const CColliderCircle& collider)
    : CCollider(collider)
    ,m_info(collider.m_info)
{
}

CColliderCircle::~CColliderCircle()
{
}

bool CColliderCircle::Init()
{
    if (!CCollider::Init())
    {
        return false;
    }
    return true;
}

void CColliderCircle::Update(float deltaTime)
{
    CCollider::Update(deltaTime);
}

void CColliderCircle::PostUpdate(float deltaTime)
{
    CCollider::PostUpdate(deltaTime);
    Vector2	pos = m_owner->GetPos();
    m_info.center = pos + m_offset;
    m_bottom = m_info.center.y + m_info.radius;
}

void CColliderCircle::Render(HDC hDC, float deltaTime)
{
#ifdef _DEBUG
    HPEN	pen = CGameManager::GetInst()->GetPen(EBrush_Type::Green);
    if (!m_collisionList.empty() || m_mouseCollision)
    {
        pen = CGameManager::GetInst()->GetPen(EBrush_Type::Red);
    }
    HPEN	prevPen = (HPEN)SelectObject(hDC, pen);
    CCamera* camera = m_scene->GetCamera();
    Vector2	pos = m_info.center - camera->GetPos();
    MoveToEx(hDC, (long)(pos.x + m_info.radius), (long)pos.y, nullptr);
    for (int i = 12; i <= 360; i += 12)
    {
        Vector2	target;
        target.x = pos.x + cosf(DegreeToRadian((float)i)) * m_info.radius;
        target.y = pos.y + sinf(DegreeToRadian((float)i)) * m_info.radius;
        LineTo(hDC, (long)target.x, (long)target.y);
    }
    SelectObject(hDC, prevPen);
#endif // _DEBUG
}

bool CColliderCircle::Collision(CCollider* dest)
{
    switch (dest->GetColliderType())
    {
    case ECollider_Type::Box:
        return CCollisionManager::GetInst()->CollisionBoxToCircle(m_hitPoint, (CColliderBox*)dest, this);
        break;
    case ECollider_Type::Circle:
        return CCollisionManager::GetInst()->CollisionCircleToCircle(m_hitPoint, this, (CColliderCircle*)dest);
    }

    return false;
}

bool CColliderCircle::CollisionMouse(const Vector2& mouse)
{
    return CCollisionManager::GetInst()->CollisionPointToCircle(m_hitPoint, mouse, m_info);
}
