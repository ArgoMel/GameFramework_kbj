#pragma once
#include "GameObject.h"
class CBomb : public CGameObject
{
private:
	friend class CScene;
	CSharedPtr<class CColliderBox> m_box;
	std::list<CSharedPtr<class CWall>>	m_listWall;
	Vector2	m_bombMove;
	Vector2	m_bombDir;
	Vector2 m_BombTilePos;
	int	m_distance;
	int	m_WallCount;
	float	m_fireTime;
	float	m_maxTime;
	float	m_BombSpeed;
	bool	m_isBomb;
	void CollisionBegin(CCollider* src, CCollider* dest);
	void CollisionEnd(CCollider* src, CCollider* dest);
	void Nomalize();
protected:
	CBomb();
	CBomb(const CBomb& obj);
	~CBomb();
public:
	bool GetIsBomb()	const
	{
		return m_isBomb;
	}
	void SetBombMove(float x, float y)
	{
		m_bombMove.x = x;
		m_bombMove.y = y;
	}
	void SetBombMove(const Vector2& move)
	{
		m_bombMove = move;
	}
	void SetDistance(int dist)
	{
		m_distance = dist;
	}
	void SetMaxTime(float time)
	{
		m_maxTime = time;
	}
	void SetBombSpeed(float speed)
	{
		m_BombSpeed = speed;
	}
	void SetIsBomb(bool bomb)
	{
		m_isBomb = bomb;
	}
	virtual bool Init();
	virtual void Update(float deltaTime);
	virtual void PostUpdate(float deltaTime);
	virtual void Render(HDC hDC, float deltaTime);
	void Explosion();
};

