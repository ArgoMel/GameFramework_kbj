#pragma once
#include "AnimationInfo.h"

class CAnimation
{
private:
	friend class CGameObject;
	class CGameObject* m_owner;
	class CScene* m_scene;
	CAnimationInfo* m_currentAnimation;
	std::function<void()>	m_currentAnimationEndFunc;
	std::unordered_map<std::string, CAnimationInfo*>	m_mapAnimation;
	CAnimation();
	~CAnimation();
	CAnimationInfo* FindInfo(const std::string& name);
public:
	void AddAnimation(const std::string& sequenceName, bool loop = true,float playTime = 1.f, float playScale = 1.f,
		bool reverse = false);
	void SetPlayTime(const std::string& name, float playTime);
	void SetPlayScale(const std::string& name, float playScale);
	void SetPlayLoop(const std::string& name, bool loop);
	void SetPlayReverse(const std::string& name, bool reverse);
	void SetCurrentAnimation(const std::string& name);
	void ChangeAnimation(const std::string& name);
	bool CheckCurrentAnimation(const std::string& name);
	void Update(float deltaTime);
	template <typename T>
	void SetEndFunction(const std::string& name, T* obj, void(T::* func)())
	{
		CAnimationInfo* info = FindInfo(name);
		if (!info)
		{
			return;
		}
		info->SetEndFunction<T>(obj, func);
	}
	template <typename T>
	void SetCurrentAnimationEndFunction(T* obj, void(T::* func)())
	{
		m_currentAnimationEndFunc = std::bind(func, obj);
	}
	template <typename T>
	void AddNotify(const std::string& name, int frame, T* obj, void(T::* func)())
	{
		CAnimationInfo* info = FindInfo(name);
		if (!info)
		{
			return;
		}
		info->AddNotify<T>(frame, obj, func);
	}
};

