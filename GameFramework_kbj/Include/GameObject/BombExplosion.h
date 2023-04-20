#pragma once
#include "GameObject.h"
class CBombExplosion :public CGameObject
{
private:
	friend class CScene;
	float	m_damage;
	void CollisionBegin(CCollider* src, CCollider* dest);
	void CollisionEnd(CCollider* src, CCollider* dest);
	void Remove();
protected:
	CBombExplosion();
	CBombExplosion(const CBombExplosion& obj);
	~CBombExplosion();
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

