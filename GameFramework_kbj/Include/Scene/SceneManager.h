#pragma once
#include "../GameInfo.h"
#include "../SingletonMacro.h"
class CSceneManager
{
	DECLARE_SINGLE(CSceneManager)
private:
	class CScene* m_scene;
	class CScene* m_nextScene;
	std::string m_SceneName;
	bool ChangeScene();
public:
	class CScene* GetScene()	const
	{
		return m_scene;
	}
	std::string GetSceneName()	const
	{
		return m_SceneName;
	}
	bool Init();
	bool Update(float deltatime);
	bool PostUpdate(float deltaTime);
	void Render(HDC hdc, float deltatime);
	template<typename T>
	bool CreateScene()
	{
		T* scene = new T;
		if(!scene->Init())
		{
			SAFE_DELETE(scene);
			return false;
		}
		if (!m_scene) 
		{
			m_scene = (CScene*)scene;
		}
		else
		{
			m_nextScene = (CScene*)scene;
		}
		m_SceneName = scene->GetName();
		return true;
	}
};

