#include "SceneNext.h"
#include "SceneResource.h"
#include "SceneManager.h"
#include "Scene01.h"
#include "Scene02.h"
#include "SceneEnd.h"

CSceneNext::CSceneNext()
{
}

CSceneNext::~CSceneNext()
{
}

bool CSceneNext::Init()
{
	m_SceneName = CSceneManager::GetInst()->GetSceneName();
	return true;
}

void CSceneNext::Update(float deltaTime)
{
	if (m_SceneName == "CScene00")
	{
		CSceneManager::GetInst()->CreateScene<CScene01>();
	}
	else if (m_SceneName == "CScene01")
	{
		CSceneManager::GetInst()->CreateScene<CScene02>();
	}
	else if (m_SceneName == "CScene02")
	{
		CSceneManager::GetInst()->CreateScene<CSceneEnd>();
	}
}
