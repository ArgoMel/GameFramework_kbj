#pragma once
#include "GameObject.h"
class CKingSeal :public CGameObject
{
private:
	friend class CScene;
	CSharedPtr<class CColliderCircle> m_Circle;
	CSharedPtr<class CWidgetComponent>	m_HPBar;
	CSharedPtr<class CWidgetComponent>	m_nameBar;
	CSharedPtr<class CEffect>	m_Warning;
	std::list<CSharedPtr<class CMarker>>  m_listMarker;
	std::list<CSharedPtr<class CGamgyul_E>>  m_listMonster;
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
	int		m_RumbleCount;		//구르는 횟수
	int		m_HP;
	int		m_HPMax;
	int		m_BossDir;
	int		m_MarkerCount;
	bool	m_IsPattern;
	void CollisionBegin(CCollider* src, CCollider* dest);
	void CollisionEnd(CCollider* src, CCollider* dest);
	void Die();
	void DieSound();
	void Recovery();
	void Again();
	void Rumble();
	void Summon();
	void Falling();
	void EXPattern();
protected:
	CKingSeal();
	CKingSeal(const CKingSeal& obj);
	virtual ~CKingSeal();
public:
	virtual bool Init();
	virtual void Update(float deltaTime);
	virtual void PostUpdate(float deltaTime);
	virtual void Render(HDC hDC, float deltaTime);
	virtual float InflictDamage(float damage);
};

