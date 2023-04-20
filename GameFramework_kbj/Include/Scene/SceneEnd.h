#pragma once
#include "Scene.h"
class CSceneEnd :public CScene
{
private:
	friend class CSceneManager;
	void CreateAnimationSequence();
protected:
	CSceneEnd();
	virtual ~CSceneEnd();
public:
	bool Init();
};

