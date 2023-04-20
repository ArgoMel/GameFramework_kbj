#pragma once
#include "GameObject.h"

class CEffect :public CGameObject
{
private:
	friend class CScene;
	EEffect_Type	m_effectType;
	float			m_duration;
	float			m_time;
protected:
	CEffect();
	CEffect(const CEffect& obj);
	virtual ~CEffect();
	void AnimationEnd();
public:
	EEffect_Type GetEffectType()	const
	{
		return m_effectType;
	}
	void SetDuration(float duration)
	{
		m_duration = duration;
	}
	virtual bool Init();
	virtual void Update(float deltaTime);
	virtual void PostUpdate(float deltaTime);
	virtual void Render(HDC hDC, float deltaTime);
};

