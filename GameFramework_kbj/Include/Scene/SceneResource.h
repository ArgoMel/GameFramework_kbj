#pragma once
#include "../GameInfo.h"

class CSceneResource
{
private:
	friend class CScene;
	std::unordered_map<std::string, CSharedPtr<class CTexture>>	m_mapTexture;
	std::unordered_map<std::string, CSharedPtr<class CAnimationSequence>>	m_mapAnimationSequence;
	std::unordered_map<std::string, CSharedPtr<class CSound>>	m_mapSound;
	std::unordered_map<std::string, CSharedPtr<class CFont>>	m_mapFont;
	CSceneResource();
	~CSceneResource();
public:
	// ==================== Texture ====================
	bool LoadTexture(const std::string& name, const TCHAR* fileName,const std::string& pathName = TEXTURE_PATH);
	bool LoadTextureFullPath(const std::string& name, const TCHAR* fullPath);
	class CTexture* LoadTexture(FILE* file);
	bool SetColorKey(const std::string& name, unsigned char r, unsigned char g, unsigned char b,int index = 0);
	bool SetColorKeyAll(const std::string& name, unsigned char r, unsigned char g, unsigned char b);
	class CTexture* FindTexture(const std::string& name);
	// ==================== Animation Sequence ====================
	bool CreateAnimationSequence(const std::string& name, class CTexture* texture);
	bool CreateAnimationSequence(const std::string& name, const std::string& texName);
	bool CreateAnimationSequence(const std::string& name, const std::string& texName,
		const TCHAR* fileName, const std::string& pathName);
	bool CreateAnimationSequenceFullPath(const std::string& name, const std::string& texName,const TCHAR* fullPath);
	bool AddAnimationFrame(const std::string& name, const Vector2& start,const Vector2& end);
	bool AddAnimationFrame(const std::string& name,float posX, float posY, float sizeX, float sizeY);
	class CAnimationSequence* FindAnimation(const std::string& name);
	// ============================ Sound ================================
	bool CreateSoundChannel(const std::string& name);
	bool LoadSound(const std::string& groupName, const std::string& name,bool loop, const char* fileName, 
		const std::string& pathName = SOUND_PATH);
	bool SetVolume(int volume);
	bool SetVolume(const std::string& groupName, int volume);
	bool SoundPlay(const std::string& name);
	bool SoundStop(const std::string& name);
	bool SoundPause(const std::string& name);
	bool SoundResume(const std::string& name);
	FMOD::ChannelGroup* FindChannelGroup(const std::string& name);
	class CSound* FindSound(const std::string& name);
	// =========================== Font ==============================
	bool LoadFont(const std::string& name, const TCHAR* fontName,int width, int height);
	bool LoadFont(const TCHAR* fontFileName,const std::string& pathName = FONT_PATH);
	void SetFont(const std::string& name, HDC hDC);
	void ResetFont(const std::string& name, HDC hDC);
	class CFont* FindFont(const std::string& name);
#ifdef UNICODE
	bool LoadTexture(const std::string& name, const std::vector<std::wstring>& vecFileName,const std::string& pathName = TEXTURE_PATH);
	bool LoadTextureFullPath(const std::string& name, const std::vector<std::wstring>& vecFullPath);
	bool CreateAnimationSequence(const std::string& name, const std::string& texName,
		const std::vector<std::wstring>& vecFileName, const std::string& pathName);
	bool CreateAnimationSequenceFullPath(const std::string& name, const std::string& texName,
		const std::vector<std::wstring>& vecFullPath);
#else
	bool LoadTexture(const std::string& name, const std::vector<std::string>& vecFileName,const std::string& pathName = TEXTURE_PATH);
	bool LoadTextureFullPath(const std::string& name, const std::vector<std::string>& vecFullPath);
	bool CreateAnimationSequence(const std::string& name, const std::string& texName,
		const std::vector<std::string>& vecFileName, const std::string& pathName);
	bool CreateAnimationSequenceFullPath(const std::string& name, const std::string& texName,
		const std::vector<std::string>& vecFullPath);
#endif // UNICODE
};

