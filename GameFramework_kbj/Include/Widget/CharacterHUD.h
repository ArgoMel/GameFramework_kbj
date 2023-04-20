#pragma once
#include "WidgetWindow.h"
class CCharacterHUD :public CWidgetWindow
{
protected:
    friend class CScene;
    CSharedPtr<class CProgressBar>  m_HPBar;
    CSharedPtr<class CImageWidget>  m_HPBarFrame;
    CSharedPtr<class CText>         m_FPSText;
    CCharacterHUD();
    virtual ~CCharacterHUD();
public:
    void SetHP(float HP);
    virtual bool Init();
    virtual void Update(float deltaTime);
};

