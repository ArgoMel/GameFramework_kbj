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
	int				m_frame;					// ���� �ִϸ��̼��� ���۵Ǵ� ������.
	float			m_time;						// �ִϸ��̼� �������� ���������ֱ� ���� �ð���.
	float			m_frameTime;				// �� �������� �����ϱ� ���� �ð�.
	float			m_playTime;					// ��� �ѹ��� ���۵Ǳ� ���� �ð�.
	float			m_playScale;				// ����ӵ� ����.
	bool			m_loop;						// �ݺ��ؼ� ����ؾ� �ϴ��� ����.
	bool			m_reverse;					// ����� ����.
	std::function<void()>		m_endFunction;	// �ִϸ��̼��� ���������� ȣ��� �Լ� ���.
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

