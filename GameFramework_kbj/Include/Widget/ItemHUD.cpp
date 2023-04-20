#include "ItemHUD.h"
#include "../GameManager.h"
#include "ImageWidget.h"
#include "Text.h"
#include "Number.h"
#include "Button.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"

CItemHUD::CItemHUD()
	: m_time(0.f)
	, m_QuitTime(0.f)
	, m_IsQuit(false)
{
}

CItemHUD::~CItemHUD()
{
}

bool CItemHUD::Init()
{
	if (!CWidgetWindow::Init())
	{
		return false;
	}
	SetSize(1280.f, 720.f);
	//m_scene->GetSceneResource()->LoadSound("UI", "ButtonHovered", false, "button_highlight.wav");
	//m_scene->GetSceneResource()->LoadSound("UI", "ButtonClick", false, "click.mp3");

	m_minute = CreateWidget<CNumber>("Minute");
	m_minute->SetTexture("Number", TEXT("Number/number.bmp"));
	m_minute->SetColorKey(255, 0, 255);
	m_minute->SetSize(22.4f, 30.f);
	m_minute->SetPos(1140.f, 42.f);

	CImageWidget* colon = CreateWidget<CImageWidget>("Colon");
	colon->SetTexture("Colon", TEXT("Number/Colon.bmp"));
	colon->SetSize(20.f, 30.f);
	colon->SetPos(1180.f, 42.f);
	colon->SetColorKey(255, 0, 255);

	m_second = CreateWidget<CNumber>("Second");
	m_second->SetTexture("Number", TEXT("Number/number.bmp"));
	m_second->SetColorKey(255, 0, 255);
	m_second->SetSize(22.4f, 30.f);
	m_second->SetPos(1195.f, 42.f);

	CButton* endButton = CreateWidget<CButton>("QuitButton");
	endButton->SetTexture("QuitButton", TEXT("buttons/Button_quit.bmp"));
	endButton->SetColorKey(255, 0, 255);
	endButton->SetButtonStateData(EButton_State::Normal, Vector2(0.f, 0.f), Vector2(182.f, 42.f));
	endButton->SetButtonStateData(EButton_State::MouseHovered, Vector2(182.f, 0.f), Vector2(364.f, 42.f));
	endButton->SetButtonStateData(EButton_State::Click, Vector2(364.f, 0.f), Vector2(546.f, 42.f));
	endButton->SetButtonStateData(EButton_State::Disable, Vector2(546.f, 0.f), Vector2(728.f, 42.f));
	endButton->SetSound(EButton_Sound_State::MouseHovered, "ButtonHovered");
	endButton->SetSound(EButton_Sound_State::Click, "ButtonClick");
	endButton->SetPos(1072.f, 667.f);
	endButton->SetZOrder(1);
	endButton->SetCallback<CItemHUD>(EButton_Sound_State::Click, this, &CItemHUD::EndButtonCallback);
	return true;
}

void CItemHUD::Update(float deltaTime)
{
	CWidgetWindow::Update(deltaTime);
	m_time += deltaTime;
	if (m_time >= 1.f)
	{
		if(m_time>=60.f)
		{
			m_minute->AddNumber(1);
			m_second->SetNumber(0);
			m_time = 0.f;
		}
		m_second->SetNumber((int)m_time);
	}
	if(m_IsQuit)
	{
		m_QuitTime += deltaTime;
		if(m_QuitTime>0.3f)
		{
			CGameManager::GetInst()->Exit();
		}
	}
}

void CItemHUD::EndButtonCallback()
{
	m_IsQuit = true;
}
