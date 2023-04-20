#include "GameStart.h"
#include "ImageWidget.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"
#include "../GameObject/Player.h"
#include "../GameObject/Boss.h"
#include "../GameObject/KingSeal.h"
#include "../GameObject/EmperorPenguin.h"

CGameStart::CGameStart()
	: m_ImageMaxY(300.f)
	, m_ExistTime(2.f)
{
}

CGameStart::~CGameStart()
{
}

bool CGameStart::Init()
{
	if (!CWidgetWindow::Init())
	{
		return false;
	}
	SetSize(500.f, 200.f);

	CImageWidget* m_Game = CreateWidget<CImageWidget>("Game");
	m_Game->SetTexture("Game", TEXT("Game_start/GAME.bmp"));
	m_Game->SetSize(244.f, 54.f);
	m_Game->SetPos(525.f, -100.f);
	m_Game->SetColorKey(255, 0, 255);

	CImageWidget* m_Start = CreateWidget<CImageWidget>("Start");
	m_Start->SetTexture("Start", TEXT("Game_start/START.bmp"));
	m_Start->SetSize(477.f, 77.f);
	m_Start->SetPos(400.f, -20.f);
	m_Start->SetColorKey(255, 0, 255);

	m_scene->GetSceneResource()->SoundPlay("GameStart");
	m_scene->GetPlayer()->SetTimeScale(0.f);
	m_Boss = m_scene->FindObject<CBoss>("Boss");
	if (m_Boss)
	{
		m_Boss->SetTimeScale(0.f);
		return true;
	}
	m_Seal = m_scene->FindObject<CKingSeal>("Seal");
	if (m_Seal)
	{
		m_Seal->SetTimeScale(0.f);
		return true;
	}
	m_Penguin = m_scene->FindObject<CEmperorPenguin>("Penguin");
	if (m_Penguin)
	{
		m_Penguin->SetTimeScale(0.f);
		return true;
	}
	return true;
}

void CGameStart::Update(float deltaTime)
{
	CWidgetWindow::Update(deltaTime);
	m_ExistTime -= deltaTime;
	if(m_pos.y<m_ImageMaxY)
	{
		m_pos.y += 500.f*deltaTime;
	}
	if(m_ExistTime<0)
	{
		m_scene->GetPlayer()->SetTimeScale(1.f);
		if (m_Boss)
		{
			m_Boss->SetTimeScale(1.f);
		}
		else if(m_Seal)
		{
			m_Seal->SetTimeScale(1.f);
		}
		else if (m_Penguin)
		{
			m_Penguin->SetTimeScale(1.f);
		}
		SetActive(false);
	}
}
