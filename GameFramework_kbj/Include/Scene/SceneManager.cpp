#include "SceneManager.h"
#include "Scene01.h"
#include "Scene02.h"
#include "Scene_start.h"
#include "SceneEnd.h"
#include "../Input.h"

DEFINITION_SINGLE(CSceneManager)
CSceneManager::CSceneManager()
    : m_scene(nullptr)
    , m_nextScene(nullptr)
{}

CSceneManager::~CSceneManager()
{
    SAFE_DELETE(m_nextScene);
    SAFE_DELETE(m_scene);
}

bool CSceneManager::ChangeScene()
{
    if (m_nextScene)
    {
        SAFE_DELETE(m_scene);
        //CInput::GetInst()->ClearCallback();
        m_scene = m_nextScene;
        m_nextScene = nullptr;
        return true;
    }
    return false;
}
bool CSceneManager::Init()
{
    CreateScene<CScene_start>();
    //CreateScene<CScene01>();
    //CreateScene<CScene02>();
    //CreateScene<CSceneEnd>();
    return true;
}

bool CSceneManager::Update(float deltatime)
{
    m_scene->Update(deltatime);
    return ChangeScene();
}

bool CSceneManager::PostUpdate(float deltaTime)
{
    m_scene->PostUpdate(deltaTime);
    return ChangeScene();
}

void CSceneManager::Render(HDC hdc, float deltatime)
{
    m_scene->Render(hdc, deltatime);
}