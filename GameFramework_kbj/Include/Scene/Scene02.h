#pragma once
#include "Scene.h"
class CScene02 : public CScene
{
private:
	friend class CSceneManager;
	void CreateAnimationSequence();
protected:
	CScene02();
	virtual ~CScene02();
public:
	bool Init();
};

