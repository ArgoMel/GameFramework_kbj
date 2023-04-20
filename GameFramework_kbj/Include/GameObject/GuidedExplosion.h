#pragma once
#include "GameObject.h"
class CGuidedExplosion :public CGameObject
{
private:
	friend class CScene;
	CSharedPtr<class CBombExplosion> m_Explosion;
	Vector2	m_ObjectDir;
	Vector2 m_ObjectTilePos;
	float	m_CoolTime;
	int		m_ExplodeCount;
	bool	m_CanExplosion;
protected:
	CGuidedExplosion();
	CGuidedExplosion(const CGuidedExplosion& obj);
	~CGuidedExplosion();
	void Nomalize(const Vector2& vec);
public:
	virtual bool Init();
	virtual void Update(float deltaTime);
	virtual void PostUpdate(float deltaTime);
	virtual void Render(HDC hDC, float deltaTime);
	void Explosion();
};

