#pragma once
#include "../../Ref.h"
class CSound :public CRef
{
private:
	friend class CSoundManager;
    FMOD::System* m_system;
    FMOD::Sound* m_sound;
    FMOD::ChannelGroup* m_group;
    FMOD::Channel* m_channel;
    bool        m_play;
    bool        m_loop;
    bool        m_pause;
	CSound();
	~CSound();
public:
    bool GetPlay()   const
    {
        return m_play;
    }

    bool GetLoop()  const
    {
        return m_loop;
    }
    bool LoadSound(FMOD::System* system, FMOD::ChannelGroup* group, bool loop,const char* fileName, 
        const std::string& pathName = SOUND_PATH);
    void Play();
    void Stop();
    void Pause();
    void Resume();
};

