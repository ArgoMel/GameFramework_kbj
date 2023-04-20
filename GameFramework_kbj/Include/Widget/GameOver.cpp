#include "GameOver.h"
#include "Button.h"
#include "ImageWidget.h"
#include "../GameManager.h"
#include "../Input.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"
#include "../Scene/SceneRetry.h"
#include "../Scene/SceneManager.h"

CGameOver::CGameOver()
	: m_ImageMaxY(300.f)
{
}

CGameOver::~CGameOver()
{
}

bool CGameOver::Init()
{
	if (!CWidgetWindow::Init())
	{
		return false;
	}
	SetSize(1280.f, 720.f);
	m_scene->GetSceneResource()->LoadSound("UI", "ButtonHovered", false, "button_highlight.wav");
	m_scene->GetSceneResource()->LoadSound("UI", "ButtonClick", false, "click.mp3");
	m_scene->GetSceneResource()->SoundPlay("Lose");

	m_Game = CreateWidget<CImageWidget>("GameOver");
	m_Game->SetTexture("GameOver", TEXT("Game_over/GAME.bmp"));
	m_Game->SetSize(351.f, 78.f);
	m_Game->SetPos(480.f, -100.f);
	m_Game->SetColorKey(255, 0, 255);

	m_Over = CreateWidget<CImageWidget>("Over");
	m_Over->SetTexture("Over", TEXT("Game_over/OVER.bmp"));
	m_Over->SetSize(443.f, 81.f);
	m_Over->SetPos(430.f, -20.f);
	m_Over->SetColorKey(255, 0, 255);
	return true;
}

void CGameOver::Update(float deltaTime)
{
	CWidgetWindow::Update(deltaTime);
	Vector2 GamePos = m_Game->GetPos();
	Vector2 OverPos = m_Over->GetPos();
	if (OverPos.y < m_ImageMaxY)
	{
		m_Game->SetPos(GamePos.x, GamePos.y + 500.f * deltaTime);
		m_Over->SetPos(OverPos.x, OverPos.y + 500.f * deltaTime);
	}
}

void CGameOver::PostUpdate(float deltaTime)
{
	CWidgetWindow::PostUpdate(deltaTime);
	Vector2 OverPos = m_Over->GetPos();
	if (OverPos.y >= m_ImageMaxY && !m_ExitButton)
	{
		CButton* m_RetryButton = CreateWidget<CButton>("RetryButton");
		m_RetryButton->SetTexture("RetryButton", TEXT("buttons/Button_retry.bmp"));
		m_RetryButton->SetColorKey(255, 0, 255);
		m_RetryButton->SetButtonStateData(EButton_State::Normal, Vector2(0.f, 0.f), Vector2(200.f, 200.f));
		m_RetryButton->SetButtonStateData(EButton_State::MouseHovered, Vector2(200.f, 0.f), Vector2(400.f, 200.f));
		m_RetryButton->SetButtonStateData(EButton_State::Click, Vector2(400.f, 0.f), Vector2(600.f, 200.f));
		m_RetryButton->SetButtonStateData(EButton_State::Disable, Vector2(600.f, 0.f), Vector2(800.f, 200.f));
		m_RetryButton->SetSound(EButton_Sound_State::MouseHovered, "ButtonHovered");
		m_RetryButton->SetSound(EButton_Sound_State::Click, "ButtonClick");
		m_RetryButton->SetPos(400.f, 400.f);
		m_RetryButton->SetZOrder(1);
		m_RetryButton->SetCallback<CGameOver>(EButton_Sound_State::Click, this, &CGameOver::RetryButtonCallback);

		m_ExitButton = CreateWidget<CButton>("ExitButton");
		m_ExitButton->SetTexture("ExitButton", TEXT("buttons/Button_exit.bmp"));
		m_ExitButton->SetColorKey(255, 0, 255);
		m_ExitButton->SetButtonStateData(EButton_State::Normal, Vector2(0.f, 0.f), Vector2(200.f, 200.f));
		m_ExitButton->SetButtonStateData(EButton_State::MouseHovered, Vector2(200.f, 0.f), Vector2(400.f, 200.f));
		m_ExitButton->SetButtonStateData(EButton_State::Click, Vector2(400.f, 0.f), Vector2(600.f, 200.f));
		m_ExitButton->SetButtonStateData(EButton_State::Disable, Vector2(600.f, 0.f), Vector2(800.f, 200.f));
		m_ExitButton->SetSound(EButton_Sound_State::MouseHovered, "ButtonHovered");
		m_ExitButton->SetSound(EButton_Sound_State::Click, "ButtonClick");
		m_ExitButton->SetPos(700.f, 400.f);
		m_ExitButton->SetZOrder(1);
		m_ExitButton->SetCallback<CGameOver>(EButton_Sound_State::Click, this, &CGameOver::EndButtonCallback);
	}
}

void CGameOver::RetryButtonCallback()
{
	CInput::GetInst()->ClearCallback();
	CSceneManager::GetInst()->CreateScene<CSceneRetry>();
}

void CGameOver::EndButtonCallback()
{
	CGameManager::GetInst()->Exit();
}
