#pragma once
#include "WidgetWindow.h"
class CClearWindow :public CWidgetWindow
{
private:
	friend class CScene;
	CSharedPtr<class CImageWidget>		m_Image;
	Vector2       m_OutputSize;
protected:
	CClearWindow();
	virtual ~CClearWindow();
public:
	virtual bool Init();
	virtual void Update(float deltaTime);
};

