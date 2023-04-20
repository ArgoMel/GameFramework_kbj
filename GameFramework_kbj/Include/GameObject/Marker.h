#pragma once
#include "GameObject.h"
class CMarker :public CGameObject
{
private:
	friend class CScene;
	CSharedPtr<class CWidgetComponent>	m_TimeText;
	float m_Time;
	bool m_IsBreak;
	void CollisionBegin(CCollider* src, CCollider* dest);
	void CollisionEnd(CCollider* src, CCollider* dest);
	void Die();
	void CheckBreak();
protected:
	CMarker();
	CMarker(const CMarker& obj);
	~CMarker();
public:
	float GetTime()	const
	{
		return m_Time;
	}
	bool GetIsBreak()	const
	{
		return m_IsBreak;
	}
	void SetTime(float time)
	{
		m_Time = time+0.9f;
	}
	void SetIsBreak(bool b)
	{
		m_IsBreak = b;
	}
	virtual bool Init();
	virtual void Update(float deltaTime);
	virtual void PostUpdate(float deltaTime);
	virtual void Render(HDC hDC, float deltaTime);
	void DeactiveText();
};

