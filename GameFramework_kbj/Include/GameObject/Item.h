#pragma once
#include "GameObject.h"
class CItem : public CGameObject
{
private:
	friend class CScene;
	float m_InvisibleTime;
	bool m_CanDelete;
	void CollisionBegin(CCollider* src, CCollider* dest);
	void CollisionEnd(CCollider* src, CCollider* dest);
protected:
	CItem();
	CItem(const CItem& obj);
	~CItem();
public:
	void SetCanDelete(bool b)
	{
		m_CanDelete = b;
	}
	virtual bool Init();
	virtual void Update(float deltaTime);
	virtual void PostUpdate(float deltaTime);
	virtual void Render(HDC hDC, float deltaTime);
};

