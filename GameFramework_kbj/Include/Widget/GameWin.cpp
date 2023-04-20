#include "GameWin.h"
#include "Button.h"
#include "ImageWidget.h"
#include "../GameManager.h"
#include "../Input.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"
#include "../Scene/SceneNext.h"
#include "../Scene/SceneManager.h"

CGameWin::CGameWin()
	: m_ImageMaxY(250.f)
{
}

CGameWin::~CGameWin()
{
}

bool CGameWin::Init()
{
	if (!CWidgetWindow::Init())
	{
		return false;
	}
	SetSize(1280.f, 720.f);
	m_scene->GetSceneResource()->LoadSound("UI", "ButtonHovered", false, "button_highlight.wav");
	m_scene->GetSceneResource()->LoadSound("UI", "ButtonClick", false, "click.mp3");
	m_scene->GetSceneResource()->SoundPlay("Win");

	m_Win = CreateWidget<CImageWidget>("Win");
	m_Win->SetTexture("Win", TEXT("Game_start/WIN.bmp"));
	m_Win->SetSize(462.f, 100.f);
	m_Win->SetPos(410.f, -100.f);
	m_Win->SetColorKey(255, 0, 255);
	return true;
}

void CGameWin::Update(float deltaTime)
{
	CWidgetWindow::Update(deltaTime);
	Vector2 WinPos = m_Win->GetPos();
	if (WinPos.y < m_ImageMaxY)
	{
		m_Win->SetPos(WinPos.x, WinPos.y + 500.f * deltaTime);
	}
}

void CGameWin::PostUpdate(float deltaTime)
{
	CWidgetWindow::PostUpdate(deltaTime);
	Vector2 WinPos = m_Win->GetPos();
	if (WinPos.y >= m_ImageMaxY && !m_ExitButton)
	{
		CButton* m_NextButton = CreateWidget<CButton>("NextButton");
		m_NextButton->SetTexture("NextButton", TEXT("buttons/Button_play.bmp"));
		m_NextButton->SetColorKey(255, 0, 255);
		m_NextButton->SetButtonStateData(EButton_State::Normal, Vector2(0.f, 0.f), Vector2(200.f, 200.f));
		m_NextButton->SetButtonStateData(EButton_State::MouseHovered, Vector2(200.f, 0.f), Vector2(400.f, 200.f));
		m_NextButton->SetButtonStateData(EButton_State::Click, Vector2(400.f, 0.f), Vector2(600.f, 200.f));
		m_NextButton->SetButtonStateData(EButton_State::Disable, Vector2(600.f, 0.f), Vector2(800.f, 200.f));
		m_NextButton->SetSound(EButton_Sound_State::MouseHovered, "ButtonHovered");
		m_NextButton->SetSound(EButton_Sound_State::Click, "ButtonClick");
		m_NextButton->SetPos(420.f, 400.f);
		m_NextButton->SetZOrder(1);
		m_NextButton->SetCallback<CGameWin>(EButton_Sound_State::Click, this, &CGameWin::NextButtonCallback);

		m_ExitButton = CreateWidget<CButton>("ExitButton");
		m_ExitButton->SetTexture("ExitButton", TEXT("buttons/Button_exit.bmp"));
		m_ExitButton->SetColorKey(255, 0, 255);
		m_ExitButton->SetButtonStateData(EButton_State::Normal, Vector2(0.f, 0.f), Vector2(200.f, 200.f));
		m_ExitButton->SetButtonStateData(EButton_State::MouseHovered, Vector2(200.f, 0.f), Vector2(400.f, 200.f));
		m_ExitButton->SetButtonStateData(EButton_State::Click, Vector2(400.f, 0.f), Vector2(600.f, 200.f));
		m_ExitButton->SetButtonStateData(EButton_State::Disable, Vector2(600.f, 0.f), Vector2(800.f, 200.f));
		m_ExitButton->SetSound(EButton_Sound_State::MouseHovered, "ButtonHovered");
		m_ExitButton->SetSound(EButton_Sound_State::Click, "ButtonClick");
		m_ExitButton->SetPos(660.f, 400.f);
		m_ExitButton->SetZOrder(1);
		m_ExitButton->SetCallback<CGameWin>(EButton_Sound_State::Click, this, &CGameWin::EndButtonCallback);
	}
}

void CGameWin::NextButtonCallback()
{
	CInput::GetInst()->ClearCallback();
	m_scene->GetSceneResource()->SoundStop("stage00");
	m_scene->GetSceneResource()->SoundStop("stage01");
	m_scene->GetSceneResource()->SoundStop("stage02");
	CSceneManager::GetInst()->CreateScene<CSceneNext>();
}

void CGameWin::EndButtonCallback()
{
	CGameManager::GetInst()->Exit();
}
