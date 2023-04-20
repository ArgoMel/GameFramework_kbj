#pragma once
#include "../../GameInfo.h"

class CTextureManager
{
private:
	friend class CResourceManager;
	std::unordered_map<std::string, CSharedPtr<class CTexture>>	m_mapTexture;
	CTextureManager();
	~CTextureManager();
public:
	bool Init();
	bool LoadTexture(const std::string& name, const TCHAR* fileName,const std::string& pathName = TEXTURE_PATH);
	bool LoadTextureFullPath(const std::string& name, const TCHAR* fullPath);
	CTexture* LoadTexture(FILE* file);
	bool SetColorKey(const std::string& name, unsigned char r, unsigned char g, unsigned char b,int index = 0);
	bool SetColorKeyAll(const std::string& name, unsigned char r, unsigned char g, unsigned char b);
	class CTexture* FindTexture(const std::string& name);
	void ReleaseTexture(const std::string& name);
#ifdef UNICODE
	bool LoadTexture(const std::string& name, const std::vector<std::wstring>& vecFileName,const std::string& pathName = TEXTURE_PATH);
	bool LoadTextureFullPath(const std::string& name, const std::vector<std::wstring>& vecFullPath);
#else
	bool LoadTexture(const std::string& name, const std::vector<std::string>& vecFileName,const std::string& pathName = TEXTURE_PATH);
	bool LoadTextureFullPath(const std::string& name, const std::vector<std::string>& vecFullPath);
#endif // UNICODE
};

