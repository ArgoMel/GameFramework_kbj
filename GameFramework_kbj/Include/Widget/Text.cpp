#include "Text.h"
#include "../Resource/Font/Font.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"
#include "WidgetWindow.h"

CText::CText()
{
	m_count = 0;
	m_capacity = 32;
	m_text = new TCHAR[m_capacity];
	memset(m_text, 0, sizeof(TCHAR) * m_capacity);
	m_textColor = RGB(0, 0, 0);
	m_shadowColor = RGB(30, 30, 30);
	m_shadow = false;
	m_shadowOffset = Vector2(1.f, 1.f);
}

CText::CText(const CText& widget) 
	: CWidget(widget)
	, m_count(widget.m_count)
	, m_capacity(widget.m_capacity)
	, m_text(widget.m_text)
	, m_textColor(widget.m_textColor)
	, m_shadow(widget.m_shadow)
	, m_shadowColor(widget.m_shadowColor)

{
}

CText::~CText()
{
	SAFE_DELETE_ARRAY(m_text);
}

void CText::SetFont(const std::string& name)
{
	m_font = m_scene->GetSceneResource()->FindFont(name);
}

bool CText::Init()
{
	m_font = m_scene->GetSceneResource()->FindFont("DefaultFont");
	return true;
}

void CText::Update(float deltaTime)
{
}

void CText::PostUpdate(float deltaTime)
{
}

void CText::Render(HDC hDC, float deltaTime)
{
	m_font->SetFont(hDC);
	Vector2	renderPos = m_pos + m_owner->GetPos();
	SetBkMode(hDC, TRANSPARENT);
	// 그림자를 출력해야 한다면 그림자 먼저 출력한다.
	if (m_shadow)
	{
		Vector2	shadowPos = renderPos + m_shadowOffset;
		::SetTextColor(hDC, m_shadowColor);
		TextOut(hDC, (int)shadowPos.x, (int)shadowPos.y, m_text, m_count);
	}
	// 멤버함수가 아닌 같은 이름의 전역함수를 호출하고자 한다면 앞에 :: 을 붙여서 호출한다.
	::SetTextColor(hDC, m_textColor);
	TextOut(hDC, (int)renderPos.x, (int)renderPos.y, m_text, m_count);
	m_font->ResetFont(hDC);
}

void CText::Render(HDC hDC, const Vector2& pos, float deltaTime)
{
	m_font->SetFont(hDC);
	Vector2	renderPos = pos;
	SetBkMode(hDC, TRANSPARENT);
	if (m_shadow)
	{
		Vector2	shadowPos = renderPos + m_shadowOffset;
		::SetTextColor(hDC, m_shadowColor);
		TextOut(hDC, (int)shadowPos.x, (int)shadowPos.y, m_text, m_count);
	}
	::SetTextColor(hDC, m_textColor);
	TextOut(hDC, (int)renderPos.x, (int)renderPos.y, m_text, m_count);
	m_font->ResetFont(hDC);
}
