#include "CollisionManager.h"
#include "ColliderBox.h"
#include "ColliderCircle.h"

DEFINITION_SINGLE(CCollisionManager)

CCollisionManager::CCollisionManager()
{
}

CCollisionManager::~CCollisionManager()
{
	auto	iter = m_mapProfile.begin();
	auto	iterEnd = m_mapProfile.end();
	for (; iter != iterEnd; ++iter)
	{
		SAFE_DELETE(iter->second);
	}
}

bool CCollisionManager::Init()
{
	CreateProfile("Default", ECollision_Channel::Default, true);
	CreateProfile("Player", ECollision_Channel::Player, true, ECollision_Interaction::Ignore);
	CreateProfile("Monster", ECollision_Channel::Monster, true, ECollision_Interaction::Ignore);
	CreateProfile("PlayerAttack", ECollision_Channel::PlayerAttack, true);
	CreateProfile("MonsterAttack", ECollision_Channel::MonsterAttack, true, ECollision_Interaction::Ignore);
	CreateProfile("Mouse", ECollision_Channel::Mouse, true, ECollision_Interaction::Collision);
	CreateProfile("Item", ECollision_Channel::Item, true, ECollision_Interaction::Ignore);
	CreateProfile("Bubble", ECollision_Channel::Bubble, true, ECollision_Interaction::Ignore);
	CreateProfile("Wall", ECollision_Channel::Wall, true, ECollision_Interaction::Ignore);
	CreateProfile("Event", ECollision_Channel::Event, true, ECollision_Interaction::Ignore);

	SetCollisionInteraction("Player", ECollision_Channel::Default, ECollision_Interaction::Collision);
	SetCollisionInteraction("Player", ECollision_Channel::MonsterAttack, ECollision_Interaction::Collision);
	SetCollisionInteraction("Player", ECollision_Channel::Monster, ECollision_Interaction::Collision);
	SetCollisionInteraction("Player", ECollision_Channel::PlayerAttack, ECollision_Interaction::Collision);
	SetCollisionInteraction("Player", ECollision_Channel::Item, ECollision_Interaction::Collision);
	SetCollisionInteraction("Player", ECollision_Channel::Wall, ECollision_Interaction::Collision);
	SetCollisionInteraction("Monster", ECollision_Channel::Default, ECollision_Interaction::Collision);
	SetCollisionInteraction("Monster", ECollision_Channel::PlayerAttack, ECollision_Interaction::Collision);
	SetCollisionInteraction("Monster", ECollision_Channel::Player, ECollision_Interaction::Collision);
	SetCollisionInteraction("Monster", ECollision_Channel::Wall, ECollision_Interaction::Collision);
	SetCollisionInteraction("PlayerAttack", ECollision_Channel::Default, ECollision_Interaction::Collision);
	SetCollisionInteraction("PlayerAttack", ECollision_Channel::Player, ECollision_Interaction::Collision);
	SetCollisionInteraction("PlayerAttack", ECollision_Channel::MonsterAttack, ECollision_Interaction::Collision);
	SetCollisionInteraction("PlayerAttack", ECollision_Channel::Monster, ECollision_Interaction::Collision);
	SetCollisionInteraction("PlayerAttack", ECollision_Channel::Wall, ECollision_Interaction::Collision);
	SetCollisionInteraction("PlayerAttack", ECollision_Channel::Event, ECollision_Interaction::Collision);
	SetCollisionInteraction("MonsterAttack", ECollision_Channel::Default, ECollision_Interaction::Collision);
	SetCollisionInteraction("MonsterAttack", ECollision_Channel::Player, ECollision_Interaction::Collision);
	SetCollisionInteraction("MonsterAttack", ECollision_Channel::PlayerAttack, ECollision_Interaction::Collision);
	SetCollisionInteraction("MonsterAttack", ECollision_Channel::Item, ECollision_Interaction::Collision);
	SetCollisionInteraction("MonsterAttack", ECollision_Channel::Wall, ECollision_Interaction::Collision);
	SetCollisionInteraction("MonsterAttack", ECollision_Channel::Event, ECollision_Interaction::Collision);
	SetCollisionInteraction("Mouse", ECollision_Channel::Default, ECollision_Interaction::Ignore);
	SetCollisionInteraction("Mouse", ECollision_Channel::Item, ECollision_Interaction::Ignore);
	SetCollisionInteraction("Item", ECollision_Channel::Default, ECollision_Interaction::Collision);
	SetCollisionInteraction("Item", ECollision_Channel::Player, ECollision_Interaction::Collision);
	SetCollisionInteraction("Item", ECollision_Channel::PlayerAttack, ECollision_Interaction::Collision);
	SetCollisionInteraction("Item", ECollision_Channel::MonsterAttack, ECollision_Interaction::Collision);
	SetCollisionInteraction("Bubble", ECollision_Channel::Wall, ECollision_Interaction::Collision);
	SetCollisionInteraction("Wall", ECollision_Channel::Default, ECollision_Interaction::Collision);
	SetCollisionInteraction("Wall", ECollision_Channel::MonsterAttack, ECollision_Interaction::Collision);
	SetCollisionInteraction("Wall", ECollision_Channel::Monster, ECollision_Interaction::Collision);
	SetCollisionInteraction("Wall", ECollision_Channel::PlayerAttack, ECollision_Interaction::Collision);
	SetCollisionInteraction("Wall", ECollision_Channel::Player, ECollision_Interaction::Collision);
	SetCollisionInteraction("Wall", ECollision_Channel::Bubble, ECollision_Interaction::Collision);
	SetCollisionInteraction("Event", ECollision_Channel::Default, ECollision_Interaction::Collision);
	SetCollisionInteraction("Event", ECollision_Channel::PlayerAttack, ECollision_Interaction::Collision);
	SetCollisionInteraction("Event", ECollision_Channel::MonsterAttack, ECollision_Interaction::Collision);
	return true;
}

bool CCollisionManager::CreateProfile(const std::string& name, ECollision_Channel channel, bool enable, 
	ECollision_Interaction baseIteraction)
{
	CollisionProfile* profile = FindProfile(name);
	if (profile)
	{
		return false;
	}
	profile = new CollisionProfile;
	profile->name = name;
	profile->channel = channel;
	profile->enable = enable;
	profile->vecCollisionInteraction.resize((size_t)ECollision_Channel::Max);

	for (int i = 0; i < (int)ECollision_Channel::Max; ++i)
	{
		profile->vecCollisionInteraction[i] = baseIteraction;
	}
	m_mapProfile.insert(std::make_pair(name, profile));
	return true;
}

bool CCollisionManager::SetCollisionInteraction(const std::string& name, ECollision_Channel channel, ECollision_Interaction iteraction)
{
	CollisionProfile* profile = FindProfile(name);
	if (!profile)
	{
		return false;
	}
	profile->vecCollisionInteraction[(int)channel] = iteraction;
	return true;
}

CollisionProfile* CCollisionManager::FindProfile(const std::string& name)
{
	auto	iter = m_mapProfile.find(name);
	if (iter == m_mapProfile.end())
	{
		return nullptr;
	}
	return iter->second;
}

bool CCollisionManager::CollisionBoxToBox(Vector2& hitPoint, CColliderBox* src, CColliderBox* dest)
{
	if (CollisionBoxToBox(hitPoint, src->GetInfo(), dest->GetInfo()))
	{
		dest->m_hitPoint = hitPoint;
		return true;
	}
	return false;
}

bool CCollisionManager::CollisionBoxToBox(Vector2& hitPoint, const BoxInfo& src, const BoxInfo& dest)
{
	if (src.LT.x > dest.RB.x)
	{
		return false;
	}
	else if (src.LT.y > dest.RB.y)
	{
		return false;
	}
	else if (src.RB.x < dest.LT.x)
	{
		return false;
	}
	else if (src.RB.y < dest.LT.y)
	{
		return false;
	}
	float left = src.LT.x > dest.LT.x ? src.LT.x : dest.LT.x;
	float top = src.LT.y > dest.LT.y ? src.LT.y : dest.LT.y;
	float right = src.RB.x < dest.RB.x ? src.RB.x : dest.RB.x;
	float bottom = src.RB.y < dest.RB.y ? src.RB.y : dest.RB.y;
	hitPoint.x = (left + right) / 2.f;
	hitPoint.y = (top + bottom) / 2.f;
	return true;
}

bool CCollisionManager::CollisionCircleToCircle(Vector2& hitPoint, CColliderCircle* src, CColliderCircle* dest)
{
	if (CollisionCircleToCircle(hitPoint, src->GetInfo(), dest->GetInfo()))
	{
		dest->m_hitPoint = hitPoint;
		return true;
	}
	return false;
}

bool CCollisionManager::CollisionCircleToCircle(Vector2& hitPoint, const CircleInfo& src, const CircleInfo& dest)
{
	float dist = src.center.Distance(dest.center);
	bool result = dist <= src.radius + dest.radius;
	hitPoint = (src.center + dest.center) / 2.f;
	return result;
}

bool CCollisionManager::CollisionBoxToCircle(Vector2& hitPoint, CColliderBox* Src, CColliderCircle* Dest)
{
	if (CollisionBoxToCircle(hitPoint, Src->GetInfo(), Dest->GetInfo()))
	{
		Dest->m_hitPoint = hitPoint;
		return true;
	}
	return false;
}

bool CCollisionManager::CollisionBoxToCircle(Vector2& hitPoint, const BoxInfo& src, const CircleInfo& dest)
{
	// 원의 중점이 사각형의 꼭지점보다 면의 더 가깝다면
	if ((src.LT.x <= dest.center.x && dest.center.x <= src.RB.x) ||	(src.LT.y <= dest.center.y && dest.center.y <= src.RB.y))
	{
		// 사각형을 원의 반지름만큼 확장한다.
		BoxInfo	RC = src;
		RC.LT.x -= dest.radius;
		RC.LT.y -= dest.radius;
		RC.RB.x += dest.radius;
		RC.RB.y += dest.radius;
		// 확장된 사각형 안에 원의 중점이 들어온다면 충돌된 것이다.
		if (RC.LT.x > dest.center.x)
		{
			return false;
		}
		else if (RC.LT.y > dest.center.y)
		{
			return false;
		}
		else if (RC.RB.x < dest.center.x)
		{
			return false;
		}
		else if (RC.RB.y < dest.center.y)
		{
			return false;
		}
		BoxInfo	circleBox;
		circleBox.LT = dest.center - dest.radius;
		circleBox.RB = dest.center + dest.radius;
		float left = src.LT.x > circleBox.LT.x ? src.LT.x : circleBox.LT.x;
		float top = src.LT.y > circleBox.LT.y ? src.LT.y : circleBox.LT.y;
		float right = src.RB.x < circleBox.RB.x ? src.RB.x : circleBox.RB.x;
		float bottom = src.RB.y < circleBox.RB.y ? src.RB.y : circleBox.RB.y;
		hitPoint.x = (left + right) / 2.f;
		hitPoint.y = (top + bottom) / 2.f;
		return true;
	}
	//사각형의 꼭짓점 좌표배열
	Vector2	pos[4] ={src.LT,Vector2(src.RB.x, src.LT.y),Vector2(src.LT.x, src.RB.y),src.RB};
	// 4개의 점중 하나라도 원 안에 들어온다면 충돌한 것이다.
	for (int i = 0; i < 4; ++i)
	{
		float dist = dest.center.Distance(pos[i]);
		if (dist <= dest.radius)
		{
			BoxInfo	circleBox;
			circleBox.LT = dest.center - dest.radius;
			circleBox.RB = dest.center + dest.radius;
			float left = src.LT.x > circleBox.LT.x ? src.LT.x : circleBox.LT.x;
			float top = src.LT.y > circleBox.LT.y ? src.LT.y : circleBox.LT.y;
			float right = src.RB.x < circleBox.RB.x ? src.RB.x : circleBox.RB.x;
			float bottom = src.RB.y < circleBox.RB.y ? src.RB.y : circleBox.RB.y;
			hitPoint.x = (left + right) / 2.f;
			hitPoint.y = (top + bottom) / 2.f;
			return true;
		}
	}
	return false;
}

bool CCollisionManager::CollisionPointToBox(Vector2& hitPoint, const Vector2& src, CColliderBox* dest)
{
	if (CollisionPointToBox(hitPoint, src, dest->GetInfo()))
	{
		dest->m_hitPoint = hitPoint;
		return true;
	}
	return false;
}

bool CCollisionManager::CollisionPointToBox(Vector2& hitPoint, const Vector2& src, const BoxInfo& dest)
{
	if (dest.LT.x > src.x)
	{
		return false;
	}
	else if (dest.LT.y > src.y)
	{
		return false;
	}
	else if (dest.RB.x < src.x)
	{
		return false;
	}
	else if (dest.RB.y < src.y)
	{
		return false;
	}
	hitPoint = src;
	return true;
}

bool CCollisionManager::CollisionPointToCircle(Vector2& hitPoint, const Vector2& src, CColliderCircle* dest)
{
	if (CollisionPointToCircle(hitPoint, src, dest->GetInfo()))
	{
		dest->m_hitPoint = hitPoint;
		return true;
	}
	return false;
}

bool CCollisionManager::CollisionPointToCircle(Vector2& hitPoint, const Vector2& src, const CircleInfo& dest)
{
	float dist = dest.center.Distance(src);
	if (dist <= dest.radius)
	{
		hitPoint = src;
		return true;
	}
	return false;
}
