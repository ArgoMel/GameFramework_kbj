#pragma once
#include "GameObject.h"
class CExplosion :public CGameObject
{
private:
	friend class CScene;
	float	m_damage;
	void CollisionBegin(CCollider* src, CCollider* dest);
	void CollisionEnd(CCollider* src, CCollider* dest);
	void Remove();
protected:
	CExplosion();
	CExplosion(const CExplosion& obj);
	~CExplosion();
public:
	void SetDamage(float damage)
	{
		m_damage = damage;
	}
	virtual bool Init();
	virtual void Update(float deltaTime);
	virtual void PostUpdate(float deltaTime);
	virtual void Render(HDC hDC, float deltaTime);
};