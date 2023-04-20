#include "FontManager.h"
#include "Font.h"
#include "../../PathManager.h"

CFontManager::CFontManager()
{
}

CFontManager::~CFontManager()
{
}

bool CFontManager::Init()
{
	LoadFont(TEXT("Daum_Regular.otf"));
	LoadFont("DefaultFont", TEXT("Daum_Regular"), 0, 0);
	return true;
}

bool CFontManager::LoadFont(const std::string& name, const TCHAR* fontName, int width, int height)
{
	CFont* font = FindFont(name);
	if (font)
	{
		return true;
	}
	font = new CFont;
	font->SetName(name);
	if (!font->LoadFont(fontName, width, height))
	{
		SAFE_DELETE(font);
		return false;
	}
	m_mapFont.insert(std::make_pair(name, font));
	return true;
}

bool CFontManager::LoadFont(const TCHAR* fontFileName, const std::string& pathName)
{
	TCHAR	fullPath[MAX_PATH] = {};
	const PathInfo* info = CPathManager::GetInst()->FindPath(FONT_PATH);
	if (info)
	{
		lstrcpy(fullPath, info->path);
	}
	lstrcat(fullPath, fontFileName);
	AddFontResource(fullPath);
	return true;
}

void CFontManager::SetFont(const std::string& name, HDC hDC)
{
	CFont* font = FindFont(name);
	if (!font)
	{
		return;
	}
	font->SetFont(hDC);
}

void CFontManager::ResetFont(const std::string& name, HDC hDC)
{
	CFont* font = FindFont(name);
	if (!font)
	{
		return;
	}
	font->ResetFont(hDC);
}

CFont* CFontManager::FindFont(const std::string& name)
{
	auto	iter = m_mapFont.find(name);
	if (iter == m_mapFont.end())
	{
		return nullptr;
	}
	return iter->second;
}

void CFontManager::ReleaseFont(const std::string& name)
{
	auto	iter = m_mapFont.find(name);
	if (iter == m_mapFont.end())
	{
		return;
	}
	if (iter->second->GetRefCount() == 1)
	{
		m_mapFont.erase(iter);
	}
}