#pragma once
#include "../GameInfo.h"
#include "../SingletonMacro.h"

class CCollisionManager
{
	DECLARE_SINGLE(CCollisionManager)
private:
	std::unordered_map<std::string, CollisionProfile*>	m_mapProfile;
public:
	bool Init();
	bool CreateProfile(const std::string& name, ECollision_Channel channel, bool enable,
		ECollision_Interaction baseIteraction = ECollision_Interaction::Collision);
	bool SetCollisionInteraction(const std::string& name, ECollision_Channel channel,ECollision_Interaction iteraction);
	CollisionProfile* FindProfile(const std::string& name);
	bool CollisionBoxToBox(Vector2& hitPoint, class CColliderBox* src, class CColliderBox* dest);
	bool CollisionBoxToBox(Vector2& hitPoint, const BoxInfo& src, const BoxInfo& dest);
	bool CollisionCircleToCircle(Vector2& hitPoint, class CColliderCircle* src, class CColliderCircle* dest);
	bool CollisionCircleToCircle(Vector2& hitPoint, const CircleInfo& src, const CircleInfo& dest);
	bool CollisionBoxToCircle(Vector2& hitPoint, class CColliderBox* Src, class CColliderCircle* Dest);
	bool CollisionBoxToCircle(Vector2& hitPoint, const BoxInfo& src, const CircleInfo& dest);
	bool CollisionPointToBox(Vector2& hitPoint, const Vector2& src, class CColliderBox* dest);
	bool CollisionPointToBox(Vector2& hitPoint, const Vector2& src, const BoxInfo& dest);
	bool CollisionPointToCircle(Vector2& hitPoint, const Vector2& src, class CColliderCircle* dest);
	bool CollisionPointToCircle(Vector2& hitPoint, const Vector2& src, const CircleInfo& dest);
};

