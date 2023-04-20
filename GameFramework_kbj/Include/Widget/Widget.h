#pragma once
#include "../Ref.h"

class CWidget :public CRef
{
protected:
    friend class CWidgetComponent;
	friend class CWidgetWindow;
    class CScene* m_scene;
    class CWidgetWindow* m_owner;
    Vector2 m_pos;
    Vector2 m_size;
    int     m_zOrder;   //위젯간의 위아래 순서 조정
    bool    m_mouseHovered;
	CWidget();
	CWidget(const CWidget& widget);
	virtual ~CWidget();
public:
    const Vector2& GetPos()	const
    {
        return m_pos;
    }
    const Vector2& GetSize()	const
    {
        return m_size;
    }
    int GetZOrder() const
    {
        return m_zOrder;
    }
    void SetPos(float x, float y)
    {
        m_pos.x = x;
        m_pos.y = y;
    }
    void SetPos(const Vector2& Pos)
    {
        m_pos = Pos;
    }
    void SetSize(float x, float y)
    {
        m_size.x = x;
        m_size.y = y;
    }
    void SetSize(const Vector2& Size)
    {
        m_size = Size;
    }
    void SetZOrder(int zOrder)
    {
        m_zOrder = zOrder;
    }
    virtual bool Init();
    virtual void Update(float deltaTime);
    virtual void PostUpdate(float deltaTime);
    virtual void Render(HDC hDC, float deltaTime);
    virtual void Render(HDC hDC, const Vector2& pos, float deltaTime);
    bool CollisionMouse(const Vector2& pos);
    virtual void CollisionMouseHoveredCallback(const Vector2& pos);
    virtual void CollisionMouseReleaseCallback();
};

