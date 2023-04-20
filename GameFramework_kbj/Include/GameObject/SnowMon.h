#pragma once
#include "GameObject.h"

class CSnowMon :public CGameObject
{
private:
	friend class CScene;
	CSharedPtr<class CEffect>	m_Effect;
	std::vector<std::string>	m_vecSequenceKey[4];
	Vector2	m_PlayerPos;
	Vector2	m_dir;
	float	m_ChangeTime;		//애니메이션 변경시간
	int		m_MonsterDir;
	void CollisionBegin(CCollider* src, CCollider* dest);
	void CollisionEnd(CCollider* src, CCollider* dest);
	void Die();
	void CreateItem();
protected:
	CSnowMon();
	CSnowMon(const CSnowMon& obj);
	virtual ~CSnowMon();
public:
	virtual bool Init();
	virtual void Update(float deltaTime);
	virtual void PostUpdate(float deltaTime);
	virtual void Render(HDC hDC, float deltaTime);
};

