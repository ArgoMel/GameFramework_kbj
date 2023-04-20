#include "Sound.h"
#include "../../PathManager.h"

CSound::CSound() 
	: m_system(nullptr)
	, m_sound(nullptr)
	, m_group(nullptr)
	, m_channel(nullptr)
	, m_play(false)
	, m_loop(false)
	, m_pause(false)
{
}

CSound::~CSound()
{
	if (m_sound)
	{
		m_sound->release();
	}
}

bool CSound::LoadSound(FMOD::System* system, FMOD::ChannelGroup* group, bool loop, const char* fileName, const std::string& pathName)
{
	m_system = system;
	m_group = group;
	m_loop = loop;
	char	fullPath[MAX_PATH] = {};
	const PathInfo* info = CPathManager::GetInst()->FindPath(pathName);
	if (info)
	{
		strcpy_s(fullPath, info->pathMultibyte);
	}
	strcat_s(fullPath, fileName);
	FMOD_MODE	mode = FMOD_DEFAULT;
	if (loop)
	{
		mode = FMOD_LOOP_NORMAL;
	}
	if (m_system->createSound(fullPath, mode, nullptr, &m_sound) != FMOD_OK)
	{
		return false;
	}
	return true;
}

void CSound::Play()
{
	m_system->playSound(m_sound, m_group, false, &m_channel);
	m_play = true;
	m_pause = false;
}

void CSound::Stop()
{
	if (m_channel)
	{
		bool	playing = false;
		m_channel->isPlaying(&playing);
		if (playing)
		{
			m_channel->stop();
			m_channel = nullptr;
			m_play = false;
			m_pause = false;
		}
	}
}

void CSound::Pause()
{
	if (m_channel)
	{
		bool	playing = false;
		m_channel->isPlaying(&playing);
		if (playing)
		{
			m_channel->setPaused(true);
		}
		m_play = false;
		m_pause = true;
	}
}

void CSound::Resume()
{
	if (m_channel)
	{
		if (m_pause)
		{
			m_channel->setPaused(false);
			m_play = true;
			m_pause = false;
		}
	}
}
