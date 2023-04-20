#pragma once
#include "WidgetWindow.h"
class CGameWin :public CWidgetWindow
{
private:
	friend class CScene;
	CSharedPtr<class CImageWidget>		m_Win;
	CSharedPtr<class CButton>		m_ExitButton;
	float       m_ImageMaxY;		//이미지 Y위치의 최대값
protected:
	CGameWin();
	virtual ~CGameWin();
public:
	virtual bool Init();
	virtual void Update(float deltaTime);
	virtual void PostUpdate(float deltaTime);
	void NextButtonCallback();
	void EndButtonCallback();
};

