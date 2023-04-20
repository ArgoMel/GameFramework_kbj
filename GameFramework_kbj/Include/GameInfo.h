#pragma once
#include <Windows.h>
#include <list>
#include <vector>
#include <unordered_map>
#include <crtdbg.h>
#include <typeinfo>
#include <string>
#include <functional>
#include <algorithm>
#include <stack>
#include <assert.h>
#include <time.h>
#include <TCHAR.h>
#include "Vector2.h"
#include "SharedPtr.h"
#include "Flag.h"
#include "fmod.hpp"

#pragma comment(lib, "msimg32.lib")
#pragma comment(lib, "../Bin/fmod_vc.lib")

#define	TILE	Vector2(52.f,52.f)
#define	START_TILE	Vector2(277.f,40.f)
#define	GRAVITY	9.8f
#define	ROOT_PATH		"RootPath"
#define	TEXTURE_PATH	"TexturePath"
#define	SOUND_PATH		"SoundPath"
#define	FONT_PATH		"FontPath"
#define	MAP_PATH		"MapPath"
#define	SAFE_DELETE(p)	if(p)	{ delete p; p = nullptr; }
#define	SAFE_DELETE_ARRAY(p)	if(p)	{ delete[] p; p = nullptr; }
#define	SAFE_RELEASE(p)	if(p)	{ p->Release(); p = nullptr; }
#define	DELTA_TIME	CGameManager::GetInst()->GetDeltaTime()

struct Resolution
{
	int	width;
	int	height;
};

struct AnimationFrameData
{
	Vector2	start;
	Vector2	end;
};

struct CollisionProfile
{
	std::string							name;
	ECollision_Channel					channel;
	bool								enable;
	std::vector<ECollision_Interaction>	vecCollisionInteraction;

	CollisionProfile() 
		:channel(ECollision_Channel::Default)
		,enable(true)
	{
	}
};

struct BoxInfo
{
	Vector2	LT;
	Vector2	RB;
};

struct CircleInfo
{
	Vector2	center;
	float	radius;
};

float RadianToDegree(float radian);
float DegreeToRadian(float degree);