#include "ResourceManager.h"
#include "Texture/TextureManager.h"
#include "Animation/AnimationManager.h"
#include "Sound/SoundManager.h"
#include "Font/FontManager.h"

DEFINITION_SINGLE(CResourceManager)

CResourceManager::CResourceManager()
{
	m_textureManager = new CTextureManager;
	m_textureManager->Init();
	m_animationManager = new CAnimationManager;
	m_animationManager->Init();
	m_soundManager = new CSoundManager;
	m_soundManager->Init();
	m_fontManager = new CFontManager;
	m_fontManager->Init();
}

CResourceManager::~CResourceManager()
{
	SAFE_DELETE(m_fontManager);
	SAFE_DELETE(m_soundManager);
	SAFE_DELETE(m_animationManager);
	SAFE_DELETE(m_textureManager);
}

bool CResourceManager::Init()
{
    return true;
}

void CResourceManager::Update()
{
	m_soundManager->Update();
}

bool CResourceManager::LoadTexture(const std::string& name, const TCHAR* fileName, const std::string& pathName)
{
	return m_textureManager->LoadTexture(name, fileName, pathName);
}

bool CResourceManager::LoadTextureFullPath(const std::string& name, const TCHAR* fullPath)
{
	return m_textureManager->LoadTextureFullPath(name, fullPath);
}

CTexture* CResourceManager::LoadTexture(FILE* file)
{
	return m_textureManager->LoadTexture(file);
}

bool CResourceManager::SetColorKey(const std::string& name, unsigned char r, unsigned char g, unsigned char b, int index)
{
	return m_textureManager->SetColorKey(name, r, g, b, index);
}

bool CResourceManager::SetColorKeyAll(const std::string& name, unsigned char r, unsigned char g, unsigned char b)
{
	return m_textureManager->SetColorKeyAll(name, r, g, b);
}

CTexture* CResourceManager::FindTexture(const std::string& name)
{
	return m_textureManager->FindTexture(name);
}

void CResourceManager::ReleaseTexture(const std::string& name)
{
	m_textureManager->ReleaseTexture(name);
}
bool CResourceManager::CreateAnimationSequence(const std::string& name, CTexture* texture)
{
	return m_animationManager->CreateAnimationSequence(name, texture);
}
bool CResourceManager::CreateAnimationSequence(const std::string& name, const std::string& texName)
{
	CTexture* texture = FindTexture(texName);
	return m_animationManager->CreateAnimationSequence(name, texture);
}
bool CResourceManager::CreateAnimationSequence(const std::string& name, const std::string& texName, 
	const TCHAR* fileName, const std::string& pathName)
{
	CTexture* texture = FindTexture(texName);
	if (texture)
	{
		return m_animationManager->CreateAnimationSequence(name, texture);
	}
	if (!m_textureManager->LoadTexture(texName, fileName, pathName))
	{
		return false;
	}
	texture = FindTexture(texName);
	return m_animationManager->CreateAnimationSequence(name, texture);
}
bool CResourceManager::CreateAnimationSequenceFullPath(const std::string& name, const std::string& texName, const TCHAR* fullPath)
{
	CTexture* texture = FindTexture(texName);
	if (texture)
	{
		return m_animationManager->CreateAnimationSequence(name, texture);
	}
	if (!m_textureManager->LoadTextureFullPath(texName, fullPath))
	{
		return false;
	}
	texture = FindTexture(texName);
	return m_animationManager->CreateAnimationSequence(name, texture);
}
bool CResourceManager::AddAnimationFrame(const std::string& name, const Vector2& start, const Vector2& end)
{
	return m_animationManager->AddAnimationFrame(name, start, end);
}
bool CResourceManager::AddAnimationFrame(const std::string& name, float posX, float posY, float sizeX, float sizeY)
{
	return m_animationManager->AddAnimationFrame(name, posX, posY, sizeX, sizeY);
}
CAnimationSequence* CResourceManager::FindAnimation(const std::string& name)
{
	return m_animationManager->FindAnimation(name);
}
void CResourceManager::ReleaseAnimation(const std::string& name)
{
	m_animationManager->ReleaseAnimation(name);
}
bool CResourceManager::CreateSoundChannel(const std::string& name)
{
	return m_soundManager->CreateSoundChannel(name);
}
bool CResourceManager::LoadSound(const std::string& groupName, const std::string& name, bool loop, const char* fileName, const std::string& pathName)
{
	return m_soundManager->LoadSound(groupName, name, loop, fileName, pathName);
}
bool CResourceManager::SetVolume(int volume)
{
	return m_soundManager->SetVolume(volume);
}
bool CResourceManager::SetVolume(const std::string& groupName, int volume)
{
	return m_soundManager->SetVolume(groupName, volume);
}
bool CResourceManager::SoundPlay(const std::string& name)
{
	return m_soundManager->SoundPlay(name);
}
bool CResourceManager::SoundStop(const std::string& name)
{
	return m_soundManager->SoundStop(name);
}
bool CResourceManager::SoundPause(const std::string& name)
{
	return m_soundManager->SoundPause(name);
}
bool CResourceManager::SoundResume(const std::string& name)
{
	return m_soundManager->SoundResume(name);
}
FMOD::ChannelGroup* CResourceManager::FindChannelGroup(const std::string& name)
{
	return m_soundManager->FindChannelGroup(name);
}
CSound* CResourceManager::FindSound(const std::string& name)
{
	return m_soundManager->FindSound(name);
}
void CResourceManager::ReleaseSound(const std::string& name)
{
	m_soundManager->ReleaseSound(name);
}

bool CResourceManager::LoadFont(const std::string& name, const TCHAR* fontName, int width, int height)
{
	return m_fontManager->LoadFont(name, fontName, width, height);
}

bool CResourceManager::LoadFont(const TCHAR* fontFileName, const std::string& pathName)
{
	return m_fontManager->LoadFont(fontFileName, pathName);
}

void CResourceManager::SetFont(const std::string& name, HDC hDC)
{
	m_fontManager->SetFont(name, hDC);
}

void CResourceManager::ResetFont(const std::string& name, HDC hDC)
{
	m_fontManager->ResetFont(name, hDC);
}

CFont* CResourceManager::FindFont(const std::string& name)
{
	return m_fontManager->FindFont(name);
}

void CResourceManager::ReleaseFont(const std::string& name)
{
	m_fontManager->ReleaseFont(name);
}

#ifdef UNICODE
bool CResourceManager::LoadTexture(const std::string& name, const std::vector<std::wstring>& vecFileName, const std::string& pathName)
{
	return m_textureManager->LoadTexture(name, vecFileName, pathName);
}

bool CResourceManager::LoadTextureFullPath(const std::string& name, const std::vector<std::wstring>& vecFullPath)
{
	return m_textureManager->LoadTextureFullPath(name, vecFullPath);
}
bool CResourceManager::CreateAnimationSequence(const std::string& name, const std::string& texName, 
	const std::vector<std::wstring>& vecFileName, const std::string& pathName)
{
	CTexture* texture = FindTexture(texName);
	if (texture)
	{
		return m_animationManager->CreateAnimationSequence(name, texture);
	}
	if (!m_textureManager->LoadTexture(texName, vecFileName, pathName))
	{
		return false;
	}
	texture = FindTexture(texName);
	return m_animationManager->CreateAnimationSequence(name, texture);
}
bool CResourceManager::CreateAnimationSequenceFullPath(const std::string& name, const std::string& texName, 
	const std::vector<std::wstring>& vecFullPath)
{
	CTexture* texture = FindTexture(texName);
	if (texture)
	{
		return m_animationManager->CreateAnimationSequence(name, texture);
	}
	if (!m_textureManager->LoadTextureFullPath(texName, vecFullPath))
	{
		return false;
	}
	texture = FindTexture(texName);
	return m_animationManager->CreateAnimationSequence(name, texture);
}
#else
bool CResourceManager::LoadTexture(const std::string& name,const std::vector<std::string>& vecFileName, const std::string& pathName)
{
	return m_textureManager->LoadTexture(name, vecFileName, pathName);
}

bool CResourceManager::LoadTextureFullPath(const std::string& name,const std::vector<std::string>& vecFullPath)
{
	return m_textureManager->LoadTextureFullPath(name, vecFullPath);
}
bool CResourceManager::CreateAnimationSequence(const std::string& name,const std::string& texName, 
	const std::vector<std::string>& vecFileName, const std::string& pathName)
{
	CTexture* texture = FindTexture(texName);
	if (texture)
	{
		return m_animationManager->CreateAnimationSequence(name, texture);
	}
	if (!m_textureManager->LoadTexture(texName, vecFileName, pathName))
	{
		return false;
	}
	texture = FindTexture(texName);
	return m_animationManager->CreateAnimationSequence(name, texture);
}

bool CResourceManager::CreateAnimationSequenceFullPath(const std::string& name,const std::string& texName, 
	const std::vector<std::string>& vecFullPath)
{
	CTexture* texture = FindTexture(texName);
	if (texture)
	{
		return m_animationManager->CreateAnimationSequence(name, texture);
	}
	if (!m_textureManager->LoadTextureFullPath(texName, vecFullPath))
	{
		return false;
	}
	texture = FindTexture(texName);
	return m_animationManager->CreateAnimationSequence(name, texture);
}
#endif