#include "AnimationInfo.h"
#include "../Resource/Animation/AnimationSequence.h"

CAnimationInfo::CAnimationInfo()
	: m_frame(0)
	, m_time(0.f)
	, m_frameTime(0.f)
	, m_playTime(1.f)
	, m_playScale(1.f)
	, m_loop(false)
	, m_reverse(false)
{
}

CAnimationInfo::~CAnimationInfo()
{
	size_t	size = m_vecNotify.size();
	for (size_t i = 0; i < size; ++i)
	{
		SAFE_DELETE(m_vecNotify[i]);
	}
}
