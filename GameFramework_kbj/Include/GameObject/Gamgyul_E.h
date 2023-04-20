#pragma once
#include "GameObject.h"
class CGamgyul_E :public CGameObject
{
private:
	friend class CScene;
	CSharedPtr<class CEffect>	m_Effect;
	//std::list<CSharedPtr<class CWall>>	m_listWall;
	std::vector<std::string>	m_vecSequenceKey[4];
	Vector2	m_PlayerPos;
	Vector2	m_dir;
	float	m_ChangeTime;		//애니메이션 변경시간
	int		m_GamgyulDir;
	bool	m_IsPlayer;
	void CollisionBegin(CCollider* src, CCollider* dest);
	void CollisionEnd(CCollider* src, CCollider* dest);
	void Die();
	void DeleteEffect();
protected:
	CGamgyul_E();
	CGamgyul_E(const CGamgyul_E& obj);
	virtual ~CGamgyul_E();
public:
	virtual bool Init();
	virtual void Update(float deltaTime);
	virtual void PostUpdate(float deltaTime);
	virtual void Render(HDC hDC, float deltaTime);
};

