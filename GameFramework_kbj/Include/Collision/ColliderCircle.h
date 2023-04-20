#pragma once
#include "Collider.h"
class CColliderCircle :public CCollider
{
protected:
	friend class CGameObject;
	CircleInfo m_info;
	CColliderCircle();
	CColliderCircle(const CColliderCircle& collider);
	virtual ~CColliderCircle();
public:
    CircleInfo GetInfo()   const
    {
        return m_info;
    }
    void SetRadius(float radius)
    {
        m_info.radius = radius;
    }
    virtual bool Init();
    virtual void Update(float deltaTime);
    virtual void PostUpdate(float deltaTime);
    virtual void Render(HDC hDC, float deltaTime);
    virtual bool Collision(CCollider* dest);
    virtual bool CollisionMouse(const Vector2& mouse);
};

