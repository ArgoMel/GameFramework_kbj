#include "Number.h"
#include "../Resource/Texture/Texture.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"
#include "WidgetWindow.h"

CNumber::CNumber()
	: m_number(0)
{
}

CNumber::CNumber(const CNumber& widget) 
	: CWidget(widget)
	, m_number(widget.m_number)
{
}

CNumber::~CNumber()
{
}

void CNumber::SetTexture(const std::string& name, const TCHAR* fileName, const std::string& pathName)
{
	m_scene->GetSceneResource()->LoadTexture(name, fileName, pathName);
	m_texture = m_scene->GetSceneResource()->FindTexture(name);
}

void CNumber::SetTextureFullPath(const std::string& name, const TCHAR* fullPath)
{
	m_scene->GetSceneResource()->LoadTextureFullPath(name, fullPath);
	m_texture = m_scene->GetSceneResource()->FindTexture(name);
}

void CNumber::SetColorKey(unsigned char r, unsigned char g, unsigned char b)
{
	if (m_texture)
	{
		m_texture->SetColorKey(r, g, b);
	}
}

bool CNumber::Init()
{
	return true;
}

void CNumber::Update(float deltaTime)
{
	// 숫자를 각 자리별로 분할한다.
	// 123 % 10 = 3    123 / 10 = 12   12 % 10 = 2  12 / 10 = 1   1 % 10 = 1   1 / 10 = 0
	if (m_number == 0)
	{
		m_vecNumber.clear();
		m_vecNumber.push_back(0);
		m_vecNumber.push_back(0);
	}
	else
	{
		int	number = m_number;
		std::stack<int>	numberStack;
		while (number > 0)
		{
			numberStack.push(number % 10);
			number /= 10;
		}
		m_vecNumber.clear();
		if (m_number< 10)
		{
			m_vecNumber.push_back(0);
		}
		while (!numberStack.empty())
		{
			m_vecNumber.push_back(numberStack.top());
			numberStack.pop();
		}
	}
}

void CNumber::PostUpdate(float deltaTime)
{
}

void CNumber::Render(HDC hDC, float deltaTime)
{
	if (!m_vecNumber.empty())
	{
		Vector2	renderPos = m_pos + m_owner->GetPos();
		if (m_texture)
		{
			size_t	size = m_vecNumber.size();
			for (size_t i = 0; i < size; ++i)
			{
				if (m_texture->GetTextureType() == ETexture_Type::Sprite)
				{
					if (m_texture->GetEnableColorKey())
					{
						TransparentBlt(hDC, (int)(renderPos.x + i * m_size.x), 
											(int)renderPos.y,
											(int)m_size.x, 
											(int)m_size.y,m_texture->GetDC(),
											(int)(m_vecNumber[i] * m_size.x), 0,
											(int)m_size.x, 
											(int)m_size.y,m_texture->GetColorKey());
					}
					else
					{
						BitBlt(hDC, (int)(renderPos.x + i * m_size.x),
									(int)renderPos.y,
									(int)m_size.x, 
									(int)m_size.y,m_texture->GetDC(),
									(int)(m_vecNumber[i] * m_size.x), 0, SRCCOPY);
					}
				}
				else
				{
					if (m_texture->GetEnableColorKey())
					{
						TransparentBlt(hDC, (int)(renderPos.x + i * m_size.x),
											(int)renderPos.y,
											(int)m_size.x, 
											(int)m_size.y,m_texture->GetDC(m_vecNumber[i]),0, 0, 
											(int)m_size.x, 
											(int)m_size.y,m_texture->GetColorKey());
					}
					else
					{
						BitBlt(hDC, (int)(renderPos.x + i * m_size.x),
									(int)renderPos.y,
									(int)m_size.x, 
									(int)m_size.y,m_texture->GetDC(m_vecNumber[i]),0, 0, SRCCOPY);
					}
				}
			}
		}
	}
}

void CNumber::Render(HDC hDC, const Vector2& pos, float deltaTime)
{
	if (!m_vecNumber.empty())
	{
		Vector2	renderPos = pos;
		if (m_texture)
		{
			size_t	size = m_vecNumber.size();
			for (size_t i = 0; i < size; ++i)
			{
				if (m_texture->GetTextureType() == ETexture_Type::Sprite)
				{
					if (m_texture->GetEnableColorKey())
					{
						TransparentBlt(hDC, (int)(renderPos.x + i * m_size.x), 
											(int)renderPos.y,
											(int)m_size.x, 
											(int)m_size.y,m_texture->GetDC(),
											(int)(m_vecNumber[i] * m_size.x), 0,
											(int)m_size.x, 
											(int)m_size.y,m_texture->GetColorKey());
					}
					else
					{
						BitBlt(hDC, (int)(renderPos.x + i * m_size.x),
									(int)renderPos.y,
									(int)m_size.x, 
									(int)m_size.y,m_texture->GetDC(),
									(int)(m_vecNumber[i] * m_size.x), 0, SRCCOPY);
					}
				}
				else
				{
					if (m_texture->GetEnableColorKey())
					{
						TransparentBlt(hDC, (int)(renderPos.x + i * m_size.x),
											(int)renderPos.y,
											(int)m_size.x, 
											(int)m_size.y,m_texture->GetDC(m_vecNumber[i]),0, 0, 
											(int)m_size.x, 
											(int)m_size.y,m_texture->GetColorKey());
					}
					else
					{
						BitBlt(hDC, (int)(renderPos.x + i * m_size.x),
									(int)renderPos.y,
									(int)m_size.x, 
									(int)m_size.y,m_texture->GetDC(m_vecNumber[i]),0, 0, SRCCOPY);
					}
				}
			}
		}
	}
}

#ifdef UNICODE
void CNumber::SetTexture(const std::string& name, const std::vector<std::wstring>& vecFileName, const std::string& pathName)
{
	m_scene->GetSceneResource()->LoadTexture(name, vecFileName, pathName);
	m_texture = m_scene->GetSceneResource()->FindTexture(name);
}

void CNumber::SetTextureFullPath(const std::string& name, const std::vector<std::wstring>& vecFullPath)
{
	m_scene->GetSceneResource()->LoadTextureFullPath(name, vecFullPath);
	m_texture = m_scene->GetSceneResource()->FindTexture(name);
}
#else
void CNumber::SetTexture(const std::string& name, const std::vector<std::string>& vecFileName, const std::string& pathName)
{
	m_scene->GetSceneResource()->LoadTexture(name, vecFileName, pathName);
	m_texture = m_scene->GetSceneResource()->FindTexture(name);
}

void CNumber::SetTextureFullPath(const std::string& name, const std::vector<std::string>& vecFullPath)
{
	m_scene->GetSceneResource()->LoadTextureFullPath(name, vecFullPath);
	m_texture = m_scene->GetSceneResource()->FindTexture(name);
}
#endif // UNICODE