#pragma once
#include "Character.h"

class CPlayer :public CCharacter 
{
private:
	friend class CScene;
	CSharedPtr<class CColliderBox> box;
	CSharedPtr<class CCollider> m_EnemyCollider;
	CSharedPtr<class CUIObject> m_UIObj;
	CSharedPtr<class CGamePause> m_GamePause;
	std::list<CSharedPtr<class CWall>>	m_listWall;
	std::list<CSharedPtr<class CBomb>>  m_listBomb;
	std::vector<std::string>	m_vecSequenceKey[4];
	int		m_playerDir;
	int		m_bombCount;
	int		m_bombPower;
	int		m_speedCount;
	int		m_maxCount;
	int		m_KeyCount;
	float   m_CoolTime;
	float	m_InvisibleTime;	//무적시간
	bool m_canHorizon;
	bool m_canVertical;
	bool m_HaveNeedle;
	bool m_HaveDart;
	bool m_IsCheat;
	void MoveUp();
	void MoveDown();
	void MoveLeft();
	void MoveRight();
	void Bomb();
	void Skill1();
	void Skill2();
	void Die();
	void Result();
	void Idle();
	void YesHorizontal();
	void NoHorizontal();
	void YesVertical();
	void NoVertical();
	void PositionReset();
	void CheatMode();
	void Pause();
	void CollisionBegin(CCollider* src, CCollider* dest);
	void CollisionEnd(CCollider* src, CCollider* dest);
protected:
	CPlayer();
	CPlayer(const CPlayer& obj);
	virtual ~CPlayer();
public:
	int GetBombCount()	const
	{
		return m_bombCount;
	}
	int GetBombPower()	const
	{
		return m_bombPower;
	}
	int GetSpeedCount()	const
	{
		return m_speedCount;
	}
	void AddBombPower()
	{
		++m_bombPower;
	}
	virtual bool Init();
	virtual void Update(float deltaTime);
	virtual void PostUpdate(float deltaTime);
	virtual void Render(HDC hDC,float deltaTime);
	void SetSpeed();
};