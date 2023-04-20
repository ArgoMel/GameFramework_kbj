#include "StartWindow.h"
#include "Button.h"
#include "ImageWidget.h"
#include "Text.h"
#include "../GameManager.h"
#include "../Input.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"
#include "../Scene/Scene00.h"
#include "../Scene/Scene_edit.h"
#include "../Scene/SceneManager.h"

CStartWindow::CStartWindow()
	: m_QuitTime(0.f)
	, m_IsQuit(false)
{
}

CStartWindow::~CStartWindow()
{
}

bool CStartWindow::Init()
{
	if (!CWidgetWindow::Init())
	{
		return false;
	}
	m_scene->GetSceneResource()->LoadSound("UI", "ButtonHovered", false,"button_highlight.wav");
	m_scene->GetSceneResource()->LoadSound("UI", "ButtonClick", false,"click.mp3");
	SetSize(1280.f, 720.f);

	CImageWidget* back = CreateWidget<CImageWidget>("Back");
	back->SetTexture("StartBack", TEXT("title_scene_bg.bmp"));
	back->SetSize(1280.f, 720.f);

	CButton* startButton = CreateWidget<CButton>("StartButton");
	startButton->SetTexture("StartButton", TEXT("buttons/Button_play.bmp"));
	startButton->SetColorKey(255, 0, 255);
	startButton->SetButtonStateData(EButton_State::Normal, Vector2(0.f, 0.f), Vector2(200.f, 200.f));
	startButton->SetButtonStateData(EButton_State::MouseHovered, Vector2(200.f, 0.f), Vector2(400.f, 200.f));
	startButton->SetButtonStateData(EButton_State::Click, Vector2(400.f, 0.f), Vector2(600.f, 200.f));
	startButton->SetButtonStateData(EButton_State::Disable, Vector2(600.f, 0.f), Vector2(800.f, 200.f));
	startButton->SetSound(EButton_Sound_State::MouseHovered, "ButtonHovered");
	startButton->SetSound(EButton_Sound_State::Click, "ButtonClick");
	startButton->SetPos(340.f, 410.f);
	startButton->SetZOrder(1);
	startButton->SetCallback<CStartWindow>(EButton_Sound_State::Click,this, &CStartWindow::StartButtonCallback);

	CButton* tileButton = CreateWidget<CButton>("TileButton");
	tileButton->SetTexture("TileButton", TEXT("buttons/Button_tile.bmp"));
	tileButton->SetColorKey(255, 0, 255);
	tileButton->SetButtonStateData(EButton_State::Normal, Vector2(0.f, 0.f), Vector2(200.f, 200.f));
	tileButton->SetButtonStateData(EButton_State::MouseHovered, Vector2(200.f, 0.f), Vector2(400.f, 200.f));
	tileButton->SetButtonStateData(EButton_State::Click, Vector2(400.f, 0.f), Vector2(600.f, 200.f));
	tileButton->SetButtonStateData(EButton_State::Disable, Vector2(600.f, 0.f), Vector2(800.f, 200.f));
	tileButton->SetSound(EButton_Sound_State::MouseHovered, "ButtonHovered");
	tileButton->SetSound(EButton_Sound_State::Click, "ButtonClick");
	tileButton->SetPos(540.f, 410.f);
	tileButton->SetZOrder(1);
	tileButton->SetCallback<CStartWindow>(EButton_Sound_State::Click, this, &CStartWindow::TileButtonCallback);

	CButton* endButton = CreateWidget<CButton>("EndButton");
	endButton->SetTexture("EndButton", TEXT("buttons/Button_exit.bmp"));
	endButton->SetColorKey(255, 0, 255);
	endButton->SetButtonStateData(EButton_State::Normal, Vector2(0.f, 0.f), Vector2(200.f, 200.f));
	endButton->SetButtonStateData(EButton_State::MouseHovered, Vector2(200.f, 0.f), Vector2(400.f, 200.f));
	endButton->SetButtonStateData(EButton_State::Click, Vector2(400.f, 0.f), Vector2(600.f, 200.f));
	endButton->SetButtonStateData(EButton_State::Disable, Vector2(600.f, 0.f), Vector2(800.f, 200.f));
	endButton->SetSound(EButton_Sound_State::MouseHovered, "ButtonHovered");
	endButton->SetSound(EButton_Sound_State::Click, "ButtonClick");
	endButton->SetPos(740.f, 410.f);
	endButton->SetZOrder(1);
	endButton->SetCallback<CStartWindow>(EButton_Sound_State::Click,this, &CStartWindow::EndButtonCallback);
	return true;
}

void CStartWindow::Update(float deltaTime)
{
	CWidgetWindow::Update(deltaTime);
	if (m_IsQuit)
	{
		m_QuitTime += deltaTime;
		if (m_QuitTime > 0.3f)
		{
			CGameManager::GetInst()->Exit();
		}
	}
}

void CStartWindow::StartButtonCallback()
{
	CInput::GetInst()->ClearCallback();
	CSceneManager::GetInst()->CreateScene<CScene00>();
}

void CStartWindow::TileButtonCallback()
{
	CInput::GetInst()->ClearCallback();
	CSceneManager::GetInst()->CreateScene<CScene_edit>();
}

void CStartWindow::EndButtonCallback()
{
	m_IsQuit = true;
}
