#include "WidgetComponent.h"
#include "Widget.h"
#include "../Resource/Texture/Texture.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"
#include "../Scene/Camera.h"
#include "WidgetWindow.h"
#include "../GameObject/GameObject.h"

CWidgetComponent::CWidgetComponent()
	: m_owner(nullptr)
	, m_scene(nullptr)
{
}

CWidgetComponent::CWidgetComponent(const CWidgetComponent& widget)
	: m_owner(nullptr)
	, m_scene(nullptr)
{
}

CWidgetComponent::~CWidgetComponent()
{
}

Vector2 CWidgetComponent::GetPos() const
{
	return m_pos + m_owner->GetPos() - m_scene->GetCamera()->GetPos();
}

float CWidgetComponent::GetBottom() const
{
	Vector2	pos = GetPos();
	float bottom = pos.y;
	if (m_widget)
	{
		bottom += m_widget->GetSize().y;
	}
	return bottom;
}

void CWidgetComponent::SetWidget(CWidget* widget)
{
	m_widget = widget;
}

bool CWidgetComponent::Init()
{
	m_scene->AddWidgetComponent(this);
	return true;
}

void CWidgetComponent::Update(float deltaTime)
{
	if (m_widget)
	{
		m_widget->Update(deltaTime);
	}
}

void CWidgetComponent::PostUpdate(float deltaTime)
{
	if (m_widget)
	{
		m_widget->PostUpdate(deltaTime);
	}
}

void CWidgetComponent::Render(HDC hDC, float deltaTime)
{
	if (m_widget)
	{
		Vector2	pos = m_pos + m_owner->GetPos() - m_scene->GetCamera()->GetPos();
		m_widget->Render(hDC, pos, deltaTime);
	}
}
