#pragma once
#include "Collider.h"
class CColliderBox :public CCollider
{
	friend class CGameObject;
protected:
	float   m_width;
	float   m_height;
	BoxInfo m_info;
	CColliderBox();
	CColliderBox(const CColliderBox& collider);
	virtual ~CColliderBox();
public:
	BoxInfo GetInfo()   const
	{
		return m_info;
	}
	void SetExtent(float width, float height)
	{
		m_width = width;
		m_height = height;
	}
	virtual bool Init();
	virtual void Update(float deltaTime);
	virtual void PostUpdate(float deltaTime);
	virtual void Render(HDC hDC, float deltaTime);
	virtual bool Collision(CCollider* dest);
	virtual bool CollisionMouse(const Vector2& mouse);
};

