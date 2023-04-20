#pragma once
#include "GameObject.h"
class CEmperorPenguin :public CGameObject
{
private:
	friend class CScene;
	CSharedPtr<class CColliderCircle> m_Circle;
	CSharedPtr<class CWidgetComponent>	m_HPBar;
	CSharedPtr<class CWidgetComponent>	m_nameBar;
	CSharedPtr<class CEffect>	m_Effect;
	CSharedPtr<class CEffect>	m_Warning;
	std::list<CSharedPtr<class CMarker>>  m_listMarker;
	std::list<CSharedPtr<class CSnowMon>>  m_listMonster;
	std::vector<std::string>	m_vecSequenceKey[4];
	Vector2	m_dir;
	Vector2	m_PlayerPos;
	Vector2	m_RealSkillPos;
	Vector2	m_RealSkillDir;
	float	m_InvisibleTime;	//�����ð�
	float	m_ChangeTime;		//�ִϸ��̼� ����ð�
	float	m_ChargeTime;		//Ư������ �غ�ð�
	float	m_DuringTime;		//Ư������ ���ӽð�
	float	m_PatternDelay;		//���Ͻ��۽ð�
	int		m_fireCount;		//���� 3������ Ư�����Ͼ��� ����
	int		m_HP;
	int		m_HPMax;
	int		m_BossDir;
	int		m_MarkerCount;
	int		m_ExplosionCount;
	bool	m_IsPattern;
	void CollisionBegin(CCollider* src, CCollider* dest);
	void CollisionEnd(CCollider* src, CCollider* dest);
	void Die();
	void DieSound();
	void Recovery();
	void TrippleExplosion();
	void Summon();
	void GuidedExplosion();
	void EXPattern();
protected:
	CEmperorPenguin();
	CEmperorPenguin(const CEmperorPenguin& obj);
	virtual ~CEmperorPenguin();
public:
	virtual bool Init();
	virtual void Update(float deltaTime);
	virtual void PostUpdate(float deltaTime);
	virtual void Render(HDC hDC, float deltaTime);
	virtual float InflictDamage(float damage);
};

