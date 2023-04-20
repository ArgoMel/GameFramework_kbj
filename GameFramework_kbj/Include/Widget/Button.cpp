#include "Button.h"
#include "../Resource/Texture/Texture.h"
#include "../Resource/Sound/Sound.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"
#include "WidgetWindow.h"
#include "../Input.h"

CButton::CButton()
	: m_buttonState(EButton_State::Normal)
	, m_stateData{}
{
}

CButton::CButton(const CButton& widget)
	: CWidget(widget)
	, m_buttonState(EButton_State::Normal)
{
}

CButton::~CButton()
{
}

void CButton::SetTexture(const std::string& name, const TCHAR* fileName, const std::string& pathName)
{
	m_scene->GetSceneResource()->LoadTexture(name, fileName, pathName);
	m_texture = m_scene->GetSceneResource()->FindTexture(name);
}

void CButton::SetTextureFullPath(const std::string& name, const TCHAR* fullPath)
{
	m_scene->GetSceneResource()->LoadTextureFullPath(name, fullPath);
	m_texture = m_scene->GetSceneResource()->FindTexture(name);
}

bool CButton::SetColorKey(unsigned char r, unsigned char g, unsigned char b, int index)
{
	if (!m_texture)
	{
		return false;
	}
	m_texture->SetColorKey(r, g, b, index);
	return true;
}

void CButton::SetButtonStateData(EButton_State state, const Vector2& start, const Vector2& end)
{
	m_stateData[(int)state].start = start;
	m_stateData[(int)state].end = end;
}

void CButton::SetSound(EButton_Sound_State state, const std::string& name)
{
	m_stateSound[(int)state] = m_scene->GetSceneResource()->FindSound(name);
}

bool CButton::Init()
{
	return true;
}

void CButton::Update(float deltaTime)
{
	m_size = m_stateData[(int)m_buttonState].end - m_stateData[(int)m_buttonState].start;
	if (m_buttonState != EButton_State::Disable)
	{
		if (m_mouseHovered)
		{
			if (CInput::GetInst()->GetMouseLDown())
			{
				m_buttonState = EButton_State::Click;
			}
			else if (m_buttonState == EButton_State::Click &&CInput::GetInst()->GetMouseLUp())
			{
				if (m_stateSound[(int)EButton_Sound_State::Click])
				{
					m_stateSound[(int)EButton_Sound_State::Click]->Play();
				}
				if (m_callback[(int)EButton_Sound_State::Click])
				{
					m_callback[(int)EButton_Sound_State::Click]();
				}
				m_buttonState = EButton_State::MouseHovered;
			}
			else if (m_buttonState == EButton_State::Click && CInput::GetInst()->GetMouseLPush())
			{
				m_buttonState = EButton_State::Click;
			}
			else
			{
				m_buttonState = EButton_State::MouseHovered;
			}
		}
		else
		{
			m_buttonState = EButton_State::Normal;
		}
	}
}

void CButton::PostUpdate(float deltaTime)
{
}

void CButton::Render(HDC hDC, float deltaTime)
{
	Vector2	renderPos = m_pos + m_owner->GetPos();
	if (m_texture)
	{
		if (m_texture->GetTextureType() == ETexture_Type::Sprite)
		{
			if (m_texture->GetEnableColorKey())
			{
				TransparentBlt(hDC, (int)renderPos.x, 
									(int)renderPos.y,
									(int)m_size.x, 
									(int)m_size.y,m_texture->GetDC(),
									(int)m_stateData[(int)m_buttonState].start.x,
									(int)m_stateData[(int)m_buttonState].start.y,
									(int)m_size.x, 
									(int)m_size.y, m_texture->GetColorKey());
			}
			else
			{
				BitBlt(hDC, (int)renderPos.x, 
							(int)renderPos.y,
							(int)m_size.x, 
							(int)m_size.y, m_texture->GetDC(),
							(int)m_stateData[(int)m_buttonState].start.x,
							(int)m_stateData[(int)m_buttonState].start.y, SRCCOPY);
			}
		}
		else
		{
			if (m_texture->GetEnableColorKey())
			{
				TransparentBlt(hDC, (int)renderPos.x, 
									(int)renderPos.y,
									(int)m_size.x, 
									(int)m_size.y,m_texture->GetDC(),
									(int)m_stateData[(int)m_buttonState].start.x,
									(int)m_stateData[(int)m_buttonState].start.y,
									(int)m_size.x, 
									(int)m_size.y,m_texture->GetColorKey());
			}
			else
			{
				BitBlt(hDC, (int)renderPos.x, 
							(int)renderPos.y,
							(int)m_size.x, 
							(int)m_size.y,m_texture->GetDC(),
							(int)m_stateData[(int)m_buttonState].start.x,
							(int)m_stateData[(int)m_buttonState].start.y, SRCCOPY);
			}
		}
	}
	else
	{
		Rectangle(hDC,	(int)renderPos.x, 
						(int)renderPos.y,
						(int)(renderPos.x + m_size.x), 
						(int)(renderPos.y + m_size.y));
	}
}

void CButton::Render(HDC hDC, const Vector2& pos, float deltaTime)
{
	Vector2	renderPos = pos;
	if (m_texture)
	{
		if (m_texture->GetTextureType() == ETexture_Type::Sprite)
		{
			if (m_texture->GetEnableColorKey())
			{
				TransparentBlt(hDC, (int)renderPos.x, 
									(int)renderPos.y,
									(int)m_size.x, 
									(int)m_size.y,m_texture->GetDC(),
									(int)m_stateData[(int)m_buttonState].start.x,
									(int)m_stateData[(int)m_buttonState].start.y,
									(int)m_size.x, 
									(int)m_size.y,m_texture->GetColorKey());
			}
			else
			{
				BitBlt(hDC, (int)renderPos.x, 
							(int)renderPos.y,
							(int)m_size.x, 
							(int)m_size.y,m_texture->GetDC(),
							(int)m_stateData[(int)m_buttonState].start.x,
							(int)m_stateData[(int)m_buttonState].start.y, SRCCOPY);
			}
		}
		else
		{
			if (m_texture->GetEnableColorKey())
			{
				TransparentBlt(hDC, (int)renderPos.x, 
									(int)renderPos.y,
									(int)m_size.x, 
									(int)m_size.y,m_texture->GetDC(),
									(int)m_stateData[(int)m_buttonState].start.x,
									(int)m_stateData[(int)m_buttonState].start.y,
									(int)m_size.x, 
									(int)m_size.y,m_texture->GetColorKey());
			}
			else
			{
				BitBlt(hDC, (int)renderPos.x, 
							(int)renderPos.y,
							(int)m_size.x, 
							(int)m_size.y,m_texture->GetDC(),
							(int)m_stateData[(int)m_buttonState].start.x,
							(int)m_stateData[(int)m_buttonState].start.y, SRCCOPY);
			}
		}
	}
	else
	{
		Rectangle(hDC, (int)renderPos.x, 
					   (int)renderPos.y,
					   (int)(renderPos.x + m_size.x), 
					   (int)(renderPos.y + m_size.y));
	}
}

void CButton::CollisionMouseHoveredCallback(const Vector2& pos)
{
	CWidget::CollisionMouseHoveredCallback(pos);
	if (m_stateSound[(int)EButton_Sound_State::MouseHovered])
	{
		m_stateSound[(int)EButton_Sound_State::MouseHovered]->Play();
	}
	if (m_callback[(int)EButton_Sound_State::MouseHovered])
	{
		m_callback[(int)EButton_Sound_State::MouseHovered]();
	}
}

void CButton::CollisionMouseReleaseCallback()
{
	CWidget::CollisionMouseReleaseCallback();
}

#ifdef UNICODE
void CButton::SetTexture(const std::string& name, const std::vector<std::wstring>& vecFileName, const std::string& pathName)
{
	m_scene->GetSceneResource()->LoadTexture(name, vecFileName, pathName);
	m_texture = m_scene->GetSceneResource()->FindTexture(name);
}

void CButton::SetTextureFullPath(const std::string& name, const std::vector<std::wstring>& vecFullPath)
{
	m_scene->GetSceneResource()->LoadTextureFullPath(name, vecFullPath);
	m_texture = m_scene->GetSceneResource()->FindTexture(name);
}
#else
void CButton::SetTexture(const std::string& name, const std::vector<std::string>& vecFileName, const std::string& pathName)
{
	m_scene->GetSceneResource()->LoadTexture(name, vecFileName, pathName);
	m_texture = m_scene->GetSceneResource()->FindTexture(name);
}

void CButton::SetTextureFullPath(const std::string& name, const std::vector<std::string>& vecFullPath)
{
	m_scene->GetSceneResource()->LoadTextureFullPath(name, vecFullPath);
	m_texture = m_scene->GetSceneResource()->FindTexture(name);
}
#endif // UNICODE