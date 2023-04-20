#include "Scene_start.h"
#include "SceneResource.h"
#include "Camera.h"
#include "../Input.h"
#include "../Widget/StartWindow.h"

CScene_start::CScene_start()
{
}

CScene_start::~CScene_start()
{
}

bool CScene_start::Init()
{
	GetSceneResource()->LoadSound("BGM", "Title", true, "login_scene.mp3");
	GetSceneResource()->SoundPlay("Title");
	GetSceneResource()->SetVolume(20);

	GetCamera()->SetResolution(1280.f, 720.f);
	GetCamera()->SetWorldResolution(1280.f, 720.f);
	GetCamera()->SetTargetPivot(0.5f, 0.5f);
	CreateWidgetWindow<CStartWindow>("StartWindow");
	return true;
}
