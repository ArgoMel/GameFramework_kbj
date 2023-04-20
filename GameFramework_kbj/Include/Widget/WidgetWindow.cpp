#include "WidgetWindow.h"

CWidgetWindow::CWidgetWindow()
	: m_scene(nullptr)
	, m_zOrder(0)
{
}

CWidgetWindow::~CWidgetWindow()
{
}

bool CWidgetWindow::SortCollisionWidget(const CSharedPtr<class CWidget>& src, const CSharedPtr<class CWidget>& dest)
{
	return src->GetZOrder() > dest->GetZOrder();
}

bool CWidgetWindow::SortWidget(const CSharedPtr<class CWidget>& src, const CSharedPtr<class CWidget>& dest)
{
	return src->GetZOrder() < dest->GetZOrder();
}

bool CWidgetWindow::Init()

{
    return true;
}

void CWidgetWindow::Update(float deltaTime)
{
	auto	iter = m_vecWidget.begin();
	auto	iterEnd = m_vecWidget.end();
	for (; iter != iterEnd;)
	{
		if (!(*iter)->GetActive())
		{
			iter = m_vecWidget.erase(iter);
			iterEnd = m_vecWidget.end();
			continue;
		}
		else if (!(*iter)->GetEnable())
		{
			++iter;
			continue;
		}
		(*iter)->Update(deltaTime);
		++iter;
	}
}

void CWidgetWindow::PostUpdate(float deltaTime)
{
	auto	iter = m_vecWidget.begin();
	auto	iterEnd = m_vecWidget.end();
	for (; iter != iterEnd;)
	{
		if (!(*iter)->GetActive())
		{
			iter = m_vecWidget.erase(iter);
			iterEnd = m_vecWidget.end();
			continue;
		}
		else if (!(*iter)->GetEnable())
		{
			++iter;
			continue;
		}
		(*iter)->PostUpdate(deltaTime);
		++iter;
	}
}

void CWidgetWindow::Render(HDC hDC, float deltaTime)
{
	size_t	size = m_vecWidget.size();
	if (size > 1)
	{
		std::sort(m_vecWidget.begin(), m_vecWidget.end(), CWidgetWindow::SortWidget);
	}
	auto	iter = m_vecWidget.begin();
	auto	iterEnd = m_vecWidget.end();
	for (; iter != iterEnd;)
	{
		if (!(*iter)->GetActive())
		{
			iter = m_vecWidget.erase(iter);
			iterEnd = m_vecWidget.end();
			continue;
		}
		else if (!(*iter)->GetEnable())
		{
			++iter;
			continue;
		}
		(*iter)->Render(hDC, deltaTime);
		++iter;
	}
}

void CWidgetWindow::SortCollision()
{
	if (m_vecWidget.size() > 1)
	{
		std::sort(m_vecWidget.begin(), m_vecWidget.end(), CWidgetWindow::SortCollisionWidget);
	}
}

bool CWidgetWindow::CollisionMouse(CWidget** widget, const Vector2& pos)
{
	if (pos.x < m_pos.x)
	{
		return false;
	}
	else if (pos.y < m_pos.y)
	{
		return false;
	}
	else if (pos.x > m_pos.x + m_size.x)
	{
		return false;
	}
	else if (pos.y > m_pos.y + m_size.y)
	{
		return false;
	}
	size_t	widgetCount = m_vecWidget.size();
	for (size_t i = 0; i < widgetCount; ++i)
	{
		if (!m_vecWidget[i]->GetEnable())
		{
			continue;
		}
		if (m_vecWidget[i]->CollisionMouse(pos))
		{
			*widget = m_vecWidget[i];
			return true;
		}
	}
	return false;
}
