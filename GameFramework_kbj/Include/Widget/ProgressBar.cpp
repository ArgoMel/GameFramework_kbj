#include "ProgressBar.h"
#include "../Resource/Texture/Texture.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"
#include "WidgetWindow.h"

CProgressBar::CProgressBar()
	: m_dir(EProgressBar_Dir::LeftToRight)
	, m_value(1.f)
{
}

CProgressBar::CProgressBar(const CProgressBar& widget)
	: CWidget(widget)
	, m_dir(widget.m_dir)
	, m_value(widget.m_value)
{
}

CProgressBar::~CProgressBar()
{
}

void CProgressBar::SetTexture(EProgressBar_Texture_Type type, const std::string& name, const TCHAR* fileName, const std::string& pathName)
{
	m_scene->GetSceneResource()->LoadTexture(name, fileName, pathName);
	m_texture[(int)type] = m_scene->GetSceneResource()->FindTexture(name);
}

void CProgressBar::SetTextureFullPath(EProgressBar_Texture_Type type, const std::string& name, const TCHAR* fullPath)
{
	m_scene->GetSceneResource()->LoadTextureFullPath(name, fullPath);
	m_texture[(int)type] = m_scene->GetSceneResource()->FindTexture(name);
}



void CProgressBar::SetColorKey(EProgressBar_Texture_Type type, unsigned char r, unsigned char g, unsigned char b)
{
	if (m_texture[(int)type])
	{
		m_texture[(int)type]->SetColorKey(r, g, b);
	}
}

bool CProgressBar::Init()
{
	return true;
}

void CProgressBar::Update(float deltaTime)
{
	m_barSize = m_size;
	m_barPos = m_pos;
	switch (m_dir)
	{
	case EProgressBar_Dir::LeftToRight:
		m_barSize.x = m_value * m_size.x;
		break;
	case EProgressBar_Dir::RightToLeft:
		m_barSize.x = m_value * m_size.x;
		m_barPos.x = m_pos.x + (1.f - m_value) * m_size.x;
		break;
	case EProgressBar_Dir::BottomToTop:
		m_barSize.y = m_value * m_size.y;
		m_barPos.y = m_pos.y + (1.f - m_value) * m_size.y;
		break;
	case EProgressBar_Dir::TopToBottom:
		m_barSize.y = m_value * m_size.y;
		break;
	}
}

void CProgressBar::PostUpdate(float deltaTime)
{
}

void CProgressBar::Render(HDC hDC, float deltaTime)
{
	Vector2	renderPos = m_barPos + m_owner->GetPos();
	for (int i = 0; i < (int)EProgressBar_Texture_Type::End; ++i)
	{
		if (m_texture[i])
		{
			if (m_texture[i]->GetTextureType() == ETexture_Type::Sprite)
			{
				if (m_texture[i]->GetEnableColorKey())
				{
					TransparentBlt(hDC, (int)renderPos.x, 
										(int)renderPos.y,
										(int)m_barSize.x, 
										(int)m_barSize.y,m_texture[i]->GetDC(),0, 0, 
										(int)m_barSize.x, 
										(int)m_barSize.y,m_texture[i]->GetColorKey());
				}
				else
				{
					BitBlt(hDC, (int)renderPos.x, 
								(int)renderPos.y,
								(int)m_barSize.x, 
								(int)m_barSize.y,m_texture[i]->GetDC(),0, 0, SRCCOPY);
				}
			}
			else
			{
			}
		}
	}
}

void CProgressBar::Render(HDC hDC, const Vector2& pos, float deltaTime)
{
	Vector2	renderPos = pos;
	for (int i = 0; i < (int)EProgressBar_Texture_Type::End; ++i)
	{
		if (m_texture[i])
		{
			if (m_texture[i]->GetTextureType() == ETexture_Type::Sprite)
			{
				if (m_texture[i]->GetEnableColorKey())
				{
					TransparentBlt(hDC, (int)renderPos.x, 
										(int)renderPos.y,
										(int)m_barSize.x, 
										(int)m_barSize.y,m_texture[i]->GetDC(),0, 0, 
										(int)m_barSize.x, 
										(int)m_barSize.y,m_texture[i]->GetColorKey());
				}
				else
				{
					BitBlt(hDC, (int)renderPos.x, 
								(int)renderPos.y,
								(int)m_barSize.x, 
								(int)m_barSize.y,m_texture[i]->GetDC(),0, 0, SRCCOPY);
				}
			}
			else
			{
			}
		}
	}
}

#ifdef UNICODE
void CProgressBar::SetTexture(EProgressBar_Texture_Type type, const std::string& name, const std::vector<std::wstring>& vecFileName, const std::string& pathName)
{
	m_scene->GetSceneResource()->LoadTexture(name, vecFileName, pathName);
	m_texture[(int)type] = m_scene->GetSceneResource()->FindTexture(name);
}
void CProgressBar::SetTextureFullPath(EProgressBar_Texture_Type type, const std::string& name, const std::vector<std::wstring>& vecFullPath)
{
	m_scene->GetSceneResource()->LoadTextureFullPath(name, vecFullPath);
	m_texture[(int)type] = m_scene->GetSceneResource()->FindTexture(name);
}
#else
void CProgressBar::SetTexture(EProgressBar_Texture_Type Type, const std::string& Name, const std::vector<std::string>& vecFileName, const std::string& PathName)
{
	m_scene->GetSceneResource()->LoadTexture(name, vecFileName, pathName);
	m_texture[(int)type] = m_scene->GetSceneResource()->FindTexture(name);
}

void CProgressBar::SetTextureFullPath(EProgressBar_Texture_Type Type, const std::string& Name, const std::vector<std::string>& vecFullPath)
{
	m_scene->GetSceneResource()->LoadTextureFullPath(name, vecFullPath);
	m_texture[(int)type] = m_scene->GetSceneResource()->FindTexture(name);
}

#endif // UNICODE