#pragma once
#include "WidgetWindow.h"
class CGameStart :public CWidgetWindow
{
private:
	friend class CScene;
	CSharedPtr<class CBoss>	m_Boss;
	CSharedPtr<class CKingSeal>	m_Seal;
	CSharedPtr<class CEmperorPenguin>	m_Penguin;
	float       m_ImageMaxY;		//이미지 Y위치의 최대값
	float       m_ExistTime;		//존재하는 시간
protected:
	CGameStart();
	virtual ~CGameStart();
public:
	virtual bool Init();
	virtual void Update(float deltaTime);
};

