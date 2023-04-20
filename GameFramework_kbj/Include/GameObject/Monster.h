#pragma once
#include "Character.h"
class CMonster : public CGameObject
{
private:
	friend class CScene;
	float	m_fireTime;		//ÄðÅ¸ÀÓ
	void CollisionBegin(CCollider* src, CCollider* dest);
	void CollisionEnd(CCollider* src, CCollider* dest);
	void Die();
protected:
	CMonster();
	CMonster(const CMonster& obj);
	virtual ~CMonster();
public:
	virtual bool Init();
	virtual void Update(float deltaTime);
	virtual void PostUpdate(float deltaTime);
	virtual void Render(HDC hDC, float deltaTime);
};

