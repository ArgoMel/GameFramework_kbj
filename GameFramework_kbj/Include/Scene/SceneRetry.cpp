#include "SceneRetry.h"
#include "SceneResource.h"
#include "SceneManager.h"
#include "Scene00.h"
#include "Scene01.h"
#include "Scene02.h"

CSceneRetry::CSceneRetry()
{
}

CSceneRetry::~CSceneRetry()
{
}

bool CSceneRetry::Init()
{
	m_SceneName = CSceneManager::GetInst()->GetSceneName();
	return true;
}

void CSceneRetry::Update(float deltaTime)
{
	if (m_SceneName == "CScene00")
	{
		CSceneManager::GetInst()->CreateScene<CScene00>();
	}
	else if (m_SceneName == "CScene01")
	{
		CSceneManager::GetInst()->CreateScene<CScene01>();
	}
	else if (m_SceneName == "CScene02")
	{
		CSceneManager::GetInst()->CreateScene<CScene02>();
	}
}
