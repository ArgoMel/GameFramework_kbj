#include "Collider.h"
#include "CollisionManager.h"

CCollider::CCollider()
	: m_scene(nullptr)
	, m_owner(nullptr)
	, m_colliderType(ECollider_Type::Box)
	, m_profile(nullptr)
	, m_bottom(0.f)
	, m_mouseCollision(false)
{
}

CCollider::CCollider(const CCollider& collider)
	: CRef(collider)
	, m_scene(nullptr)
	, m_owner(nullptr)
	, m_colliderType(collider.m_colliderType)
	, m_offset(collider.m_offset)
	, m_profile(collider.m_profile)
	, m_bottom(0.f)
	, m_mouseCollision(false)
{
}

CCollider::~CCollider()
{
	auto	iter = m_collisionList.begin();
	auto	iterEnd = m_collisionList.end();
	for (; iter != iterEnd; ++iter)
	{
		(*iter)->DeleteCollisionList(this);
	}
}

void CCollider::SetCollisionProfile(const std::string& name)
{
	m_profile = CCollisionManager::GetInst()->FindProfile(name);
}

void CCollider::AddCollisionList(CCollider* collider)
{
	m_collisionList.push_back(collider);
}

bool CCollider::CheckCollisionList(CCollider* collider)
{
	auto	iter = m_collisionList.begin();
	auto	iterEnd = m_collisionList.end();
	for (; iter != iterEnd; ++iter)
	{
		if (*iter == collider)
		{
			return true;
		}
	}
	return false;
}

void CCollider::DeleteCollisionList(CCollider* collider)
{
	auto	iter = m_collisionList.begin();
	auto	iterEnd = m_collisionList.end();
	for (; iter != iterEnd; ++iter)
	{
		if (*iter == collider)
		{
			m_collisionList.erase(iter);
			return;
		}
	}
}

void CCollider::ClearCollisionList()
{
	auto	iter = m_collisionList.begin();
	auto	iterEnd = m_collisionList.end();
	for (; iter != iterEnd; ++iter)
	{
		(*iter)->DeleteCollisionList(this);
	}
	m_collisionList.clear();
}

void CCollider::CallCollisionBegin(CCollider* dest)
{
	if (m_collisionBegin)
	{
		m_collisionBegin(this, dest);
	}
}

void CCollider::CallCollisionEnd(CCollider* dest)
{
	if (m_collisionEnd)
	{
		m_collisionEnd(this, dest);
	}
}

void CCollider::CallMouseCollisionBegin(const Vector2& mousePos)
{
	if (m_mouseCollisionBegin)
	{
		m_mouseCollisionBegin(this, mousePos);
	}
}

void CCollider::CallMouseCollisionEnd(const Vector2& mousePos)
{
	if (m_mouseCollisionEnd)
	{
		m_mouseCollisionEnd(this, mousePos);
	}
}

bool CCollider::Init()
{
	m_profile = CCollisionManager::GetInst()->FindProfile("Default");
	return true;
}

void CCollider::Update(float deltaTime)
{
}

void CCollider::PostUpdate(float deltaTime)
{
}

void CCollider::Render(HDC hDC, float deltaTime)
{
}

bool CCollider::Collision(CCollider* dest)
{
	return false;
}

bool CCollider::CollisionMouse(const Vector2& mouse)
{
	return false;
}
