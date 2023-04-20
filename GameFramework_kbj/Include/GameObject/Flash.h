#pragma once
#include "GameObject.h"
class CFlash :public CGameObject
{
private:
	friend class CScene;
	int			m_Count;
	float			m_time;
protected:
	CFlash();
	CFlash(const CFlash& obj);
	virtual ~CFlash();
public:
	virtual bool Init();
	virtual void Update(float deltaTime);
	virtual void PostUpdate(float deltaTime);
	virtual void Render(HDC hDC, float deltaTime);
};

