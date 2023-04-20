#pragma once
#include "Widget.h"

enum class EProgressBar_Texture_Type
{
    Back,
    Bar,
    End
};

enum class EProgressBar_Dir
{
    LeftToRight,
    RightToLeft,
    BottomToTop,
    TopToBottom,
    End
};

class CProgressBar : public CWidget
{
protected:
    friend class CWidgetComponent;
    friend class CWidgetWindow;
    CSharedPtr<class CTexture>  m_texture[(int)EProgressBar_Texture_Type::End];
    EProgressBar_Dir    m_dir;
    Vector2             m_barSize;
    Vector2             m_barPos;
    float               m_value;    // 0 ~ 1 사이의 값
    CProgressBar();
    CProgressBar(const CProgressBar& widget);
    virtual ~CProgressBar();
public:
    void SetBarDir(EProgressBar_Dir dir)
    {
        m_dir = dir;
    }
    void SetValue(float value)
    {
        m_value = value;
        if (m_value > 1.f)
        {
            m_value = 1.f;
        }
        else if (m_value < 0.f)
        {
            m_value = 0.f;
        }
    }
    void AddValue(float value)
    {
        m_value += value;
        if (m_value > 1.f)
        {
            m_value = 1.f;
        }
        else if (m_value < 0.f)
        {
            m_value = 0.f;
        }
    }
    void SetTexture(EProgressBar_Texture_Type type, const std::string& name, const TCHAR* fileName,
        const std::string& pathName = TEXTURE_PATH);
    void SetTextureFullPath(EProgressBar_Texture_Type type, const std::string& name, const TCHAR* fullPath);
    void SetColorKey(EProgressBar_Texture_Type type, unsigned char r, unsigned char g, unsigned char b);
    virtual bool Init();
    virtual void Update(float deltaTime);
    virtual void PostUpdate(float deltaTime);
    virtual void Render(HDC hDC, float deltaTime);
    virtual void Render(HDC hDC, const Vector2& pos, float deltaTime);
#ifdef UNICODE
    void SetTexture(EProgressBar_Texture_Type type, const std::string& name, const std::vector<std::wstring>& vecFileName,
        const std::string& pathName = TEXTURE_PATH);
    void SetTextureFullPath(EProgressBar_Texture_Type type, const std::string& name, const std::vector<std::wstring>& vecFullPath);
#else
    void SetTexture(EProgressBar_Texture_Type type, const std::string& name, const std::vector<std::string>& vecFileName,
        const std::string& pathName = TEXTURE_PATH);
    void SetTextureFullPath(EProgressBar_Texture_Type type, const std::string& name, const std::vector<std::string>& vecFullPath);
#endif
};

