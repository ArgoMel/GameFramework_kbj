#pragma once
#include "GameObject.h"
class CWall :public CGameObject
{
private:
	friend class CScene;
	Vector2 tilePos;
	void CollisionBegin(CCollider* src, CCollider* dest);
	void CollisionEnd(CCollider* src, CCollider* dest);
	void Die();
protected:
	CWall();
	CWall(const CWall& obj);
	virtual ~CWall();
public:
	virtual bool Init();
	virtual void Update(float deltaTime);
	virtual void PostUpdate(float deltaTime);
	virtual void Render(HDC hDC, float deltaTime);
};

