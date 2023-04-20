#include "ClearWindow.h"
#include "ImageWidget.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"
#include "../Scene/SceneManager.h"

CClearWindow::CClearWindow()
{
	m_OutputSize = Vector2(0,100.f);
}

CClearWindow::~CClearWindow()
{
}

bool CClearWindow::Init()
{
	if (!CWidgetWindow::Init())
	{
		return false;
	}
	SetSize(1280.f, 720.f);

	m_Image = CreateWidget<CImageWidget>("Thanks");
	m_Image->SetTexture("Thanks", TEXT("Game_over/Clear.bmp"));
	m_Image->SetColorKey(255,0,255);
	m_Image->SetPos(340.f, 50.f);
	return true;
}

void CClearWindow::Update(float deltaTime)
{
	CWidgetWindow::Update(deltaTime);
	if(m_OutputSize.x<600.f)
	{
		m_OutputSize.x += 400.f*deltaTime;
		m_Image->SetSize(m_OutputSize);
		if(m_OutputSize.x>600.f)
		{
			m_OutputSize = 600.f;
		}
	}
}
