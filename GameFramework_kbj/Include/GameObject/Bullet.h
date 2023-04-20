#pragma once
#include "GameObject.h"
class CBullet :public CGameObject
{
private:
	friend class CScene;
	Vector2	m_angle;
	float	m_distance;
	float	m_damage;
	void CollisionBegin(CCollider* src, CCollider* dest);
	void CollisionEnd(CCollider* src, CCollider* dest);
protected:
	CBullet();
	CBullet(const CBullet& obj);
	~CBullet();
public:
	void SetAngle(const Vector2& angle)
	{
		m_angle = angle;
	}
	void SetAngle(float angle)
	{
		m_angle.x = angle;
		m_angle.y = angle;
	}
	void SetDistance(float dist)
	{
		m_distance = dist;
	}
	void SetDamage(float damage)
	{
		m_damage = damage;
	}
	virtual bool Init();
	virtual void Update(float deltaTime);
	virtual void PostUpdate(float deltaTime);
	virtual void Render(HDC hDC, float deltaTime);
};

