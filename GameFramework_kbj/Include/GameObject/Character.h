#pragma once
#include "GameObject.h"
class CCharacter :public CGameObject
{
protected:
	friend class CScene;
	CCharacter();
	CCharacter(const CCharacter& obj);
	virtual ~CCharacter();
public:
	virtual bool Init();
	virtual void Update(float deltaTime);
	virtual void Render(HDC hDC,float deltaTime);
	virtual float InflictDamage(float damage);
};

