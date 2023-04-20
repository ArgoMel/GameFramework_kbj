#include "Widget.h"
#include "WidgetWindow.h"

CWidget::CWidget()
	: m_scene(nullptr)
	, m_owner(nullptr)
	, m_zOrder(0)
	, m_mouseHovered(false)
{
}

CWidget::CWidget(const CWidget& widget)
	: CRef(widget)
	, m_scene(nullptr)
	, m_owner(nullptr)
{
	m_zOrder = widget.m_zOrder;
	m_mouseHovered = widget.m_mouseHovered;
}

CWidget::~CWidget()
{
}

bool CWidget::Init()
{
	return true;
}

void CWidget::Update(float deltaTime)
{
}

void CWidget::PostUpdate(float deltaTime)
{
}

void CWidget::Render(HDC hDC, float deltaTime)
{
}

void CWidget::Render(HDC hDC, const Vector2& pos, float deltaTime)
{
}

bool CWidget::CollisionMouse(const Vector2& pos)
{
	Vector2	renderPos = m_pos + m_owner->GetPos();
	if (pos.x < renderPos.x)
	{
		return false;
	}
	else if (pos.x > renderPos.x + m_size.x)
	{
		return false;
	}
	else if (pos.y < renderPos.y)
	{
		return false;
	}
	else if (pos.y > renderPos.y + m_size.y)
	{
		return false;
	}
	if (!m_mouseHovered)
	{
		CollisionMouseHoveredCallback(pos);
	}
	return true;
}

void CWidget::CollisionMouseHoveredCallback(const Vector2& pos)
{
	m_mouseHovered = true;
}

void CWidget::CollisionMouseReleaseCallback()
{
	m_mouseHovered = false;
}
