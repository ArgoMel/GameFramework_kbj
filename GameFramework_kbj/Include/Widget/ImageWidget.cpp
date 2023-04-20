#include "ImageWidget.h"
#include "../Resource/Texture/Texture.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"
#include "WidgetWindow.h"

CImageWidget::CImageWidget()
{
}

CImageWidget::CImageWidget(const CImageWidget& widget)
	: CWidget(widget)
{
}

CImageWidget::~CImageWidget()
{
}

void CImageWidget::SetTexture(const std::string& name, const TCHAR* fileName, const std::string& pathName)
{
	m_scene->GetSceneResource()->LoadTexture(name, fileName, pathName);
	m_texture = m_scene->GetSceneResource()->FindTexture(name);
}

void CImageWidget::SetTextureFullPath(const std::string& name, const TCHAR* fullPath)
{
	m_scene->GetSceneResource()->LoadTextureFullPath(name, fullPath);
	m_texture = m_scene->GetSceneResource()->FindTexture(name);
}

void CImageWidget::SetColorKey(unsigned char r, unsigned char g, unsigned char b)
{
	if (m_texture)
	{
		m_texture->SetColorKey(r, g, b);
	}
}

bool CImageWidget::Init()
{
	return true;
}

void CImageWidget::Update(float deltaTime)
{
}

void CImageWidget::PostUpdate(float deltaTime)
{
}

void CImageWidget::Render(HDC hDC, float deltaTime)
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
									(int)m_size.y,m_texture->GetDC(),0, 0, 
									(int)m_size.x, 
									(int)m_size.y, m_texture->GetColorKey());
			}
			else
			{
				BitBlt(hDC, (int)renderPos.x, 
							(int)renderPos.y,
							(int)m_size.x, 
							(int)m_size.y, m_texture->GetDC(),0, 0, SRCCOPY);
			}
		}
		else
		{
			if (m_texture->GetEnableColorKey())
			{
				TransparentBlt(hDC, (int)renderPos.x, 
									(int)renderPos.y,
									(int)m_size.x, 
									(int)m_size.y,m_texture->GetDC(),0, 0, 
									(int)m_size.x, 
									(int)m_size.y,m_texture->GetColorKey());
			}
			else
			{
				BitBlt(hDC, (int)renderPos.x, 
							(int)renderPos.y,
							(int)m_size.x, 
							(int)m_size.y,m_texture->GetDC(),0, 0, SRCCOPY);
			}
		}
	}
	else
	{
		Rectangle(hDC,  (int)renderPos.x, 
						(int)renderPos.y,
						(int)(renderPos.x + m_size.x), 
						(int)(renderPos.y + m_size.y));
	}
}

void CImageWidget::Render(HDC hDC, const Vector2& pos, float deltaTime)
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
									(int)m_size.y,m_texture->GetDC(),0, 0, 
									(int)m_size.x, 
									(int)m_size.y,m_texture->GetColorKey());
			}
			else
			{
				BitBlt(hDC, (int)renderPos.x, 
							(int)renderPos.y,
							(int)m_size.x, 
							(int)m_size.y,m_texture->GetDC(),0, 0, SRCCOPY);
			}
		}
		else
		{
			if (m_texture->GetEnableColorKey())
			{
				TransparentBlt(hDC, (int)renderPos.x, 
									(int)renderPos.y,
									(int)m_size.x, 
									(int)m_size.y,m_texture->GetDC(),0, 0, 
									(int)m_size.x,	
									(int)m_size.y,m_texture->GetColorKey());
			}
			else
			{
				BitBlt(hDC, (int)renderPos.x, 
							(int)renderPos.y,
							(int)m_size.x, 
							(int)m_size.y,m_texture->GetDC(),0, 0, SRCCOPY);
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

#ifdef UNICODE
void CImageWidget::SetTexture(const std::string& name, const std::vector<std::wstring>& vecFileName, const std::string& pathName)
{
	m_scene->GetSceneResource()->LoadTexture(name, vecFileName, pathName);
	m_texture = m_scene->GetSceneResource()->FindTexture(name);
}
void CImageWidget::SetTextureFullPath(const std::string& name, const std::vector<std::wstring>& vecFullPath)
{
	m_scene->GetSceneResource()->LoadTextureFullPath(name, vecFullPath);
	m_texture = m_scene->GetSceneResource()->FindTexture(name);
}
#else
void CImageWidget::SetTexture(const std::string& name, const std::vector<std::string>& vecFileName, const std::string& pathName)
{
	m_scene->GetSceneResource()->LoadTexture(name, vecFileName, pathName);
	m_texture = m_scene->GetSceneResource()->FindTexture(name);
}
void CImageWidget::SetTextureFullPath(const std::string& name, const std::vector<std::string>& vecFullPath)
{
	m_scene->GetSceneResource()->LoadTextureFullPath(name, vecFullPath);
	m_texture = m_scene->GetSceneResource()->FindTexture(name);
}
#endif // UNICODE