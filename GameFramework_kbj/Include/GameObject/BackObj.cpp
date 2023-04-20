#include "BackObj.h"

CBackObj::CBackObj()
{
	SetTypeID<CBackObj>();
	m_renderLayer = ERender_Layer::Back;
}

CBackObj::CBackObj(const CBackObj& obj)
	:CGameObject(obj)
{
}

CBackObj::~CBackObj()
{
}

bool CBackObj::Init()
{
	SetPos(0.f, 0.f);
	SetSize(1280.f, 720.f);
	SetPivot(0.f, 0.f);
	SetTexture("BackGround", TEXT("Map/play_bg.bmp"));
	SetColorKey(255,0,255);
	return true;
}

void CBackObj::Update(float deltaTime)
{
	CGameObject::Update(deltaTime);
}

void CBackObj::Render(HDC hDC, float deltaTime)
{
	CGameObject::Render(hDC, deltaTime);
}
