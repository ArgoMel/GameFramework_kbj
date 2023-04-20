#pragma once
#include "Scene.h"

class CScene_start : public CScene
{
protected:
	friend class CSceneManager;
	CScene_start();
	virtual ~CScene_start();
public:
	bool Init();
};

