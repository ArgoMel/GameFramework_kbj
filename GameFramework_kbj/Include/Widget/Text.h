#pragma once
#include "Widget.h"
class CText :public CWidget
{
protected:
	friend class CWidgetComponent;
	friend class CWidgetWindow;
    CSharedPtr<class CFont> m_font;
    TCHAR*                  m_text;
    COLORREF                m_textColor;
    COLORREF                m_shadowColor;
    Vector2                 m_shadowOffset;
    int                     m_count;
    int                     m_capacity;
    bool                    m_shadow;
	CText();
	CText(const CText& widget);
	virtual ~CText();
public:
    void SetText(const TCHAR* text)
    {
        int length = lstrlen(text);
        if (length + 1 > m_capacity)
        {
            m_capacity = length + 1;
            SAFE_DELETE_ARRAY(m_text);
            m_text = new TCHAR[m_capacity];
            memset(m_text, 0, sizeof(TCHAR) * m_capacity);
        }
        lstrcpy(m_text, text);
        m_count = lstrlen(m_text);
    }
    void SetTextColor(unsigned char r, unsigned char g, unsigned char b)
    {
        m_textColor = RGB(r, g, b);
    }
    void SetTextShadowColor(unsigned char r, unsigned char g, unsigned char b)
    {
        m_shadowColor = RGB(r, g, b);
    }
    void SetShadowOffset(float x, float y)
    {
        m_shadowOffset = Vector2(x, y);
    }
    void EnableShadow(bool Shadow)
    {
        m_shadow = Shadow;
    }
    void AddText(const TCHAR text)
    {
        int length = m_count + 1;
        if (length + 1 > m_capacity)
        {
            m_capacity = length + 1;
            TCHAR* newText = new TCHAR[m_capacity];
            memset(newText, 0, sizeof(TCHAR) * m_capacity);
            lstrcpy(newText, m_text);
            SAFE_DELETE_ARRAY(m_text);
            m_text = newText;
        }
        m_text[m_count] = text;
        ++m_count;
    }
    void AddText(const TCHAR* text)
    {
        int length = m_count + lstrlen(text);
        if (length + 1 > m_capacity)
        {
            m_capacity = length + 1;
            TCHAR* newText = new TCHAR[m_capacity];
            memset(newText, 0, sizeof(TCHAR) * m_capacity);
            lstrcpy(newText, m_text);
            SAFE_DELETE_ARRAY(m_text);
            m_text = newText;
        }
        lstrcat(m_text, text);
        m_count += lstrlen(text);
    }
    void pop_back()
    {
        --m_count;
        m_text[m_count] = 0;
    }
    void clear()
    {
        m_count = 0;
        m_text[m_count] = 0;
    }
    void SetFont(const std::string& name);
    virtual bool Init();
    virtual void Update(float deltaTime);
    virtual void PostUpdate(float deltaTime);
    virtual void Render(HDC hDC, float deltaTime);
    virtual void Render(HDC hDC, const Vector2& pos, float deltaTime);
};

