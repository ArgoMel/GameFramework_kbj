#pragma once
#include "WidgetWindow.h"
class CGameOver : public CWidgetWindow
{
private:
	friend class CScene;
	CSharedPtr<class CButton>		m_ExitButton;
	CSharedPtr<class CImageWidget>		m_Game;
	CSharedPtr<class CImageWidget>		m_Over;
	float       m_ImageMaxY;		//이미지 Y위치의 최대값
protected:
	CGameOver();
	virtual ~CGameOver();
public:
	virtual bool Init();
	virtual void Update(float deltaTime);
	virtual void PostUpdate(float deltaTime);
	void RetryButtonCallback();
	void EndButtonCallback();
};