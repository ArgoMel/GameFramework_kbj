#include "Font.h"

CFont::CFont()
	: m_fontInfo{}
	, m_hFont(0)
	, m_hPrevFont(0)
{
}

CFont::~CFont()
{
	if (m_hFont)
	{
		DeleteObject(m_hFont);
	}
}

bool CFont::LoadFont(const TCHAR* fontName, int width, int height)
{
    m_fontInfo.lfWidth = (LONG)width;
    m_fontInfo.lfHeight = (LONG)height;
    m_fontInfo.lfCharSet = HANGEUL_CHARSET;
    m_fontInfo.lfWeight = FW_BOLD;    // ����
    m_fontInfo.lfItalic = 0;            // ����
    m_fontInfo.lfEscapement = 1;        // ����
    m_fontInfo.lfUnderline = 0;         // ����
    m_fontInfo.lfStrikeOut = 0;         // ��Ҽ�
    m_fontInfo.lfPitchAndFamily = 3;    // �ڰ�
    lstrcpy(m_fontInfo.lfFaceName, fontName);
    m_hFont = CreateFontIndirect(&m_fontInfo);
    return m_hFont == nullptr ? false : true;
}

void CFont::SetFont(HDC hDC)
{
    m_hPrevFont = (HFONT)SelectObject(hDC, m_hFont);
}

void CFont::ResetFont(HDC hDC)
{
    SelectObject(hDC, m_hPrevFont);
}
