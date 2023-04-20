#pragma once
#include "Scene.h"
class CSceneRetry :public CScene
{
private:
	friend class CSceneManager;
	std::string m_SceneName;
protected:
	CSceneRetry();
	virtual ~CSceneRetry();
public:
	bool Init();
	virtual void Update(float deltaTime);
};

