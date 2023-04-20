#include "Scene01.h"
#include "SceneResource.h"
#include "Camera.h"
#include "../GameObject/Player.h"
#include "../GameObject/KingSeal.h"
#include "../GameObject/Wall.h"
#include "../GameObject/Sewer.h"
#include "../GameObject/BackObj.h"
#include "../GameObject/TileMap.h"
#include "../GameObject/Tile.h"
#include "../Widget/CharacterHUD.h"
#include "../Widget/ItemHUD.h"
#include "../Widget/GameStart.h"

CScene01::CScene01()
{
}

CScene01::~CScene01()
{
}

bool CScene01::Init()
{
	SetName("CScene01");

	CreateAnimationSequence();
	GetSceneResource()->LoadSound("BGM", "stage01", true, "bg_1.ogg");
	GetSceneResource()->LoadSound("Effect", "EnemySummon", false, "ef_0.ogg");
	GetSceneResource()->LoadSound("Effect", "EnemySummonError", false, "Error.mp3");
	GetSceneResource()->LoadSound("Effect", "EnemyDie", false, "enemy_die.ogg");
	GetSceneResource()->LoadSound("Effect", "BossDie", false, "boss_dead.ogg");
	GetSceneResource()->LoadSound("Effect", "BossSpin", false, "Spin.mp3");
	GetSceneResource()->LoadSound("Effect", "BossTornado", false, "Tornado.wav");
	GetSceneResource()->LoadSound("Effect", "BossStun", false, "Stun.wav");
	GetSceneResource()->LoadSound("Effect", "FallingBomb", false, "Falling.wav");
	GetSceneResource()->LoadSound("Effect", "SealHit", false, "SealHit.mp3");
	GetSceneResource()->LoadSound("Effect", "MarkerBreak", false, "marker_break.mp3");
	GetSceneResource()->LoadSound("Effect", "Bubble", false, "Bubble.wav");
	GetSceneResource()->LoadSound("Effect", "Pop", false, "Pop.wav");
	GetSceneResource()->LoadSound("Effect", "Bomb_set", false, "bomb_set.mp3");
	GetSceneResource()->LoadSound("Effect", "Bomb_wave", false, "wave.mp3");
	GetSceneResource()->LoadSound("Effect", "EatItem", false, "eat_item.mp3");
	GetSceneResource()->LoadSound("Effect", "Escape", false, "bomb_escape.mp3");
	GetSceneResource()->LoadSound("Effect", "Dart", false, "dart.wav");
	GetSceneResource()->LoadSound("Effect", "Lose", false, "lose.mp3");
	GetSceneResource()->LoadSound("Effect", "Win", false, "win.mp3");
	GetSceneResource()->LoadSound("Effect", "GameStart", false, "game_start.mp3");
	GetSceneResource()->SoundPlay("stage01");
	GetSceneResource()->SetVolume(20);

	CreateObject<CBackObj>("BackObj");
	CTileMap* tileMap = CreateObject<CTileMap>("TileMap");
	tileMap->LoadFileName("scene01.tmp", MAP_PATH);
	tileMap->SetPos(199.f, -30.f);

	CWall* wall = CreateObject<CWall>("Wall1");
	wall->ChangeAnimation("FlactoryBlock");
	wall->SetPos(277.f + 52.f, 40.f + 52.f * 12);
	wall = CreateObject<CWall>("Wall2");
	wall->ChangeAnimation("FlactoryBlock");
	wall->SetPos(277.f + 52.f*2, 40.f + 52.f * 11);
	wall = CreateObject<CWall>("Wall3");
	wall->ChangeAnimation("FlactoryBlock");
	wall->SetPos(277.f + 52.f * 3, 40.f + 52.f * 12);
	wall = CreateObject<CWall>("Wall4");
	wall->ChangeAnimation("FlactoryBlock");
	wall->SetPos(277.f + 52.f * 4, 40.f + 52.f * 11);
	wall = CreateObject<CWall>("Wall5");
	wall->ChangeAnimation("FlactoryBlock");
	wall->SetPos(277.f + 52.f * 5, 40.f + 52.f * 12);
	wall = CreateObject<CWall>("Wall6");
	wall->ChangeAnimation("FlactoryBlock");
	wall->SetPos(277.f + 52.f * 6, 40.f + 52.f * 11);
	wall = CreateObject<CWall>("Wall7");
	wall->ChangeAnimation("FlactoryBlock");
	wall->SetPos(277.f + 52.f * 7, 40.f + 52.f * 12);
	wall = CreateObject<CWall>("Wall8");
	wall->ChangeAnimation("FlactoryBlock");
	wall->SetPos(277.f + 52.f * 8, 40.f + 52.f * 11);
	wall = CreateObject<CWall>("Wall9");
	wall->ChangeAnimation("FlactoryBlock");
	wall->SetPos(277.f + 52.f * 9, 40.f + 52.f * 12);
	wall = CreateObject<CWall>("Wall10");
	wall->ChangeAnimation("FlactoryBlock");
	wall->SetPos(277.f + 52.f * 10, 40.f + 52.f * 11);
	wall = CreateObject<CWall>("Wall11");
	wall->ChangeAnimation("FlactoryBlock");
	wall->SetPos(277.f + 52.f * 11, 40.f + 52.f * 12);
	wall = CreateObject<CWall>("Wall12");
	wall->ChangeAnimation("FlactoryBlock");
	wall->SetPos(277.f + 52.f * 12, 40.f + 52.f * 11);
	wall = CreateObject<CWall>("Wall13");
	wall->ChangeAnimation("FlactoryBlock");
	wall->SetPos(277.f + 52.f * 13, 40.f + 52.f * 12);
	SetWallCount(13);

	CSewer* sewer= CreateObject<CSewer>("Sewer1");
	sewer->SetPos(START_TILE.x + TILE.x * 2, START_TILE.y + TILE.y * 2+sewer->GetOffsetSize().y);
	m_listSewer.push_back(sewer);
	sewer = CreateObject<CSewer>("Sewer2");
	sewer->SetPos(START_TILE.x + TILE.x * 12, START_TILE.y + TILE.y * 2 + sewer->GetOffsetSize().y);
	m_listSewer.push_back(sewer);
	sewer=CreateObject<CSewer>("Sewer3");
	sewer->SetPos(START_TILE.x + TILE.x * 2, START_TILE.y + TILE.y * 10 + sewer->GetOffsetSize().y);
	m_listSewer.push_back(sewer);
	sewer = CreateObject<CSewer>("Sewer4");
	sewer->SetPos(START_TILE.x + TILE.x * 12, START_TILE.y + TILE.y * 10 + sewer->GetOffsetSize().y);
	m_listSewer.push_back(sewer);

	CPlayer* player = CreateObject<CPlayer>("Player");
	SetPlayer(player);
	CreateObject<CKingSeal>("Seal");

	GetCamera()->SetResolution(1280.f, 720.f);
	GetCamera()->SetWorldResolution(1280.f, 720.f);
	GetCamera()->SetTargetPivot(0.5f, 0.5f);
	GetCamera()->SetTarget(player);

	CreateWidgetWindow<CCharacterHUD>("CharacterHUD");
	CreateWidgetWindow<CItemHUD>("ItemHUD");
	CreateWidgetWindow<CGameStart>("GameStart");
	return true;
}

void CScene01::CreateAnimationSequence()
{
//player
	GetSceneResource()->CreateAnimationSequence("PlayerStart", "PlayerStart", TEXT("Player/ready.bmp"), TEXTURE_PATH);
	GetSceneResource()->CreateAnimationSequence("PlayerIdle", "PlayerIdle", TEXT("Player/wait.bmp"), TEXTURE_PATH);
	GetSceneResource()->CreateAnimationSequence("PlayerUp", "PlayerUp", TEXT("Player/up.bmp"), TEXTURE_PATH);
	GetSceneResource()->CreateAnimationSequence("PlayerDown", "PlayerDown", TEXT("Player/down.bmp"), TEXTURE_PATH);
	GetSceneResource()->CreateAnimationSequence("PlayerLeft", "PlayerLeft", TEXT("Player/left.bmp"), TEXTURE_PATH);
	GetSceneResource()->CreateAnimationSequence("PlayerRight", "PlayerRight", TEXT("Player/right.bmp"), TEXTURE_PATH);
	GetSceneResource()->CreateAnimationSequence("PlayerBubble", "PlayerBubble", TEXT("Player/trap.bmp"), TEXTURE_PATH);
	GetSceneResource()->CreateAnimationSequence("PlayerDie", "PlayerDie", TEXT("Player/die.bmp"), TEXTURE_PATH);
	GetSceneResource()->CreateAnimationSequence("PlayerEscape", "PlayerEscape", TEXT("Player/live.bmp"), TEXTURE_PATH);
	GetSceneResource()->CreateAnimationSequence("PlayerInvisibleD", "PlayerInvisibleD", TEXT("Player/flash_shortD.bmp"), TEXTURE_PATH);
	GetSceneResource()->CreateAnimationSequence("PlayerInvisibleU", "PlayerInvisibleU", TEXT("Player/flash_shortU.bmp"), TEXTURE_PATH);
	GetSceneResource()->CreateAnimationSequence("PlayerInvisibleL", "PlayerInvisibleL", TEXT("Player/flash_shortL.bmp"), TEXTURE_PATH);
	GetSceneResource()->CreateAnimationSequence("PlayerInvisibleR", "PlayerInvisibleR", TEXT("Player/flash_shortR.bmp"), TEXTURE_PATH);
	//for (int i = 0; i < 18; ++i)
	//{
	//	GetSceneResource()->AddAnimationFrame("PlayerStart", 64.f * i, 0.f, 64.f, 86.f);
	//}
	//GetSceneResource()->SetColorKey("PlayerStart", 255, 0, 255);
	//for (int i = 0; i < 3; ++i)
	//{
	//	GetSceneResource()->AddAnimationFrame("PlayerIdle", 64.f * i, 0.f, 64.f, 76.f);
	//}
	//GetSceneResource()->SetColorKey("PlayerIdle", 255, 0, 255);
	//for (int i = 0; i < 8; ++i)
	//{
	//	GetSceneResource()->AddAnimationFrame("PlayerUp", 64.f * i, 0.f, 64.f, 76.f);
	//}
	//GetSceneResource()->SetColorKey("PlayerUp", 255, 0, 255);
	//for (int i = 0; i < 8; ++i)
	//{
	//	GetSceneResource()->AddAnimationFrame("PlayerDown", 64.f * i, 0.f, 64.f, 76.f);
	//}
	//GetSceneResource()->SetColorKey("PlayerDown", 255, 0, 255);
	//for (int i = 0; i < 6; ++i)
	//{
	//	GetSceneResource()->AddAnimationFrame("PlayerLeft", 64.f * i, 0.f, 64.f, 76.f);
	//}
	//GetSceneResource()->SetColorKey("PlayerLeft", 255, 0, 255);
	//for (int i = 0; i < 6; ++i)
	//{
	//	GetSceneResource()->AddAnimationFrame("PlayerRight", 64.f * i, 0.f, 64.f, 76.f);
	//}
	//GetSceneResource()->SetColorKey("PlayerRight", 255, 0, 255);
	//for (int i = 0; i < 13; ++i)
	//{
	//	GetSceneResource()->AddAnimationFrame("PlayerBubble", 88.f * i, 0.f, 88.f, 144.f);
	//}
	//GetSceneResource()->SetColorKey("PlayerBubble", 255, 0, 255);
	//for (int i = 1; i < 13; ++i)
	//{
	//	GetSceneResource()->AddAnimationFrame("PlayerDie", 88.f * i, 0.f, 88.f, 144.f);
	//}
	//GetSceneResource()->SetColorKey("PlayerDie", 255, 0, 255);
	//for (int i = 0; i < 5; ++i)
	//{
	//	GetSceneResource()->AddAnimationFrame("PlayerEscape", 88.f * i, 0.f, 88.f, 144.f);
	//}
	//GetSceneResource()->SetColorKey("PlayerEscape", 255, 0, 255);
	//for (int i = 0; i < 2; ++i)
	//{
	//	GetSceneResource()->AddAnimationFrame("PlayerInvisibleD", 64.f * i, 0.f, 64.f, 76.f);
	//}
	//GetSceneResource()->SetColorKey("PlayerInvisibleD", 255, 0, 255);
	//for (int i = 0; i < 2; ++i)
	//{
	//	GetSceneResource()->AddAnimationFrame("PlayerInvisibleU", 64.f * i, 0.f, 64.f, 76.f);
	//}
	//GetSceneResource()->SetColorKey("PlayerInvisibleU", 255, 0, 255);
	//for (int i = 0; i < 2; ++i)
	//{
	//	GetSceneResource()->AddAnimationFrame("PlayerInvisibleL", 64.f * i, 0.f, 64.f, 76.f);
	//}
	//GetSceneResource()->SetColorKey("PlayerInvisibleL", 255, 0, 255);
	//for (int i = 0; i < 2; ++i)
	//{
	//	GetSceneResource()->AddAnimationFrame("PlayerInvisibleR", 64.f * i, 0.f, 64.f, 76.f);
	//}
	//GetSceneResource()->SetColorKey("PlayerInvisibleR", 255, 0, 255);
//explosion
	GetSceneResource()->CreateAnimationSequence("PlayerBomb", "PlayerBomb", TEXT("Bomb/1.bmp"), TEXTURE_PATH);
	for (int i = 0; i < 4; ++i)
	{
		GetSceneResource()->AddAnimationFrame("PlayerBomb", 56.f * i, 0.f, 56.f, 54.f);
	}
	GetSceneResource()->SetColorKey("PlayerBomb", 255, 0, 255);

	GetSceneResource()->CreateAnimationSequence("ExplosionCenter", "ExplosionCenter", TEXT("Bomb/pop.bmp"), TEXTURE_PATH);
	for (int i = 0; i < 7; ++i)
	{
		GetSceneResource()->AddAnimationFrame("ExplosionCenter", 52.f * i, 0.f, 52.f, 52.f);
	}
	GetSceneResource()->SetColorKey("ExplosionCenter", 255, 0, 255);

	GetSceneResource()->CreateAnimationSequence("ExplosionDown1", "ExplosionDown1", TEXT("Wave/down1.bmp"), TEXTURE_PATH);
	for (int i = 0; i < 11; ++i)
	{
		GetSceneResource()->AddAnimationFrame("ExplosionDown1", 52.f * i, 0.f, 52.f, 52.f);
	}
	GetSceneResource()->SetColorKey("ExplosionDown1", 255, 0, 255);

	GetSceneResource()->CreateAnimationSequence("ExplosionUp1", "ExplosionUp1", TEXT("Wave/up1.bmp"), TEXTURE_PATH);
	for (int i = 0; i < 11; ++i)
	{
		GetSceneResource()->AddAnimationFrame("ExplosionUp1", 52.f * i, 0.f, 52.f, 52.f);
	}
	GetSceneResource()->SetColorKey("ExplosionUp1", 255, 0, 255);

	GetSceneResource()->CreateAnimationSequence("ExplosionLeft1", "ExplosionLeft1", TEXT("Wave/left1.bmp"), TEXTURE_PATH);
	for (int i = 0; i < 11; ++i)
	{
		GetSceneResource()->AddAnimationFrame("ExplosionLeft1", 52.f * i, 0.f, 52.f, 52.f);
	}
	GetSceneResource()->SetColorKey("ExplosionLeft1", 255, 0, 255);

	GetSceneResource()->CreateAnimationSequence("ExplosionRight1", "ExplosionRight1", TEXT("Wave/right1.bmp"), TEXTURE_PATH);
	for (int i = 0; i < 11; ++i)
	{
		GetSceneResource()->AddAnimationFrame("ExplosionRight1", 52.f * i, 0.f, 52.f, 52.f);
	}
	GetSceneResource()->SetColorKey("ExplosionRight1", 255, 0, 255);

	GetSceneResource()->CreateAnimationSequence("ExplosionDown2", "ExplosionDown2", TEXT("Wave/down2.bmp"), TEXTURE_PATH);
	for (int i = 0; i < 11; ++i)
	{
		GetSceneResource()->AddAnimationFrame("ExplosionDown2", 52.f * i, 0.f, 52.f, 52.f);
	}
	GetSceneResource()->SetColorKey("ExplosionDown2", 255, 0, 255);

	GetSceneResource()->CreateAnimationSequence("ExplosionUp2", "ExplosionUp2", TEXT("Wave/up2.bmp"), TEXTURE_PATH);
	for (int i = 0; i < 11; ++i)
	{
		GetSceneResource()->AddAnimationFrame("ExplosionUp2", 52.f * i, 0.f, 52.f, 52.f);
	}
	GetSceneResource()->SetColorKey("ExplosionUp2", 255, 0, 255);

	GetSceneResource()->CreateAnimationSequence("ExplosionLeft2", "ExplosionLeft2", TEXT("Wave/left2.bmp"), TEXTURE_PATH);
	for (int i = 0; i < 11; ++i)
	{
		GetSceneResource()->AddAnimationFrame("ExplosionLeft2", 52.f * i, 0.f, 52.f, 52.f);
	}
	GetSceneResource()->SetColorKey("ExplosionLeft2", 255, 0, 255);

	GetSceneResource()->CreateAnimationSequence("ExplosionRight2", "ExplosionRight2", TEXT("Wave/right2.bmp"), TEXTURE_PATH);
	for (int i = 0; i < 11; ++i)
	{
		GetSceneResource()->AddAnimationFrame("ExplosionRight2", 52.f * i, 0.f, 52.f, 52.f);
	}
	GetSceneResource()->SetColorKey("ExplosionRight2", 255, 0, 255);
//Monster
	GetSceneResource()->CreateAnimationSequence("GamgyulU", "GamgyulU", TEXT("Monster/Gamgyul.bmp"), TEXTURE_PATH);
	for (int i = 0; i < 2; ++i)
	{
		GetSceneResource()->AddAnimationFrame("GamgyulU", 50.f * i, 0.f, 50.f, 56.f);
	}
	GetSceneResource()->SetColorKey("GamgyulU", 255, 0, 255);

	GetSceneResource()->CreateAnimationSequence("GamgyulD", "GamgyulD", TEXT("Monster/Gamgyul.bmp"), TEXTURE_PATH);
	for (int i = 2; i < 4; ++i)
	{
		GetSceneResource()->AddAnimationFrame("GamgyulD", 50.f * i, 0.f, 50.f, 56.f);
	}
	GetSceneResource()->SetColorKey("GamgyulD", 255, 0, 255);

	GetSceneResource()->CreateAnimationSequence("GamgyulR", "GamgyulR", TEXT("Monster/Gamgyul.bmp"), TEXTURE_PATH);
	for (int i = 6; i < 8; ++i)
	{
		GetSceneResource()->AddAnimationFrame("GamgyulR", 50.f * i, 0.f, 50.f, 56.f);
	}
	GetSceneResource()->SetColorKey("GamgyulR", 255, 0, 255);

	GetSceneResource()->CreateAnimationSequence("GamgyulL", "GamgyulL", TEXT("Monster/Gamgyul.bmp"), TEXTURE_PATH);
	for (int i = 4; i < 6; ++i)
	{
		GetSceneResource()->AddAnimationFrame("GamgyulL", 50.f * i, 0.f, 50.f, 56.f);
	}
	GetSceneResource()->SetColorKey("GamgyulL", 255, 0, 255);

	GetSceneResource()->CreateAnimationSequence("GamgyulDie", "GamgyulDie", TEXT("Monster/Gamgyul.bmp"), TEXTURE_PATH);
	for (int i = 0; i < 4; ++i)
	{
		GetSceneResource()->AddAnimationFrame("GamgyulDie", 50.f * i,56.f, 50.f, 56.f);
	}
	GetSceneResource()->SetColorKey("GamgyulDie", 255, 0, 255);
//Boss
	GetSceneResource()->CreateAnimationSequence("SealU", "SealU", TEXT("Monster/boss_2.bmp"), TEXTURE_PATH);
	for (int i = 6; i < 8; ++i)
	{
		GetSceneResource()->AddAnimationFrame("SealU", 120.f * i, 0.f, 120.f, 120.f);
	}
	GetSceneResource()->SetColorKey("SealU", 255, 0, 255);

	GetSceneResource()->CreateAnimationSequence("SealD", "SealD", TEXT("Monster/boss_2.bmp"), TEXTURE_PATH);
	for (int i = 0; i < 2; ++i)
	{
		GetSceneResource()->AddAnimationFrame("SealD", 120.f * i, 0.f, 120.f, 120.f);
	}
	GetSceneResource()->SetColorKey("SealD", 255, 0, 255);

	GetSceneResource()->CreateAnimationSequence("SealR", "SealR", TEXT("Monster/boss_2.bmp"), TEXTURE_PATH);
	for (int i = 2; i < 4; ++i)
	{
		GetSceneResource()->AddAnimationFrame("SealR", 120.f * i, 0.f, 120.f, 120.f);
	}
	GetSceneResource()->SetColorKey("SealR", 255, 0, 255);

	GetSceneResource()->CreateAnimationSequence("SealL", "SealL", TEXT("Monster/boss_2.bmp"), TEXTURE_PATH);
	for (int i = 4; i < 6; ++i)
	{
		GetSceneResource()->AddAnimationFrame("SealL", 120.f * i, 0.f, 120.f, 120.f);
	}
	GetSceneResource()->SetColorKey("SealL", 255, 0, 255);

	GetSceneResource()->CreateAnimationSequence("SealDie", "SealDie", TEXT("Monster/boss_2.bmp"), TEXTURE_PATH);
	for (int i = 3; i < 8; ++i)
	{
		GetSceneResource()->AddAnimationFrame("SealDie", 120.f * i, 360.f, 120.f, 120.f);
	}
	GetSceneResource()->SetColorKey("SealDie", 255, 0, 255);

	GetSceneResource()->CreateAnimationSequence("SealCharge", "SealCharge", TEXT("Monster/boss_2.bmp"), TEXTURE_PATH);
	for (int i = 0; i < 2; ++i)
	{
		GetSceneResource()->AddAnimationFrame("SealCharge", 120.f * i, 360.f, 120.f, 120.f);
	}
	GetSceneResource()->SetColorKey("SealCharge", 255, 0, 255);

	GetSceneResource()->CreateAnimationSequence("SealStun", "SealStun", TEXT("Monster/boss_2.bmp"), TEXTURE_PATH);
	for (int i = 5; i < 7; ++i)
	{
		GetSceneResource()->AddAnimationFrame("SealStun", 120.f * i, 240.f, 120.f, 120.f);
	}
	GetSceneResource()->SetColorKey("SealStun", 255, 0, 255);

	GetSceneResource()->CreateAnimationSequence("SealUInvisible", "SealUInvisible", TEXT("Monster/boss_2.bmp"), TEXTURE_PATH);
	for (int i = 6; i < 8; ++i)
	{
		GetSceneResource()->AddAnimationFrame("SealUInvisible", 120.f * i, 120.f, 120.f, 120.f);
	}
	GetSceneResource()->SetColorKey("SealUInvisible", 255, 0, 255);

	GetSceneResource()->CreateAnimationSequence("SealDInvisible", "SealDInvisible", TEXT("Monster/boss_2.bmp"), TEXTURE_PATH);
	for (int i = 0; i < 2; ++i)
	{
		GetSceneResource()->AddAnimationFrame("SealDInvisible", 120.f * i, 120.f, 120.f, 120.f);
	}
	GetSceneResource()->SetColorKey("SealDInvisible", 255, 0, 255);

	GetSceneResource()->CreateAnimationSequence("SealRInvisible", "SealRInvisible", TEXT("Monster/boss_2.bmp"), TEXTURE_PATH);
	for (int i = 2; i < 4; ++i)
	{
		GetSceneResource()->AddAnimationFrame("SealRInvisible", 120.f * i, 120.f, 120.f, 120.f);
	}
	GetSceneResource()->SetColorKey("SealRInvisible", 255, 0, 255);

	GetSceneResource()->CreateAnimationSequence("SealLInvisible", "SealLInvisible", TEXT("Monster/boss_2.bmp"), TEXTURE_PATH);
	for (int i = 4; i < 6; ++i)
	{
		GetSceneResource()->AddAnimationFrame("SealLInvisible", 120.f * i, 120.f, 120.f, 120.f);
	}
	GetSceneResource()->SetColorKey("SealLInvisible", 255, 0, 255);

	GetSceneResource()->CreateAnimationSequence("SealCInvisible", "SealCInvisible", TEXT("Monster/boss_2.bmp"), TEXTURE_PATH);
	for (int i = 1; i < 3; ++i)
	{
		GetSceneResource()->AddAnimationFrame("SealCInvisible", 120.f * i, 360.f, 120.f, 120.f);
	}
	GetSceneResource()->SetColorKey("SealCInvisible", 255, 0, 255);

	GetSceneResource()->CreateAnimationSequence("SealSInvisible", "SealSInvisible", TEXT("Monster/boss_2.bmp"), TEXTURE_PATH);
	for (int i =6; i < 8; ++i)
	{
		GetSceneResource()->AddAnimationFrame("SealSInvisible", 120.f * i, 240.f, 120.f, 120.f);
	}
	GetSceneResource()->SetColorKey("SealSInvisible", 255, 0, 255);

	GetSceneResource()->CreateAnimationSequence("SealRumble", "SealRumble", TEXT("Monster/boss_2.bmp"), TEXTURE_PATH);
	for (int i = 0; i < 5; ++i)
	{
		GetSceneResource()->AddAnimationFrame("SealRumble", 120.f * i, 240.f, 120.f, 120.f);
	}
	GetSceneResource()->SetColorKey("SealRumble", 255, 0, 255);
//Item
	GetSceneResource()->CreateAnimationSequence("Item_potion", "Item_potion", TEXT("Item/potion.bmp"), TEXTURE_PATH);
	for (int i = 0; i < 2; ++i)
	{
		GetSceneResource()->AddAnimationFrame("Item_potion", 56.f * i, 0, 56.f, 70.f);
	}
	GetSceneResource()->SetColorKey("Item_potion", 255, 0, 255);

	GetSceneResource()->CreateAnimationSequence("Item_potionI", "Item_potionI", TEXT("Item/potion.bmp"), TEXTURE_PATH);
	for (int i = 1; i < 3; ++i)
	{
		GetSceneResource()->AddAnimationFrame("Item_potionI", 56.f * i, 0, 56.f, 70.f);
	}
	GetSceneResource()->SetColorKey("Item_potionI", 255, 0, 255);

	GetSceneResource()->CreateAnimationSequence("Item_potion_max", "Item_potion_max", TEXT("Item/potion_max.bmp"), TEXTURE_PATH);
	for (int i = 0; i < 2; ++i)
	{
		GetSceneResource()->AddAnimationFrame("Item_potion_max", 56.f * i, 0, 56.f, 70.f);
	}
	GetSceneResource()->SetColorKey("Item_potion_max", 255, 0, 255);

	GetSceneResource()->CreateAnimationSequence("Item_potion_maxI", "Item_potion_maxI", TEXT("Item/potion_max.bmp"), TEXTURE_PATH);
	for (int i = 1; i < 3; ++i)
	{
		GetSceneResource()->AddAnimationFrame("Item_potion_maxI", 56.f * i, 0, 56.f, 70.f);
	}
	GetSceneResource()->SetColorKey("Item_potion_maxI", 255, 0, 255);

	GetSceneResource()->CreateAnimationSequence("Item_ballon", "Item_ballon", TEXT("Item/ballon.bmp"), TEXTURE_PATH);
	for (int i = 0; i < 2; ++i)
	{
		GetSceneResource()->AddAnimationFrame("Item_ballon", 56.f * i, 0, 56.f, 70.f);
	}
	GetSceneResource()->SetColorKey("Item_ballon", 255, 0, 255);

	GetSceneResource()->CreateAnimationSequence("Item_ballonI", "Item_ballonI", TEXT("Item/ballon.bmp"), TEXTURE_PATH);
	for (int i = 1; i < 3; ++i)
	{
		GetSceneResource()->AddAnimationFrame("Item_ballonI", 56.f * i, 0, 56.f, 70.f);
	}
	GetSceneResource()->SetColorKey("Item_ballonI", 255, 0, 255);

	GetSceneResource()->CreateAnimationSequence("Item_skate", "Item_skate", TEXT("Item/skate.bmp"), TEXTURE_PATH);
	for (int i = 0; i < 2; ++i)
	{
		GetSceneResource()->AddAnimationFrame("Item_skate", 56.f * i, 0, 56.f, 70.f);
	}
	GetSceneResource()->SetColorKey("Item_skate", 255, 0, 255);

	GetSceneResource()->CreateAnimationSequence("Item_skateI", "Item_skateI", TEXT("Item/skate.bmp"), TEXTURE_PATH);
	for (int i = 1; i < 3; ++i)
	{
		GetSceneResource()->AddAnimationFrame("Item_skateI", 56.f * i, 0, 56.f, 70.f);
	}
	GetSceneResource()->SetColorKey("Item_skateI", 255, 0, 255);

	GetSceneResource()->CreateAnimationSequence("Item_needle", "Item_needle", TEXT("Item/needle.bmp"), TEXTURE_PATH);
	for (int i = 0; i < 2; ++i)
	{
		GetSceneResource()->AddAnimationFrame("Item_needle", 56.f * i, 0, 56.f, 70.f);
	}
	GetSceneResource()->SetColorKey("Item_needle", 255, 0, 255);

	GetSceneResource()->CreateAnimationSequence("Item_needleI", "Item_needleI", TEXT("Item/needle.bmp"), TEXTURE_PATH);
	for (int i = 1; i < 3; ++i)
	{
		GetSceneResource()->AddAnimationFrame("Item_needleI", 56.f * i, 0, 56.f, 70.f);
	}
	GetSceneResource()->SetColorKey("Item_needleI", 255, 0, 255);

	GetSceneResource()->CreateAnimationSequence("Item_shoes", "Item_shoes", TEXT("Item/shoes.bmp"), TEXTURE_PATH);
	for (int i = 0; i < 2; ++i)
	{
		GetSceneResource()->AddAnimationFrame("Item_shoes", 56.f * i, 0, 56.f, 70.f);
	}
	GetSceneResource()->SetColorKey("Item_shoes", 255, 0, 255);

	GetSceneResource()->CreateAnimationSequence("Item_dart", "Item_dart", TEXT("Item/dart.bmp"), TEXTURE_PATH);
	for (int i = 0; i < 2; ++i)
	{
		GetSceneResource()->AddAnimationFrame("Item_dart", 56.f * i, 0, 56.f, 70.f);
	}
	GetSceneResource()->SetColorKey("Item_dart", 255, 0, 255);
//effect
	GetSceneResource()->CreateAnimationSequence("Warning", "Warning", TEXT("Effect/warning.bmp"), TEXTURE_PATH);
	for (int i = 0; i < 2; ++i)
	{
		for (int j = 0; j < 8; ++j)
		{
			GetSceneResource()->AddAnimationFrame("Warning", 52.f * j, 52.f * i, 52.f, 52.f);
		}
	}
	GetSceneResource()->SetColorKey("Warning", 255, 0, 255);

	GetSceneResource()->CreateAnimationSequence("Marker", "Marker", TEXT("Effect/marker.bmp"), TEXTURE_PATH);
	for (int i = 0; i < 8; ++i)
	{
		GetSceneResource()->AddAnimationFrame("Marker", 30.f * i, 0.f, 30.f, 30.f);
	}
	GetSceneResource()->SetColorKey("Marker", 255, 0, 255);

	GetSceneResource()->CreateAnimationSequence("MarkerBreak", "MarkerBreak", TEXT("Effect/marker_break.bmp"), TEXTURE_PATH);
	for (int i = 0; i < 7; ++i)
	{
		GetSceneResource()->AddAnimationFrame("MarkerBreak", 30.f * i, 0.f, 30.f, 30.f);
	}
	GetSceneResource()->SetColorKey("MarkerBreak", 255, 0, 255);

	GetSceneResource()->CreateAnimationSequence("Exclamation_mark", "Exclamation_mark", TEXT("Effect/Exclamation_mark.bmp"), TEXTURE_PATH);
	for (int i = 0; i < 4; ++i)
	{
		GetSceneResource()->AddAnimationFrame("Exclamation_mark", 15.f * i, 0.f,15.f, 50.f);
	}
	GetSceneResource()->SetColorKey("Exclamation_mark", 255, 0, 255);
//Wall
	GetSceneResource()->CreateAnimationSequence("FactoryBlock", "FactoryBlock", TEXT("Map/block/map_factory_block.bmp"), TEXTURE_PATH);
	GetSceneResource()->AddAnimationFrame("FactoryBlock", 0.f, 0.f, 68.f, 67.f);
	GetSceneResource()->SetColorKey("FactoryBlock", 255, 0, 255);

	GetSceneResource()->CreateAnimationSequence("FactoryBlock_Pop", "FactoryBlock_Pop", TEXT("Map/block/map_factory_block_pop.bmp"), TEXTURE_PATH);
	for (int i = 0; i < 5; ++i)
	{
		GetSceneResource()->AddAnimationFrame("FactoryBlock_Pop", 68.f * i, 0.f, 68.f, 67.f);
	}
	GetSceneResource()->SetColorKey("FactoryBlock_Pop", 255, 0, 255);
}