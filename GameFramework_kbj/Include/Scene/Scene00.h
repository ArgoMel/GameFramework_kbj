#pragma once
#include "Scene.h"

class CScene00 : public CScene
{
private:
	friend class CSceneManager;
	//CSharedPtr<class CBoss>	m_boss;
	void CreateAnimationSequence();
protected:
	CScene00();
	virtual ~CScene00();
public:
	bool Init();
};

