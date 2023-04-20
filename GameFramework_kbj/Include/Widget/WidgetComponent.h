#pragma once
#include "../Ref.h"

class CWidgetComponent : public CRef
{
private:
	friend class CGameObject;
	class CGameObject* m_owner;
	class CScene* m_scene;
	CSharedPtr<class CWidget>   m_widget;
	Vector2     m_pos;
protected:
	CWidgetComponent();
	CWidgetComponent(const CWidgetComponent& widget);
	virtual ~CWidgetComponent();
public:
    class CWidget* GetWidget()  const
    {
        return m_widget;
    }
    Vector2 GetPos() const;
    float GetBottom()   const;
    void SetWidget(class CWidget* widget);
    void SetPos(float x, float y)
    {
        m_pos = Vector2(x, y);
    }

    void SetPos(const Vector2& pos)
    {
        m_pos = pos;
    }
    virtual bool Init();
    virtual void Update(float deltaTime);
    virtual void PostUpdate(float deltaTime);
    virtual void Render(HDC hDC, float deltaTime);
    template <typename T>
    T* GetWidget()  const
    {
        return (T*)m_widget.Get();
    }
    template <typename T>
    T* CreateWidget(const std::string& name)
    {
        T* widget = new T;
        widget->SetName(name);
        widget->m_scene = m_scene;
        if (!widget->Init())
        {
            SAFE_DELETE(widget);
            return nullptr;
        }
        m_widget = widget;
        return (T*)widget;
    }
};

