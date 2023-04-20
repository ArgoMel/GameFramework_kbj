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
    Vector2            m_offset;    // Owner�κ��� �󸶸�ŭ ������ ������.
    Vector2            m_hitPoint;
    CollisionProfile* m_profile;
    // �Լ������Ϳ��� CCollider* 2���� �޴� ������ ���� �浹�� �� ��ü�� ���ڷ� �Ѱ��ֱ� ���ؼ��̴�.
    std::function<void(CCollider*, CCollider*)> m_collisionBegin;
    std::function<void(CCollider*, CCollider*)> m_collisionEnd;
    std::function<void(CCollider*, const Vector2&)> m_mouseCollisionBegin;
    std::function<void(CCollider*, const Vector2&)> m_mouseCollisionEnd;
    /*
    ���� �����ӿ� �� ��ü�� �浹�ǰ� ���� �����ӿ��� �� ��ü�� �浹�� �Ǿ��ٸ� ��� �浹�� �ǰ� �ִ� ���·�
    �Ǵ��ؾ� �Ѵ�.
    �׷��� �̷� �Ǵ��� �ϱ� ���ؼ��� ���� �����ӿ��� �� ��ü�� ���� �浹�� �Ǿ������� ���� ������ �ʿ��� ���̴�.
    �׷��Ƿ� �浹ü�� ���� �����ӿ� �浹�Ǿ��� �浹ü�� ��Ƶ� �ʿ䰡 �ִ�.
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