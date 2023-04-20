#pragma once
#include "GameObject.h"
class CFallingBomb :   public CGameObject
{
private:
	friend class CScene;
	float			m_Height;
	float			m_FallingSpeed;
protected:
	CFallingBomb();
	CFallingBomb(const CFallingBomb& obj);
	virtual ~CFallingBomb();
public:
	float GetHeight()	const
	{
		return m_Height;
	}
	void SetHeight(float height)
	{
		m_Height = height;
	}
	virtual bool Init();
	virtual void Update(float deltaTime);
	virtual void PostUpdate(float deltaTime);
	virtual void Render(HDC hDC, float deltaTime);
};

