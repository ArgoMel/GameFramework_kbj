#pragma once
#include "GameObject.h"
class CSewer :public CGameObject
{
private:
	friend class CScene;
	CSharedPtr<class CCollider> m_BombCollider;
	Vector2 m_BombPos;
	float	m_CoolTime;		//ÄðÅ¸ÀÓ
	void CollisionBegin(CCollider* src, CCollider* dest);
	void CollisionEnd(CCollider* src, CCollider* dest);
protected:
	CSewer();
	CSewer(const CSewer& obj);
	virtual ~CSewer();
public:
	virtual bool Init();
	virtual void Update(float deltaTime);
	virtual void PostUpdate(float deltaTime);
	virtual void Render(HDC hDC, float deltaTime);
};

