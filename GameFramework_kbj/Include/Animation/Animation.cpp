#include "Animation.h"
#include "../Resource/Animation/AnimationSequence.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"
#include "../Resource/ResourceManager.h"

CAnimation::CAnimation()
	: m_owner(nullptr)
	, m_scene(nullptr)
	, m_currentAnimation(nullptr)
{
}

CAnimation::~CAnimation()
{
	auto	iter = m_mapAnimation.begin();
	auto	iterEnd = m_mapAnimation.end();
	for (; iter != iterEnd; ++iter)
	{
		SAFE_DELETE(iter->second);
	}
}

CAnimationInfo* CAnimation::FindInfo(const std::string& name)
{
	auto	iter = m_mapAnimation.find(name);
	if (iter == m_mapAnimation.end())
	{
		return nullptr;
	}
	return iter->second;
}

void CAnimation::AddAnimation(const std::string& sequenceName, bool loop, float playTime, float playScale, bool reverse)
{
	if (FindInfo(sequenceName))
	{
		return;
	}
	CAnimationSequence* sequence = nullptr;
	if (m_scene)
	{
		sequence = m_scene->GetSceneResource()->FindAnimation(sequenceName);
	}
	else
	{
		sequence = CResourceManager::GetInst()->FindAnimation(sequenceName);
	}
	if (!sequence)
	{
		return;
	}
	CAnimationInfo* info = new CAnimationInfo;
	info->m_sequence = sequence;
	info->m_loop = loop;
	info->m_playTime = playTime;
	info->m_playScale = playScale;
	info->m_reverse = reverse;
	info->m_frameTime = info->m_playTime / sequence->GetFrameCount();
	if (m_mapAnimation.empty())
	{
		m_currentAnimation = info;
	}
	m_mapAnimation.insert(std::make_pair(sequenceName, info));
}

void CAnimation::SetPlayTime(const std::string& name, float playTime)
{
	CAnimationInfo* info = FindInfo(name);
	if (!info)
	{
		return;
	}
	info->m_playTime = playTime;
}

void CAnimation::SetPlayScale(const std::string& name, float playScale)
{
	CAnimationInfo* info = FindInfo(name);
	if (!info)
	{
		return;
	}
	info->m_playScale = playScale;
}

void CAnimation::SetPlayLoop(const std::string& name, bool loop)
{
	CAnimationInfo* info = FindInfo(name);
	if (!info)
	{
		return;
	}
	info->m_loop = loop;
}

void CAnimation::SetPlayReverse(const std::string& name, bool reverse)
{
	CAnimationInfo* info = FindInfo(name);
	if (!info)
	{
		return;
	}
	info->m_reverse = reverse;
}

void CAnimation::SetCurrentAnimation(const std::string& name)
{
	CAnimationInfo* info = FindInfo(name);
	if (!info)
	{
		return;
	}
	m_currentAnimation = info;
	m_currentAnimation->m_frame = 0;
	m_currentAnimation->m_time = 0.f;
	size_t	size = m_currentAnimation->m_vecNotify.size();
	for (size_t i = 0; i < size; ++i)
	{
		m_currentAnimation->m_vecNotify[i]->call = false;
	}
}

void CAnimation::ChangeAnimation(const std::string& name)
{
	if (m_currentAnimation->m_sequence->GetName() == name)
	{
		return;
	}
	CAnimationInfo* info = FindInfo(name);
	if (!info)
	{
		return;
	}
	//for�� �����ַ��� �ʱ�ȭ
	m_currentAnimation->m_frame = 0;
	m_currentAnimation->m_time = 0.f;
	size_t	size = m_currentAnimation->m_vecNotify.size();
	for (size_t i = 0; i < size; ++i)
	{
		m_currentAnimation->m_vecNotify[i]->call = false;
	}

	m_currentAnimation = info;
	//for�� �����ַ��� �ʱ�ȭ
	m_currentAnimation->m_frame = 0;
	m_currentAnimation->m_time = 0.f;
	size = m_currentAnimation->m_vecNotify.size();
	for (size_t i = 0; i < size; ++i)
	{
		m_currentAnimation->m_vecNotify[i]->call = false;
	}
}

bool CAnimation::CheckCurrentAnimation(const std::string& name)
{
	return m_currentAnimation->m_sequence->GetName() == name;
}

void CAnimation::Update(float deltaTime)
{
	m_currentAnimation->m_time += deltaTime * m_currentAnimation->m_playScale;
	bool animationEnd = false;
	// ����� �ð��� 1�����Ӵ� �귯�� �� �ð��� �����ٸ� �������� ������Ų��.
	if (m_currentAnimation->m_time >= m_currentAnimation->m_frameTime)
	{
		// 1�������� �귯�� �� �ð��� ���� �ٽ� ����ϰ� ������ش�.
		m_currentAnimation->m_time -= m_currentAnimation->m_frameTime;
		if (m_currentAnimation->m_reverse)
		{
			--m_currentAnimation->m_frame;
			if (m_currentAnimation->m_frame < 0)
			{
				animationEnd = true;
			}
		}
		else
		{
			++m_currentAnimation->m_frame;
			if (m_currentAnimation->m_frame == m_currentAnimation->m_sequence->GetFrameCount())
			{
				animationEnd = true;
			}
		}
	}

	size_t	size = m_currentAnimation->m_vecNotify.size();
	for (size_t i = 0; i < size; ++i)
	{
		// ���� ����� ��Ƽ���̰� ȣ���� �ȵǾ��� �����ӿ� �����ߴٸ� ȣ���Ѵ�.
		if (!m_currentAnimation->m_vecNotify[i]->call &&m_currentAnimation->m_vecNotify[i]->frame == m_currentAnimation->m_frame)
		{
			m_currentAnimation->m_vecNotify[i]->call = true;
			m_currentAnimation->m_vecNotify[i]->function();
		}
	}

	if (animationEnd)
	{
		if (m_currentAnimation->m_loop)
		{
			if (m_currentAnimation->m_reverse)
			{
				m_currentAnimation->m_frame = m_currentAnimation->m_sequence->GetFrameCount() - 1;
			}
			else
			{
				m_currentAnimation->m_frame = 0;
			}
		}
		else
		{
			if (m_currentAnimation->m_reverse)
			{
				m_currentAnimation->m_frame = 0;
			}
			else
			{
				m_currentAnimation->m_frame = m_currentAnimation->m_sequence->GetFrameCount() - 1;
			}
		}
		if (m_currentAnimation->m_endFunction)
		{
			m_currentAnimation->m_endFunction();
		}
		for (size_t i = 0; i < size; ++i)
		{
			m_currentAnimation->m_vecNotify[i]->call = false;
		}
	}
}
