#pragma once
#include "WidgetWindow.h"
class CGameStart :public CWidgetWindow
{
private:
	friend class CScene;
	CSharedPtr<class CBoss>	m_Boss;
	CSharedPtr<class CKingSeal>	m_Seal;
	CSharedPtr<class CEmperorPenguin>	m_Penguin;
	float       m_ImageMaxY;		//�̹��� Y��ġ�� �ִ밪
	float       m_ExistTime;		//�����ϴ� �ð�
protected:
	CGameStart();
	virtual ~CGameStart();
public:
	virtual bool Init();
	virtual void Update(float deltaTime);
};

