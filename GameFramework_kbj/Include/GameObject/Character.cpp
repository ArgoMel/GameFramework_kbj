#include "Character.h"

CCharacter::CCharacter()
{
	SetTypeID<CCharacter>();
}

CCharacter::CCharacter(const CCharacter& obj)
	:CGameObject(obj)
{
}

CCharacter::~CCharacter()
{
}

bool CCharacter::Init()
{
	return true;
}

void CCharacter::Update(float deltaTime)
{
	CGameObject::Update(deltaTime);
}

void CCharacter::Render(HDC hDC,float deltaTime)
{
	CGameObject::Render(hDC, deltaTime);
}

float CCharacter::InflictDamage(float damage)
{
	return CGameObject::InflictDamage(damage);
}
