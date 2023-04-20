#include "SceneCollision.h"
#include "../Collision/Collider.h"
#include "../Input.h"
#include "../Widget/WidgetWindow.h"
#include "../Widget/Widget.h"

CSceneCollision::CSceneCollision()
	: m_mouseCollision(nullptr)
	, m_mouseCollisionWidget(nullptr)
{
	m_vecCollider.reserve(500);
}

CSceneCollision::~CSceneCollision()
{
}

bool CSceneCollision::SortY(CCollider* src, CCollider* dest)
{
	return src->GetBottom() > dest->GetBottom();
}

bool CSceneCollision::SortWidget(CWidgetWindow* src, CWidgetWindow* dest)
{
	return src->GetZOrder() > dest->GetZOrder();
}

void CSceneCollision::AddCollider(CCollider* collider)
{
	m_vecCollider.push_back(collider);
}

void CSceneCollision::AddWidgetWindow(CWidgetWindow* window)
{
	m_vecWidgetWindow.push_back(window);
}

void CSceneCollision::Collision(float deltaTime)
{
	size_t	size = m_vecCollider.size();
	if (size > 1)
	{
		for (size_t i = 0; i < size - 1; ++i)
		{
			CCollider* src = m_vecCollider[i];
			for (size_t j = i + 1; j < size; ++j)
			{
				CCollider* dest = m_vecCollider[j];
				if (src->GetOwner() == dest->GetOwner())
				{
					continue;
				}
				const CollisionProfile* srcProfile = src->GetProfile();
				const CollisionProfile* destProfile = dest->GetProfile();
				ECollision_Interaction	srcInteraction = srcProfile->vecCollisionInteraction[(int)destProfile->channel];
				ECollision_Interaction	destInteraction = destProfile->vecCollisionInteraction[(int)srcProfile->channel];
				if (srcInteraction == ECollision_Interaction::Ignore || destInteraction == ECollision_Interaction::Ignore)
				{
					continue;
				}
				if (src->Collision(dest))
				{
					if (!src->CheckCollisionList(dest))
					{
						src->AddCollisionList(dest);
						dest->AddCollisionList(src);
						src->CallCollisionBegin(dest);
						dest->CallCollisionBegin(src);
					}
				}
				else if (src->CheckCollisionList(dest))
				{
					src->DeleteCollisionList(dest);
					dest->DeleteCollisionList(src);
					src->CallCollisionEnd(dest);
					dest->CallCollisionEnd(src);
				}
			}
		}
	}
	m_vecCollider.clear();
	m_vecWidgetWindow.clear();
}

void CSceneCollision::CollisionMouse(float deltaTime)
{
	size_t	windowCount = m_vecWidgetWindow.size();
	bool	mouseCollision = false;
	if (windowCount >= 1)
	{
		if (windowCount > 1)
		{
			std::sort(m_vecWidgetWindow.begin(), m_vecWidgetWindow.end(), CSceneCollision::SortWidget);
		}
		Vector2	mousePos = CInput::GetInst()->GetMousePos();
		CWidget* result = nullptr;
		for (size_t i = 0; i < windowCount; ++i)
		{
			m_vecWidgetWindow[i]->SortCollision();
			if (m_vecWidgetWindow[i]->CollisionMouse(&result, mousePos))
			{
				if (m_mouseCollisionWidget && m_mouseCollisionWidget != result)
				{
					m_mouseCollisionWidget->CollisionMouseReleaseCallback();
				}
				if (m_mouseCollision)
				{
					m_mouseCollision->SetMouseCollision(false);
					m_mouseCollision->CallMouseCollisionEnd(CInput::GetInst()->GetMouseWorldPos());
					m_mouseCollision = nullptr;
				}
				m_mouseCollisionWidget = result;
				mouseCollision = true;
				break;
			}
			else if (m_mouseCollision)
			{
				m_mouseCollision->SetMouseCollision(false);
				m_mouseCollision->CallMouseCollisionEnd(CInput::GetInst()->GetMouseWorldPos());
				m_mouseCollision = nullptr;
			}
			else if (m_vecWidgetWindow[i]->CheckWidget(m_mouseCollisionWidget))
			{
				m_mouseCollisionWidget->CollisionMouseReleaseCallback();
				m_mouseCollisionWidget = nullptr;
			}
		}
	}
	if (!mouseCollision)
	{
		if (m_mouseCollisionWidget)
		{
			m_mouseCollisionWidget->CollisionMouseReleaseCallback();
			m_mouseCollisionWidget = nullptr;
		}
		size_t	size = m_vecCollider.size();
		if (size >= 1)
		{
			if (size > 1)
			{
				std::sort(m_vecCollider.begin(), m_vecCollider.end(), CSceneCollision::SortY);
			}
			Vector2	mouseWorldPos = CInput::GetInst()->GetMouseWorldPos();
			CollisionProfile* mouseProfile = CInput::GetInst()->GetMouseProfile();
			for (size_t i = 0; i < size; ++i)
			{
				CCollider* dest = m_vecCollider[i];
				const CollisionProfile* srcProfile = mouseProfile;
				const CollisionProfile* destProfile = dest->GetProfile();
				ECollision_Interaction	srcInteraction = srcProfile->vecCollisionInteraction[(int)destProfile->channel];
				ECollision_Interaction	destInteraction = destProfile->vecCollisionInteraction[(int)srcProfile->channel];
				if (srcInteraction == ECollision_Interaction::Ignore || destInteraction == ECollision_Interaction::Ignore)
				{
					continue;
				}
				if (dest->CollisionMouse(mouseWorldPos))
				{
					mouseCollision = true;
					if (!dest->GetMouseCollision())
					{
						if (m_mouseCollision)
						{
							m_mouseCollision->SetMouseCollision(false);
						}
						dest->SetMouseCollision(true);
						dest->CallMouseCollisionBegin(mouseWorldPos);
					}
					m_mouseCollision = dest;
					break;
				}
				else if (dest->GetMouseCollision())
				{
					m_mouseCollision->SetMouseCollision(false);
					m_mouseCollision = nullptr;
				}
			}
			if (!mouseCollision)
			{
				if (m_mouseCollision)
				{
					m_mouseCollision->SetMouseCollision(false);
					m_mouseCollision = nullptr;
				}
			}
		}
	}
}
