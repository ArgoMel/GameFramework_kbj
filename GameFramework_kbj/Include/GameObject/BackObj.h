#pragma once
#include "GameObject.h"
class CBackObj :public CGameObject
{
protected:
	friend class CScene;
	CBackObj();
	CBackObj(const CBackObj& obj);
	virtual ~CBackObj();
public:
	virtual bool Init();
	virtual void Update(float deltaTime);
	virtual void Render(HDC hDC, float deltaTime);
};

