#pragma once
#include "Character.h"
class CBoss :public CCharacter
{
private:
	friend class CScene;
	CSharedPtr<class CColliderCircle> m_Circle;
	CSharedPtr<class CWidgetComponent>	m_HPBar;
	CSharedPtr<class CWidgetComponent>	m_nameBar;
	CSharedPtr<class CEffect>	m_Warning;
	std::list<CSharedPtr<class CMarker>>  m_listMarker;
	std::list<CSharedPtr<class CMonster>>  m_listMonster;
	std::vector<std::string>	m_vecSequenceKey[4];
	Vector2	m_dir;
	Vector2	m_PlayerPos;
	Vector2	m_RealSkillPos;
	Vector2	m_RealSkillDir;
	float	m_InvisibleTime;	//무적시간
	float	m_ChangeTime;		//애니메이션 변경시간
	float	m_ChargeTime;		//특수패턴 준비시간
	float	m_PatternDelay;		//패턴시작시간
	int		m_fireCount;		//패턴 3번쓰면 특수패턴쓰기 위함
	int		m_HP;
	int		m_HPMax;
	int		m_BossDir;
	bool	m_IsMarkerBreak;
	bool	m_IsPattern;
	void CollisionBegin(CCollider* src, CCollider* dest);
	void CollisionEnd(CCollider* src, CCollider* dest);
	void Die();
	void DieSound();
	void Recovery();
	void Fire();
	void Summon();
	void Geyser();
	void EXPattern();
protected:
	CBoss();
	CBoss(const CBoss& obj);
	virtual ~CBoss();
public:
	virtual bool Init();
	virtual void Update(float deltaTime);
	virtual void PostUpdate(float deltaTime);
	virtual void Render(HDC hDC, float deltaTime);
	virtual float InflictDamage(float damage);
};

