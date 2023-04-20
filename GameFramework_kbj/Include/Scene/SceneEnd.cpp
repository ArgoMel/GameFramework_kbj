#include "SceneEnd.h"
#include "SceneResource.h"
#include "Camera.h"
#include "../GameObject/BackObj.h"
#include "../Widget/ClearWindow.h"

void CSceneEnd::CreateAnimationSequence()
{
}

CSceneEnd::CSceneEnd()
{
}

CSceneEnd::~CSceneEnd()
{
}

bool CSceneEnd::Init()
{
	SetName("CSceneEnd");

	CreateAnimationSequence();
	GetSceneResource()->LoadSound("BGM", "GameClear", true, "bg_7.ogg");
	GetSceneResource()->SoundPlay("GameClear");
	GetSceneResource()->SetVolume(20);

	CBackObj* bg= CreateObject<CBackObj>("BackObj");
	bg->SetTexture("GameClearBG", TEXT("Map/End_scene_bg.bmp"));
	bg->SetColorKey(255, 0, 255);

	CreateWidgetWindow<CClearWindow>("ClearWindow");
	return true;
}
