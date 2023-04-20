#include "CharacterHUD.h"
#include "../GameManager.h"
#include "ProgressBar.h"
#include "ImageWidget.h"
#include "Text.h"

CCharacterHUD::CCharacterHUD()
{
}

CCharacterHUD::~CCharacterHUD()
{
}

void CCharacterHUD::SetHP(float HP)
{
	m_HPBar->SetValue(HP);
}

bool CCharacterHUD::Init()
{
	if (!CWidgetWindow::Init())
	{
		return false;
	}
	SetSize(75.f, 600.f);
	SetPos(95.f, 50.f);

	m_HPBarFrame = CreateWidget<CImageWidget>("HPBarFrame");
	m_HPBarFrame->SetTexture("BarFrame", TEXT("BarBack.bmp"));
	m_HPBarFrame->SetColorKey(255, 0, 255);
	m_HPBarFrame->SetSize(50.f, 600.f);

	m_HPBar = CreateWidget<CProgressBar>("HPBar");
	m_HPBar->SetTexture(EProgressBar_Texture_Type::Bar, "HPBar", TEXT("BarDefault.bmp"));
	m_HPBar->SetSize(50.f, 585.f);
	m_HPBar->SetPos(10.f, 10.f);
	m_HPBar->SetBarDir(EProgressBar_Dir::BottomToTop);

	m_FPSText = CreateWidget<CText>("FPS");
	m_FPSText->SetText(TEXT("FPS"));
	m_FPSText->SetPos(-95.f, -50.f);
	m_FPSText->SetTextColor(255, 0, 0);
	m_FPSText->EnableShadow(true);
	m_FPSText->SetShadowOffset(2.f, 2.f);

	return true;
}

void CCharacterHUD::Update(float deltaTime)
{
	CWidgetWindow::Update(deltaTime);
	float FPS = CGameManager::GetInst()->GetFPS();
	char	text[256] = {};
	sprintf_s(text, "FPS : %.5f", FPS);
	TCHAR	unicode[256] = {};
	int length = MultiByteToWideChar(CP_ACP, 0, text, -1, 0, 0);
	MultiByteToWideChar(CP_ACP, 0, text, -1, unicode, length);
	m_FPSText->SetText(unicode);
}
