#pragma once
#include "../Ref.h"
#include "Widget.h"

class CWidgetWindow : public CRef
{
private:
    friend class CScene;
    static bool SortCollisionWidget(const CSharedPtr<class CWidget>& src,const CSharedPtr<class CWidget>& dest);
    static bool SortWidget(const CSharedPtr<class CWidget>& src,const CSharedPtr<class CWidget>& dest);
protected:
    class CScene* m_scene;
    Vector2     m_pos;
    Vector2     m_size;
    std::vector<CSharedPtr<class CWidget>>  m_vecWidget;
    int         m_zOrder;
	CWidgetWindow();
	virtual ~CWidgetWindow();
public:
    const Vector2& GetPos()	const
    {
        return m_pos;
    }
    const Vector2& GetSize()	const
    {
        return m_size;
    }
    class CWidget* GetWidget(int index)
    {
        return m_vecWidget[index];
    }
    int GetWidgetCount()    const
    {
        return (int)m_vecWidget.size();
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
    void SetPos(const Vector2& pos)
    {
        m_pos = pos;
    }
    void SetSize(float x, float y)
    {
        m_size.x = x;
        m_size.y = y;
    }
    void SetSize(const Vector2& size)
    {
        m_size = size;
    }
    void SetZOrder(int zOrder)
    {
        m_zOrder = zOrder;
    }
    virtual bool Init();
    virtual void Update(float deltaTime);
    virtual void PostUpdate(float deltaTime);
    virtual void Render(HDC hDC, float deltaTime);
    void SortCollision();
    bool CollisionMouse(class CWidget** widget, const Vector2& pos);
    bool CheckWidget(CWidget* widget)
    {
        size_t  size = m_vecWidget.size();
        for (size_t i = 0; i < size; ++i)
        {
            if (m_vecWidget[i] == widget)
            {
                return true;
            }
        }
        return false;
    }
    template <typename T>
    T* FindWidget(const std::string& name)
    {
        size_t  size = m_vecWidget.size();
        for (size_t i = 0; i < size; ++i)
        {
            if (m_vecWidget[i]->GetName() == name)
            {
                return (T*)m_vecWidget[i].Get();
            }
        }
        return nullptr;
    }
    template <typename T>
    T* CreateWidget(const std::string& name)
    {
        T* widget = new T;
        widget->SetName(name);
        widget->m_scene = m_scene;
        widget->m_owner = this;
        if (!widget->Init())
        {
            SAFE_DELETE(widget);
            return nullptr;
        }
        m_vecWidget.push_back(widget);
        return (T*)widget;
    }
};

