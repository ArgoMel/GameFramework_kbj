#pragma once
#include "../../Ref.h"

class CFont : public CRef
{
private:
	friend class CFontManager;
	LOGFONT m_fontInfo;
	HFONT   m_hFont;
	HFONT   m_hPrevFont;
	CFont();
	~CFont();
public:
	bool LoadFont(const TCHAR* fontName, int width, int height);
	void SetFont(HDC hDC);
	void ResetFont(HDC hDC);
};

