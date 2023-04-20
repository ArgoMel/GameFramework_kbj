#pragma once
#include "WidgetWindow.h"

class CItemHUD :public CWidgetWindow
{
protected:
    friend class CScene;
    CSharedPtr<class CNumber>   m_minute;
    CSharedPtr<class CNumber>   m_second;
    float       m_time;
    float       m_QuitTime;
    bool        m_IsQuit;
    CItemHUD();
    virtual ~CItemHUD();
public:
    virtual bool Init();
    virtual void Update(float deltaTime);
    void EndButtonCallback();
};