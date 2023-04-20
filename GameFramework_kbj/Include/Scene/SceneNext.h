#pragma once
#include "Scene.h"
class CSceneNext :public CScene
{
private:
	friend class CSceneManager;
	std::string m_SceneName;
protected:
	CSceneNext();
	virtual ~CSceneNext();
public:
	bool Init();
	virtual void Update(float deltaTime);
};

