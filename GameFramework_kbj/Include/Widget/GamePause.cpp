#include "GamePause.h"
#include "ImageWidget.h"
//#include "../GameManager.h"
//#include "../Input.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"
#include "../Scene/SceneManager.h"

CGamePause::CGamePause()
{
}

CGamePause::~CGamePause()
{
}

bool CGamePause::Init()
{
	if (!CWidgetWindow::Init())
	{
		return false;
	}
	SetSize(1280.f, 720.f);
	m_scene->GetSceneResource()->LoadSound("Effect", "PopWindow", false, "click.mp3");

	CImageWidget* pause = CreateWidget<CImageWidget>("GamePause");
	pause->SetTexture("GamePause", TEXT("control_tutorial.bmp"));
	pause->SetSize(666.f, 512.f);
	pause->SetPos(307.f,104.f);
	pause->SetColorKey(255, 0, 255);
	return true;
}

void CGamePause::Update(float deltaTime)
{
	CWidgetWindow::Update(deltaTime);
}

void CGamePause::PostUpdate(float deltaTime)
{
	CWidgetWindow::PostUpdate(deltaTime);
}
