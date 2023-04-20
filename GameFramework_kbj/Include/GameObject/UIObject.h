#pragma once
#include "GameObject.h"
class CUIObject :public CGameObject
{
private:
	friend class CScene;
	CSharedPtr<class CWidgetComponent>  m_ItemIcon[4];
	CSharedPtr<class CWidgetComponent>  m_ItemCount[3];
	CSharedPtr<class CWidgetComponent>	m_CTImage;
	Vector2       m_OutputSize;
protected:
	CUIObject();
	CUIObject(const CUIObject& obj);
	virtual ~CUIObject();
public:
	virtual bool Init();
	virtual void Update(float deltaTime);
	virtual void PostUpdate(float deltaTime);
	virtual void Render(HDC hDC, float deltaTime);
	void SetCount(int index, int count);
	void StartCT();
};
