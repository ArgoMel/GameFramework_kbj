#pragma once
#include "WidgetWindow.h"
class CGamePause :public CWidgetWindow
{
private:
	friend class CScene;
	//CSharedPtr<class CImageWidget>		m_Game;
protected:
	CGamePause();
	virtual ~CGamePause();
public:
	virtual bool Init();
	virtual void Update(float deltaTime);
	virtual void PostUpdate(float deltaTime);
};

