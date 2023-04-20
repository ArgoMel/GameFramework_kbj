#pragma once
#include "GameObject.h"
class CAurelionSol :public CGameObject
{
private:
	friend class CScene;
	float	m_angle;
	float	m_speed;
	float	m_duringTime;
	float	m_cooltime;
	float	m_range;
	float	m_rangeMin;
	float	m_rangeMax;
	float	m_skillDir;
	bool	m_skillOn;
protected:
	CAurelionSol();
	CAurelionSol(const CAurelionSol& obj);
	~CAurelionSol();
public:
	virtual void SetPos(float x, float y)
	{
		m_pos.x = x;
		m_pos.y = y;
	}
	virtual void SetPos(const Vector2& pos)
	{
		 m_pos=pos;
	}
	float GetAngle()
	{
		return m_angle;
	}
	float GetSpeed()
	{
		return m_speed;
	}
	float GetCooltime()
	{
		return m_cooltime;
	}
	float GetRange()
	{
		return m_range;
	}
	void CelestialExpansion();
	virtual bool Init();
	virtual void Update(float deltaTime);
	virtual void Render(HDC hDC, float deltaTime);
};