#pragma once
#include "../GameInfo.h"

struct AnimationNotify
{
	int		frame;
	bool	call;
	std::function<void()>	function;

	AnimationNotify() 
		:frame(0)
		,call(false)
	{
	}
};

class CAnimationInfo
{
private:
	friend class CAnimation;
	friend class CGameObject;
	CSharedPtr<class CAnimationSequence>	m_sequence;
	int				m_frame;					// 현재 애니메이션이 동작되는 프레임.
	float			m_time;						// 애니메이션 프레임을 증가시켜주기 위한 시간값.
	float			m_frameTime;				// 한 프레임이 증가하기 위한 시간.
	float			m_playTime;					// 모션 한번이 동작되기 위한 시간.
	float			m_playScale;				// 재생속도 배율.
	bool			m_loop;						// 반복해서 재생해야 하는지 여부.
	bool			m_reverse;					// 역재생 여부.
	std::function<void()>		m_endFunction;	// 애니메이션이 끝날때마다 호출될 함수 등록.
	std::vector<AnimationNotify*>	m_vecNotify;
	CAnimationInfo();
	~CAnimationInfo();
public:
	template <typename T>
	void SetEndFunction(T* obj, void(T::* func)())
	{
		m_endFunction = std::bind(func, obj);
	}

	template <typename T>
	void AddNotify(int frame, T* obj, void(T::* func)())
	{
		AnimationNotify* notify = new AnimationNotify;
		notify->frame = frame;
		notify->function = std::bind(func, obj);
		m_vecNotify.push_back(notify);
	}
};

