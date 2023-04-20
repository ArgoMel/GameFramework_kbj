#include "SceneResource.h"
#include "../Resource/Texture/Texture.h"
#include "../Resource/ResourceManager.h"
#include "../Resource/Animation/AnimationSequence.h"
#include "../Resource/Sound/Sound.h"
#include "../Resource/Font/Font.h"

CSceneResource::CSceneResource()
{
}

CSceneResource::~CSceneResource()
{
	{
		auto	iter = m_mapTexture.begin();
		auto	iterEnd = m_mapTexture.end();
		for (; iter != iterEnd;)
		{
			std::string	key = iter->first;
			iter = m_mapTexture.erase(iter);
			iterEnd = m_mapTexture.end();
			CResourceManager::GetInst()->ReleaseTexture(key);
		}
	}

	{
		auto	iter = m_mapAnimationSequence.begin();
		auto	iterEnd = m_mapAnimationSequence.end();
		for (; iter != iterEnd;)
		{
			std::string	key = iter->first;
			iter = m_mapAnimationSequence.erase(iter);
			iterEnd = m_mapAnimationSequence.end();
			CResourceManager::GetInst()->ReleaseAnimation(key);
		}
	}

	{
		auto	iter = m_mapSound.begin();
		auto	iterEnd = m_mapSound.end();
		for (; iter != iterEnd;)
		{
			std::string	key = iter->first;
			iter = m_mapSound.erase(iter);
			iterEnd = m_mapSound.end();
			CResourceManager::GetInst()->ReleaseSound(key);
		}
	}

	{
		auto	iter = m_mapFont.begin();
		auto	iterEnd = m_mapFont.end();
		for (; iter != iterEnd;)
		{
			std::string	key = iter->first;
			iter = m_mapFont.erase(iter);
			iterEnd = m_mapFont.end();
			CResourceManager::GetInst()->ReleaseFont(key);
		}
	}
}

bool CSceneResource::LoadTexture(const std::string& name, const TCHAR* fileName, const std::string& pathName)
{
	if (FindTexture(name))
	{
		return false;
	}
	if (!CResourceManager::GetInst()->LoadTexture(name, fileName, pathName))
	{
		return false;
	}
	CTexture* texture = CResourceManager::GetInst()->FindTexture(name);
	m_mapTexture.insert(std::make_pair(name, texture));
	return true;
}

bool CSceneResource::LoadTextureFullPath(const std::string& name, const TCHAR* fullPath)
{
	if (FindTexture(name))
	{
		return false;
	}
	if (!CResourceManager::GetInst()->LoadTextureFullPath(name, fullPath))
	{
		return false;
	}
	CTexture* texture = CResourceManager::GetInst()->FindTexture(name);
	m_mapTexture.insert(std::make_pair(name, texture));
	return true;
}

CTexture* CSceneResource::LoadTexture(FILE* file)
{
	CTexture* texture = CResourceManager::GetInst()->LoadTexture(file);
	if (!texture)
	{
		return nullptr;
	}
	if (!CResourceManager::GetInst()->FindTexture(texture->GetName()))
	{
		m_mapTexture.insert(std::make_pair(texture->GetName(), texture));
	}
	return texture;
}

bool CSceneResource::SetColorKey(const std::string& name, unsigned char r, unsigned char g, unsigned char b, int index)
{
	return CResourceManager::GetInst()->SetColorKey(name, r, g, b, index);
}

bool CSceneResource::SetColorKeyAll(const std::string& name, unsigned char r, unsigned char g, unsigned char b)
{
	return CResourceManager::GetInst()->SetColorKeyAll(name, r, g, b);
}

CTexture* CSceneResource::FindTexture(const std::string& name)
{
	auto	iter = m_mapTexture.find(name);
	if (iter == m_mapTexture.end())
	{
		CTexture* texture = CResourceManager::GetInst()->FindTexture(name);
		if (!texture)
		{
			return nullptr;
		}
		m_mapTexture.insert(std::make_pair(name, texture));
		return texture;
	}
	return iter->second;
}

bool CSceneResource::CreateAnimationSequence(const std::string& name, CTexture* texture)
{
	if (FindAnimation(name))
	{
		return false;
	}
	if (!CResourceManager::GetInst()->CreateAnimationSequence(name, texture))
	{
		return false;
	}
	CAnimationSequence* animation = CResourceManager::GetInst()->FindAnimation(name);
	m_mapAnimationSequence.insert(std::make_pair(name, animation));
	return true;
}

bool CSceneResource::CreateAnimationSequence(const std::string& name, const std::string& texName)
{
	if (FindAnimation(name))
	{
		return false;
	}
	if (!CResourceManager::GetInst()->CreateAnimationSequence(name, texName))
	{
		return false;
	}
	CAnimationSequence* animation = CResourceManager::GetInst()->FindAnimation(name);
	m_mapAnimationSequence.insert(std::make_pair(name, animation));
	return true;
}

bool CSceneResource::CreateAnimationSequence(const std::string& name, const std::string& texName, 
	const TCHAR* fileName, const std::string& pathName)
{
	if (FindAnimation(name))
	{
		return false;
	}
	if (!CResourceManager::GetInst()->CreateAnimationSequence(name, texName, fileName, pathName))
	{
		return false;
	}
	CAnimationSequence* animation = CResourceManager::GetInst()->FindAnimation(name);
	m_mapAnimationSequence.insert(std::make_pair(name, animation));
	return true;
}

bool CSceneResource::CreateAnimationSequenceFullPath(const std::string& name, const std::string& texName, const TCHAR* fullPath)
{
	if (FindAnimation(name))
	{
		return false;
	}
	if (!CResourceManager::GetInst()->CreateAnimationSequenceFullPath(name, texName, fullPath))
	{
		return false;
	}
	CAnimationSequence* animation = CResourceManager::GetInst()->FindAnimation(name);
	m_mapAnimationSequence.insert(std::make_pair(name, animation));
	return true;
}

bool CSceneResource::AddAnimationFrame(const std::string& name, const Vector2& start, const Vector2& end)
{
	return CResourceManager::GetInst()->AddAnimationFrame(name, start, end);
}

bool CSceneResource::AddAnimationFrame(const std::string& name, float posX, float posY, float sizeX, float sizeY)
{
	return CResourceManager::GetInst()->AddAnimationFrame(name, posX, posY, sizeX, sizeY);
}

CAnimationSequence* CSceneResource::FindAnimation(const std::string& name)
{
	auto	iter = m_mapAnimationSequence.find(name);
	if (iter == m_mapAnimationSequence.end())
	{
		CAnimationSequence* animation = CResourceManager::GetInst()->FindAnimation(name);
		if (!animation)
		{
			return nullptr;
		}
		m_mapAnimationSequence.insert(std::make_pair(name, animation));
		return animation;
	}
	return iter->second;
}

bool CSceneResource::CreateSoundChannel(const std::string& name)
{
	return CResourceManager::GetInst()->CreateSoundChannel(name);
}

bool CSceneResource::LoadSound(const std::string& groupName, const std::string& name, bool loop, const char* fileName, const std::string& pathName)
{
	if (FindSound(name))
	{
		return false;
	}
	if (!CResourceManager::GetInst()->LoadSound(groupName, name, loop, fileName, pathName))
	{
		return false;
	}
	CSound* sound = CResourceManager::GetInst()->FindSound(name);
	m_mapSound.insert(std::make_pair(name, sound));
	return true;
}

bool CSceneResource::SetVolume(int volume)
{
	return CResourceManager::GetInst()->SetVolume(volume);
}

bool CSceneResource::SetVolume(const std::string& groupName, int volume)
{
	return CResourceManager::GetInst()->SetVolume(groupName, volume);
}

bool CSceneResource::SoundPlay(const std::string& name)
{
	return CResourceManager::GetInst()->SoundPlay(name);
}

bool CSceneResource::SoundStop(const std::string& name)
{
	return CResourceManager::GetInst()->SoundStop(name);
}

bool CSceneResource::SoundPause(const std::string& name)
{
	return CResourceManager::GetInst()->SoundPause(name);
}

bool CSceneResource::SoundResume(const std::string& name)
{
	return CResourceManager::GetInst()->SoundResume(name);
}

FMOD::ChannelGroup* CSceneResource::FindChannelGroup(const std::string& name)
{
	return CResourceManager::GetInst()->FindChannelGroup(name);
}

CSound* CSceneResource::FindSound(const std::string& name)
{
	auto	iter = m_mapSound.find(name);
	if (iter == m_mapSound.end())
	{
		CSound* sound = CResourceManager::GetInst()->FindSound(name);
		if (!sound)
		{
			return nullptr;
		}
		m_mapSound.insert(std::make_pair(name, sound));
		return sound;
	}
	return iter->second;
}

bool CSceneResource::LoadFont(const std::string& name, const TCHAR* fontName, int width, int height)
{
	if (FindFont(name))
	{
		return false;
	}
	if (!CResourceManager::GetInst()->LoadFont(name, fontName, width, height))
	{
		return false;
	}
	CFont* font = CResourceManager::GetInst()->FindFont(name);
	m_mapFont.insert(std::make_pair(name, font));
	return true;
}

bool CSceneResource::LoadFont(const TCHAR* fontFileName, const std::string& pathName)
{
	return CResourceManager::GetInst()->LoadFont(fontFileName, pathName);
}

void CSceneResource::SetFont(const std::string& name, HDC hDC)
{
	return CResourceManager::GetInst()->SetFont(name, hDC);
}

void CSceneResource::ResetFont(const std::string& name, HDC hDC)
{
	return CResourceManager::GetInst()->ResetFont(name, hDC);
}

CFont* CSceneResource::FindFont(const std::string& name)
{
	auto	iter = m_mapFont.find(name);
	if (iter == m_mapFont.end())
	{
		CFont* font = CResourceManager::GetInst()->FindFont(name);
		if (!font)
		{
			return nullptr;
		}
		m_mapFont.insert(std::make_pair(name, font));
		return font;
	}
	return iter->second;
}

#ifdef UNICODE
bool CSceneResource::LoadTexture(const std::string& name, const std::vector<std::wstring>& vecFileName, const std::string& pathName)
{
	if (FindTexture(name))
	{
		return false;
	}
	if (!CResourceManager::GetInst()->LoadTexture(name, vecFileName, pathName))
	{
		return false;
	}
	CTexture* texture = CResourceManager::GetInst()->FindTexture(name);
	m_mapTexture.insert(std::make_pair(name, texture));
	return true;
}
bool CSceneResource::LoadTextureFullPath(const std::string& name, const std::vector<std::wstring>& vecFullPath)
{
	if (FindTexture(name))
	{
		return false;
	}
	if (!CResourceManager::GetInst()->LoadTextureFullPath(name, vecFullPath))
	{
		return false;
	}
	CTexture* texture = CResourceManager::GetInst()->FindTexture(name);
	m_mapTexture.insert(std::make_pair(name, texture));
	return true;
}
bool CSceneResource::CreateAnimationSequence(const std::string& name, const std::string& texName, 
	const std::vector<std::wstring>& vecFileName, const std::string& pathName)
{
	if (FindAnimation(name))
	{
		return false;
	}
	if (!CResourceManager::GetInst()->CreateAnimationSequence(name, texName, vecFileName, pathName))
	{
		return false;
	}
	CAnimationSequence* animation = CResourceManager::GetInst()->FindAnimation(name);
	m_mapAnimationSequence.insert(std::make_pair(name, animation));
	return true;
}
bool CSceneResource::CreateAnimationSequenceFullPath(const std::string& name, const std::string& texName, 
	const std::vector<std::wstring>& vecFullPath)
{
	if (FindAnimation(name))
	{
		return false;
	}
	if (!CResourceManager::GetInst()->CreateAnimationSequenceFullPath(name, texName, vecFullPath))
	{
		return false;
	}
	CAnimationSequence* animation = CResourceManager::GetInst()->FindAnimation(name);
	m_mapAnimationSequence.insert(std::make_pair(name, animation));
	return true;
}
#else
bool CSceneResource::LoadTexture(const std::string& name,const std::vector<std::string>& vecFileName, const std::string& pathName)
{
	if (FindTexture(name))
	{
		return false;
	}
	if (!CResourceManager::GetInst()->LoadTexture(name, vecFileName, pathName))
	{
		return false;
	}
	CTexture* texture = CResourceManager::GetInst()->FindTexture(name);
	m_mapTexture.insert(std::make_pair(name, texture));
	return true;
}
bool CSceneResource::LoadTextureFullPath(const std::string& name,const std::vector<std::string>& vecFullPath)
{
	if (FindTexture(name))
	{
		return false;
	}
	if (!CResourceManager::GetInst()->LoadTextureFullPath(name, vecFullPath))
	{
		return false;
	}
	CTexture* texture = CResourceManager::GetInst()->FindTexture(name);
	m_mapTexture.insert(std::make_pair(name, texture));
	return true;
}
bool CSceneResource::CreateAnimationSequence(const std::string& name,const std::string& texName, 
	const std::vector<std::string>& vecFileName, const std::string& pathName)
{
	if (FindAnimation(name))
	{
		return false;
	}
	if (!CResourceManager::GetInst()->CreateAnimationSequence(name, texName, vecFileName, pathName))
	{
		return false;
	}
	CAnimationSequence* animation = CResourceManager::GetInst()->FindAnimation(name);
	m_mapAnimationSequence.insert(std::make_pair(name, animation));
	return true;
}
bool CSceneResource::CreateAnimationSequenceFullPath(const std::string& name,const std::string& texName, 
	const std::vector<std::string>& vecFullPath)
{
	if (FindAnimation(name))
	{
		return false;
	}
	if (!CResourceManager::GetInst()->CreateAnimationSequenceFullPath(name, texName, vecFullPath))
	{
		return false;
	}
	CAnimationSequence* animation = CResourceManager::GetInst()->FindAnimation(name);
	m_mapAnimationSequence.insert(std::make_pair(name, animation));
	return true;
}
#endif