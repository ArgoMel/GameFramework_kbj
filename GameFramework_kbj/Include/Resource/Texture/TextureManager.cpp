#include "TextureManager.h"
#include "Texture.h"

CTextureManager::CTextureManager()
{
}

CTextureManager::~CTextureManager()
{
}

bool CTextureManager::Init()
{
    return true;
}

bool CTextureManager::LoadTexture(const std::string& name, const TCHAR* fileName, const std::string& pathName)
{
	CTexture* texture = FindTexture(name);
	if (texture)
	{
		return true;
	}
	texture = new CTexture;
	texture->SetName(name);
	if (!texture->LoadTexture(fileName, pathName))
	{
		SAFE_RELEASE(texture);
		return false;
	}
	m_mapTexture.insert(std::make_pair(name, texture));
    return true;
}

bool CTextureManager::LoadTextureFullPath(const std::string& name, const TCHAR* fullPath)
{
	CTexture* texture = FindTexture(name);
	if (texture)
	{
		return true;
	}
	texture = new CTexture;
	texture->SetName(name);
	if (!texture->LoadTextureFullPath(fullPath))
	{
		SAFE_RELEASE(texture);
		return false;
	}
	m_mapTexture.insert(std::make_pair(name, texture));
	return true;
}

CTexture* CTextureManager::LoadTexture(FILE* file)
{
	CTexture* texture = new CTexture;
	texture->Load(file);
	CTexture* find = FindTexture(texture->GetName());
	if (find)
	{
		SAFE_DELETE(texture);
		return find;
	}
	m_mapTexture.insert(std::make_pair(texture->GetName(), texture));
	return texture;
}

bool CTextureManager::SetColorKey(const std::string& name, unsigned char r, unsigned char g, unsigned char b, int index)
{
	CTexture* texture = FindTexture(name);
	if (!texture)
	{
		return false;
	}
	texture->SetColorKey(r, g, b, index);
	return true;
}

bool CTextureManager::SetColorKeyAll(const std::string& name, unsigned char r, unsigned char g, unsigned char b)
{
	CTexture* texture = FindTexture(name);
	if (!texture)
	{
		return false;
	}
	texture->SetColorKeyAll(r, g, b);
	return true;
}

CTexture* CTextureManager::FindTexture(const std::string& name)
{
	auto	iter = m_mapTexture.find(name);
	if (iter == m_mapTexture.end())
	{
		return nullptr;
	}
	return iter->second;
}

void CTextureManager::ReleaseTexture(const std::string& name)
{
	auto	iter = m_mapTexture.find(name);
	if (iter == m_mapTexture.end())
	{
		return;
	}
	if (iter->second->GetRefCount() == 1)
	{
		m_mapTexture.erase(iter);
	}
}
#ifdef UNICODE
bool CTextureManager::LoadTexture(const std::string& name, const std::vector<std::wstring>& vecFileName, const std::string& pathName)
{
	CTexture* texture = FindTexture(name);
	if (texture)
	{
		return true;
	}
	texture = new CTexture;
	texture->SetName(name);
	if (!texture->LoadTexture(vecFileName, pathName))
	{
		SAFE_RELEASE(texture);
		return false;
	}
	m_mapTexture.insert(std::make_pair(name, texture));
	return true;
}

bool CTextureManager::LoadTextureFullPath(const std::string& name, const std::vector<std::wstring>& vecFullPath)
{
	CTexture* texture = FindTexture(name);
	if (texture)
	{
		return true;
	}
	texture = new CTexture;
	texture->SetName(name);
	if (!texture->LoadTextureFullPath(vecFullPath))
	{
		SAFE_RELEASE(texture);
		return false;
	}
	m_mapTexture.insert(std::make_pair(name, texture));
	return true;
}
#else
bool CTextureManager::LoadTexture(const std::string& name,const std::vector<std::string>& vecFileName, const std::string& pathName)
{
	CTexture* texture = FindTexture(name);
	if (texture)
	{
		return true;
	}
	texture = new CTexture;
	texture->SetName(name);
	if (!texture->LoadTexture(vecFileName, pathName))
	{
		SAFE_RELEASE(texture);
		return false;
	}
	m_mapTexture.insert(std::make_pair(name, texture));
	return true;
}

bool CTextureManager::LoadTextureFullPath(const std::string& name,const std::vector<std::string>& vecFullPath)
{
	CTexture* texture = FindTexture(name);
	if (texture)
	{
		return true;
	}
	texture = new CTexture;
	texture->SetName(name);
	if (!texture->LoadTextureFullPath(vecFullPath))
	{
		SAFE_RELEASE(texture);
		return false;
	}
	m_mapTexture.insert(std::make_pair(name, texture));
	return true;
}
#endif