#pragma once
#include "Scene.h"
class CScene01 : public CScene
{
private:
	friend class CSceneManager;
	void CreateAnimationSequence();
protected:
	CScene01();
	virtual ~CScene01();
public:
	bool Init();
};

