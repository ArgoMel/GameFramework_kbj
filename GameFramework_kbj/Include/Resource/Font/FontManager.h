#pragma once
#include "../../GameInfo.h"

class CFontManager
{
private:
	friend class CResourceManager;
	std::unordered_map<std::string, CSharedPtr<class CFont>>	m_mapFont;
	CFontManager();
	~CFontManager();
public:
	bool Init();
	bool LoadFont(const std::string& name, const TCHAR* fontName,int width, int height);
	bool LoadFont(const TCHAR* fontFileName,const std::string& pathName = FONT_PATH);
	void SetFont(const std::string& name, HDC hDC);
	void ResetFont(const std::string& name, HDC hDC);
	class CFont* FindFont(const std::string& name);
	void ReleaseFont(const std::string& name);
};

