#pragma once
#include "../Ref.h"

class CCollider :public CRef
{
protected:
	friend class CGameObject;
    friend class CCollisionManager;
    class CScene* m_scene;
    class CGameObject* m_owner;
    ECollider_Type     m_colliderType;
    Vector2            m_pos;
    Vector2            m_offset;    // Owner로부터 얼마만큼 떨어져 있을지.
    Vector2            m_hitPoint;
    CollisionProfile* m_profile;
    // 함수포인터에서 CCollider* 2개를 받는 이유는 서로 충돌된 두 물체를 인자로 넘겨주기 위해서이다.
    std::function<void(CCollider*, CCollider*)> m_collisionBegin;
    std::function<void(CCollider*, CCollider*)> m_collisionEnd;
    std::function<void(CCollider*, const Vector2&)> m_mouseCollisionBegin;
    std::function<void(CCollider*, const Vector2&)> m_mouseCollisionEnd;
    /*
    현재 프레임에 두 물체가 충돌되고 다음 프레임에도 두 물체가 충돌이 되었다면 계속 충돌이 되고 있는 상태로
    판단해야 한다.
    그런데 이런 판단을 하기 위해서는 이전 프레임에서 두 물체가 서로 충돌이 되었는지에 대한 정보가 필요할 것이다.
    그러므로 충돌체는 이전 프레임에 충돌되었던 충돌체를 담아둘 필요가 있다.
    */
    std::list<CSharedPtr<CCollider>>    m_collisionList;
    float               m_bottom;
    bool                m_mouseCollision;
	CCollider();
	CCollider(const CCollider& collider);
	virtual ~CCollider() = 0;
public:
    class CScene* GetScene()    const
    {
        return m_scene;
    }
    class CGameObject* GetOwner()   const
    {
        return m_owner;
    }
    ECollider_Type GetColliderType()    const
    {
        return m_colliderType;
    }
    const Vector2& GetHitPoint()   const
    {
        return m_hitPoint;
    }
    const CollisionProfile* GetProfile()    const
    {
        return m_profile;
    }
    float GetBottom()   const
    {
        return m_bottom;
    }
    bool GetMouseCollision()    const
    {
        return m_mouseCollision;
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
    void SetOffset(const Vector2& offset)
    {
        m_offset = offset;
    }
    void SetOffset(float x, float y)
    {
        m_offset = Vector2(x, y);
    }
    void SetMouseCollision(bool collision)
    {
        m_mouseCollision = collision;
    }
    void SetCollisionProfile(const std::string& name);
    void AddCollisionList(CCollider* collider);
    bool CheckCollisionList(CCollider* collider);
    void DeleteCollisionList(CCollider* collider);
    void ClearCollisionList();
    void CallCollisionBegin(CCollider* dest);
    void CallCollisionEnd(CCollider* dest);
    void CallMouseCollisionBegin(const Vector2& mousePos);
    void CallMouseCollisionEnd(const Vector2& mousePos);
    virtual bool Init();
    virtual void Update(float deltaTime);
    virtual void PostUpdate(float deltaTime);
    virtual void Render(HDC hDC, float deltaTime);
    virtual bool Collision(CCollider* dest);
    virtual bool CollisionMouse(const Vector2& mouse);
    template <typename T>
    void SetCollisionBeginFunction(T* obj, void(T::* func)(CCollider*, CCollider*))
    {
        m_collisionBegin = std::bind(func, obj, std::placeholders::_1, std::placeholders::_2);
    }
    template <typename T>
    void SetCollisionEndFunction(T* obj, void(T::* func)(CCollider*, CCollider*))
    {
        m_collisionEnd = std::bind(func, obj, std::placeholders::_1, std::placeholders::_2);
    }
    template <typename T>
    void SetMouseCollisionBeginFunction(T* obj, void(T::* func)(CCollider*, const Vector2&))
    {
        m_mouseCollisionBegin = std::bind(func, obj, std::placeholders::_1, std::placeholders::_2);
    }
    template <typename T>
    void SetMouseCollisionEndFunction(T* obj, void(T::* func)(CCollider*, const Vector2&))
    {
        m_mouseCollisionEnd = std::bind(func, obj, std::placeholders::_1, std::placeholders::_2);
    }
};