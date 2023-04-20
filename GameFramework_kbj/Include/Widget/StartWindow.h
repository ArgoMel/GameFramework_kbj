#pragma once
#include "WidgetWindow.h"

class CStartWindow : public CWidgetWindow
{
private:
	friend class CScene;
protected:
	CStartWindow();
	virtual ~CStartWindow();
	float       m_QuitTime;
	bool        m_IsQuit;
public:
	virtual bool Init();
	virtual void Update(float deltaTime);
	void StartButtonCallback();
	void TileButtonCallback();
	void EndButtonCallback();
};

