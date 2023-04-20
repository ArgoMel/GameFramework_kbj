#pragma once
#include "GameObject.h"
class CTornado : public CGameObject
{
private:
	friend class CScene;
	float	m_movespeed;
	float	m_angle;
	float	m_rotationangle;
	float	m_distance;
	float	m_range;
	Vector2	m_linepos;
	void CollisionBegin(CCollider* src, CCollider* dest);
	void CollisionEnd(CCollider* src, CCollider* dest);
protected:
	CTornado();
	CTornado(const CTornado& obj);
	virtual ~CTornado();
public:
	virtual void SetPos(float x, float y)
	{
		CGameObject::SetPos(x, y);
		m_linepos = m_pos;
	}
	virtual void SetPos(const Vector2& pos)
	{
		CGameObject::SetPos(pos);
		m_linepos = m_pos;
	}
	void SetDistance(float dist)
	{
		m_distance = dist;
	}
	void SetAngle(float angle)
	{
		m_angle = angle;
	}
	virtual bool Init();
	virtual void Update(float deltaTime);
	virtual void PostUpdate(float deltaTime);
	virtual void Render(HDC hDC, float deltaTime);
};

