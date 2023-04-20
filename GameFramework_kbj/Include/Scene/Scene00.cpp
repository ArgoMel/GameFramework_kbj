#include "Scene00.h"
#include "SceneResource.h"
#include "Camera.h"
#include "../GameObject/Player.h"
#include "../GameObject/Boss.h"
#include "../GameObject/Wall.h"
#include "../GameObject/BackObj.h"
#include "../GameObject/TileMap.h"
#include "../GameObject/Tile.h"
#include "../Widget/CharacterHUD.h"
#include "../Widget/ItemHUD.h"
#include "../Widget/GameStart.h"

CScene00::CScene00()
{
}

CScene00::~CScene00()
{
}

bool CScene00::Init()
{
	SetName("CScene00");

    CreateAnimationSequence();
	GetSceneResource()->LoadSound("BGM", "stage00", true, "bg_11.ogg");
	GetSceneResource()->LoadSound("Effect", "EnemySummon", false, "ef_0.ogg");
	GetSceneResource()->LoadSound("Effect", "EnemySummonError", false, "Error.mp3");
	GetSceneResource()->LoadSound("Effect", "EnemyDie", false, "enemy_die.ogg");
	GetSceneResource()->LoadSound("Effect", "BossDie", false, "boss_dead.ogg");
	GetSceneResource()->LoadSound("Effect", "BossFire", false, "Fire1.wav");
	GetSceneResource()->LoadSound("Effect", "BossStun", false, "Stun.wav");
	GetSceneResource()->LoadSound("Effect", "BossHit", false, "OctopusHit.ogg");
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
	GetSceneResource()->SoundPlay("stage00");
	GetSceneResource()->SetVolume(20);

	CreateObject<CBackObj>("BackObj");
	CTileMap* tileMap = CreateObject<CTileMap>("TileMap");
	tileMap->LoadFileName("scene00.tmp", MAP_PATH);
	tileMap->SetPos(199.f, -30.f);
	CWall* wall = CreateObject<CWall>("Wall1");
	wall->SetPos(START_TILE.x + TILE.x*1, START_TILE.y + TILE.y *1);
	wall = CreateObject<CWall>("Wall2");
	wall->SetPos(START_TILE.x + TILE.x*1, START_TILE.y + TILE.y *3);
	wall = CreateObject<CWall>("Wall3");
	wall->SetPos(START_TILE.x + TILE.x * 1, START_TILE.y + TILE.y * 5);
	wall = CreateObject<CWall>("Wall4");
	wall->SetPos(START_TILE.x + TILE.x * 1, START_TILE.y + TILE.y * 7);
	wall = CreateObject<CWall>("Wall5");
	wall->SetPos(START_TILE.x + TILE.x * 1, START_TILE.y + TILE.y * 9);
	wall = CreateObject<CWall>("Wall6");
	wall->SetPos(START_TILE.x + TILE.x * 1, START_TILE.y + TILE.y * 11);
	wall = CreateObject<CWall>("Wall7");
	wall->SetPos(START_TILE.x + TILE.x * 13, START_TILE.y + TILE.y * 1);
	wall = CreateObject<CWall>("Wall8");
	wall->SetPos(START_TILE.x + TILE.x * 13, START_TILE.y + TILE.y * 3);
	wall = CreateObject<CWall>("Wall9");
	wall->SetPos(START_TILE.x + TILE.x * 13, START_TILE.y + TILE.y * 5);
	wall = CreateObject<CWall>("Wall10");
	wall->SetPos(START_TILE.x + TILE.x * 13, START_TILE.y + TILE.y * 7);
	wall = CreateObject<CWall>("Wall11");
	wall->SetPos(START_TILE.x + TILE.x * 13, START_TILE.y + TILE.y * 9);
	wall = CreateObject<CWall>("Wall12");
	wall->SetPos(START_TILE.x + TILE.x * 13, START_TILE.y + TILE.y * 11);
	SetWallCount(12);
    CPlayer* player=CreateObject<CPlayer>("Player");
    SetPlayer(player);
	CreateObject<CBoss>("Boss");

	GetCamera()->SetResolution(1280.f, 720.f);
	GetCamera()->SetWorldResolution(1280.f, 720.f);
	GetCamera()->SetTargetPivot(0.5f, 0.5f);
	GetCamera()->SetTarget(player);

	CreateWidgetWindow<CCharacterHUD>("CharacterHUD");
	CreateWidgetWindow<CItemHUD>("ItemHUD");
	CreateWidgetWindow<CGameStart>("GameStart");
    return true;
}

void CScene00::CreateAnimationSequence()
{
//player
	GetSceneResource()->CreateAnimationSequence("PlayerStart", "PlayerStart", TEXT("Player/ready.bmp"), TEXTURE_PATH);
	for (int i = 0; i < 18; ++i)
	{
		GetSceneResource()->AddAnimationFrame("PlayerStart", 64.f * i, 0.f, 64.f, 86.f);
	}
	GetSceneResource()->SetColorKey("PlayerStart", 255, 0, 255);

	GetSceneResource()->CreateAnimationSequence("PlayerIdle", "PlayerIdle", TEXT("Player/wait.bmp"), TEXTURE_PATH);
	for (int i = 0; i < 3; ++i)
	{
		GetSceneResource()->AddAnimationFrame("PlayerIdle", 64.f * i, 0.f, 64.f, 76.f);
	}
	GetSceneResource()->SetColorKey("PlayerIdle", 255, 0, 255);

	GetSceneResource()->CreateAnimationSequence("PlayerUp", "PlayerUp", TEXT("Player/up.bmp"), TEXTURE_PATH);
	for (int i = 0; i < 8; ++i)
	{
		GetSceneResource()->AddAnimationFrame("PlayerUp", 64.f * i, 0.f, 64.f, 76.f);
	}
	GetSceneResource()->SetColorKey("PlayerUp", 255, 0, 255);

	GetSceneResource()->CreateAnimationSequence("PlayerDown","PlayerDown", TEXT("Player/down.bmp"), TEXTURE_PATH);
	for (int i = 0; i < 8; ++i)
	{
		GetSceneResource()->AddAnimationFrame("PlayerDown", 64.f * i, 0.f, 64.f, 76.f);
	}
	GetSceneResource()->SetColorKey("PlayerDown", 255, 0, 255);

	GetSceneResource()->CreateAnimationSequence("PlayerLeft", "PlayerLeft", TEXT("Player/left.bmp"), TEXTURE_PATH);
	for (int i = 0; i < 6; ++i)
	{
		GetSceneResource()->AddAnimationFrame("PlayerLeft", 64.f * i, 0.f, 64.f, 76.f);
	}
	GetSceneResource()->SetColorKey("PlayerLeft", 255, 0, 255);

	GetSceneResource()->CreateAnimationSequence("PlayerRight", "PlayerRight", TEXT("Player/right.bmp"), TEXTURE_PATH);
	for (int i = 0; i < 6; ++i)
	{
		GetSceneResource()->AddAnimationFrame("PlayerRight", 64.f * i, 0.f, 64.f, 76.f);
	}
	GetSceneResource()->SetColorKey("PlayerRight", 255, 0, 255);

	GetSceneResource()->CreateAnimationSequence("PlayerBubble", "PlayerBubble", TEXT("Player/trap.bmp"), TEXTURE_PATH);
	for (int i = 0; i < 13; ++i)
	{
		GetSceneResource()->AddAnimationFrame("PlayerBubble", 88.f * i, 0.f, 88.f, 144.f);
	}
	GetSceneResource()->SetColorKey("PlayerBubble", 255, 0, 255);

	GetSceneResource()->CreateAnimationSequence("PlayerDie", "PlayerDie", TEXT("Player/die.bmp"), TEXTURE_PATH);
	for (int i = 1; i < 13; ++i)
	{
		GetSceneResource()->AddAnimationFrame("PlayerDie", 88.f * i, 0.f, 88.f, 144.f);
	}
	GetSceneResource()->SetColorKey("PlayerDie", 255, 0, 255);

	GetSceneResource()->CreateAnimationSequence("PlayerEscape", "PlayerEscape", TEXT("Player/live.bmp"), TEXTURE_PATH);
	for (int i = 0; i < 5; ++i)
	{
		GetSceneResource()->AddAnimationFrame("PlayerEscape", 88.f * i, 0.f, 88.f, 144.f);
	}
	GetSceneResource()->SetColorKey("PlayerEscape", 255, 0, 255);

	GetSceneResource()->CreateAnimationSequence("PlayerInvisibleD", "PlayerInvisibleD", TEXT("Player/flash_shortD.bmp"), TEXTURE_PATH);
	for (int i = 0; i < 2; ++i)
	{
		GetSceneResource()->AddAnimationFrame("PlayerInvisibleD", 64.f * i, 0.f, 64.f, 76.f);
	}
	GetSceneResource()->SetColorKey("PlayerInvisibleD", 255, 0, 255);

	GetSceneResource()->CreateAnimationSequence("PlayerInvisibleU", "PlayerInvisibleU", TEXT("Player/flash_shortU.bmp"), TEXTURE_PATH);
	for (int i = 0; i < 2; ++i)
	{
		GetSceneResource()->AddAnimationFrame("PlayerInvisibleU", 64.f * i, 0.f, 64.f, 76.f);
	}
	GetSceneResource()->SetColorKey("PlayerInvisibleU", 255, 0, 255);

	GetSceneResource()->CreateAnimationSequence("PlayerInvisibleL", "PlayerInvisibleL", TEXT("Player/flash_shortL.bmp"), TEXTURE_PATH);
	for (int i = 0; i < 2; ++i)
	{
		GetSceneResource()->AddAnimationFrame("PlayerInvisibleL", 64.f * i, 0.f, 64.f, 76.f);
	}
	GetSceneResource()->SetColorKey("PlayerInvisibleL", 255, 0, 255);

	GetSceneResource()->CreateAnimationSequence("PlayerInvisibleR", "PlayerInvisibleR", TEXT("Player/flash_shortR.bmp"), TEXTURE_PATH);
	for (int i = 0; i < 2; ++i)
	{
		GetSceneResource()->AddAnimationFrame("PlayerInvisibleR", 64.f * i, 0.f, 64.f, 76.f);
	}
	GetSceneResource()->SetColorKey("PlayerInvisibleR", 255, 0, 255);
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
	GetSceneResource()->CreateAnimationSequence("Monster1_1Right", "Monster1_1Right", TEXT("Monster/unit_monster03.bmp"), TEXTURE_PATH);
	for (int i = 6; i < 8; ++i)
	{
		GetSceneResource()->AddAnimationFrame("Monster1_1Right", 50.f * i, 0.f, 50.f, 56.f);
	}
	GetSceneResource()->SetColorKey("Monster1_1Right", 255, 0, 255);

	GetSceneResource()->CreateAnimationSequence("Monster1_1Left", "Monster1_1Left", TEXT("Monster/unit_monster03.bmp"), TEXTURE_PATH);
	for (int i = 4; i < 6; ++i)
	{
		GetSceneResource()->AddAnimationFrame("Monster1_1Left", 50.f * i, 0.f, 50.f, 56.f);
	}
	GetSceneResource()->SetColorKey("Monster1_1Left", 255, 0, 255);

	GetSceneResource()->CreateAnimationSequence("Monster1_1Die", "Monster1_1Die", TEXT("Monster/unit_monster03.bmp"), TEXTURE_PATH);
	for (int i = 8; i < 12; ++i)
	{
		GetSceneResource()->AddAnimationFrame("Monster1_1Die", 50.f * i,0.f, 50.f, 56.f);
	}
	GetSceneResource()->SetColorKey("Monster1_1Die", 255, 0, 255);
//Boss
	GetSceneResource()->CreateAnimationSequence("Boss_Up", "Boss_Up", TEXT("Monster/boss_1.bmp"), TEXTURE_PATH);
	for (int i = 0; i < 2; ++i)
	{
		GetSceneResource()->AddAnimationFrame("Boss_Up", 84.f * i, 246.f, 84.f, 123.f);
	}
	GetSceneResource()->SetColorKey("Boss_Up", 255, 0, 255);

	GetSceneResource()->CreateAnimationSequence("Boss_Down", "Boss_Down", TEXT("Monster/boss_1.bmp"), TEXTURE_PATH);
	for (int i = 2; i < 4; ++i)
	{
		GetSceneResource()->AddAnimationFrame("Boss_Down", 84.f * i, 246.f, 84.f, 123.f);
	}
	GetSceneResource()->SetColorKey("Boss_Down", 255, 0, 255);

	GetSceneResource()->CreateAnimationSequence("Boss_Right", "Boss_Right", TEXT("Monster/boss_1.bmp"), TEXTURE_PATH);
	for (int i = 4; i < 6; ++i)
	{
		GetSceneResource()->AddAnimationFrame("Boss_Right", 84.f * i, 246.f, 84.f, 123.f);
	}
	GetSceneResource()->SetColorKey("Boss_Right", 255, 0, 255);

	GetSceneResource()->CreateAnimationSequence("Boss_Left", "Boss_Left", TEXT("Monster/boss_1.bmp"), TEXTURE_PATH);
	for (int i = 6; i < 8; ++i)
	{
		GetSceneResource()->AddAnimationFrame("Boss_Left", 84.f * i, 246.f, 84.f, 123.f);
	}
	GetSceneResource()->SetColorKey("Boss_Left", 255, 0, 255);

	GetSceneResource()->CreateAnimationSequence("Boss_Die", "Boss_Die", TEXT("Monster/boss_1.bmp"), TEXTURE_PATH);
	for (int i = 4; i < 10; ++i)
	{
		GetSceneResource()->AddAnimationFrame("Boss_Die", 84.f * i, 0, 84.f, 123.f);
	}
	GetSceneResource()->SetColorKey("Boss_Die", 255, 0, 255);

	GetSceneResource()->CreateAnimationSequence("Boss_Charge", "Boss_Charge", TEXT("Monster/boss_1.bmp"), TEXTURE_PATH);
	for (int i = 8; i < 10; ++i)
	{
		GetSceneResource()->AddAnimationFrame("Boss_Charge", 84.f * i, 123.f, 84.f, 123.f);
	}
	GetSceneResource()->SetColorKey("Boss_Charge", 255, 0, 255);

	GetSceneResource()->CreateAnimationSequence("Boss_Stun", "Boss_Stun", TEXT("Monster/boss_1.bmp"), TEXTURE_PATH);
	for (int i = 8; i < 10; ++i)
	{
		GetSceneResource()->AddAnimationFrame("Boss_Stun", 84.f * i, 246.f, 84.f, 123.f);
	}
	GetSceneResource()->SetColorKey("Boss_Stun", 255, 0, 255);

	GetSceneResource()->CreateAnimationSequence("Boss_InvisibleU", "Boss_InvisibleU", TEXT("Monster/boss_1.bmp"), TEXTURE_PATH);
	for (int i = 0; i < 2; ++i)
	{
		GetSceneResource()->AddAnimationFrame("Boss_InvisibleU", 84.f * i, 123.f, 84.f, 123.f);
	}
	GetSceneResource()->SetColorKey("Boss_InvisibleU", 255, 0, 255);

	GetSceneResource()->CreateAnimationSequence("Boss_InvisibleD", "Boss_InvisibleD", TEXT("Monster/boss_1.bmp"), TEXTURE_PATH);
	for (int i = 2; i < 4; ++i)
	{
		GetSceneResource()->AddAnimationFrame("Boss_InvisibleD", 84.f * i, 123.f, 84.f, 123.f);
	}
	GetSceneResource()->SetColorKey("Boss_InvisibleD", 255, 0, 255);

	GetSceneResource()->CreateAnimationSequence("Boss_InvisibleR", "Boss_InvisibleR", TEXT("Monster/boss_1.bmp"), TEXTURE_PATH);
	for (int i = 4; i < 6; ++i)
	{
		GetSceneResource()->AddAnimationFrame("Boss_InvisibleR", 84.f * i, 123.f, 84.f, 123.f);
	}
	GetSceneResource()->SetColorKey("Boss_InvisibleR", 255, 0, 255);

	GetSceneResource()->CreateAnimationSequence("Boss_InvisibleL", "Boss_InvisibleL", TEXT("Monster/boss_1.bmp"), TEXTURE_PATH);
	for (int i = 6; i < 8; ++i)
	{
		GetSceneResource()->AddAnimationFrame("Boss_InvisibleL", 84.f * i, 123.f, 84.f, 123.f);
	}
	GetSceneResource()->SetColorKey("Boss_InvisibleL", 255, 0, 255);

	GetSceneResource()->CreateAnimationSequence("Boss_InvisibleC", "Boss_InvisibleC", TEXT("Monster/boss_1.bmp"), TEXTURE_PATH);
	for (int i = 0; i < 2; ++i)
	{
		GetSceneResource()->AddAnimationFrame("Boss_InvisibleC", 84.f * i, 369.f, 84.f, 123.f);
	}
	GetSceneResource()->SetColorKey("Boss_InvisibleC", 255, 0, 255);

	GetSceneResource()->CreateAnimationSequence("Boss_InvisibleS", "Boss_InvisibleS", TEXT("Monster/boss_1.bmp"), TEXTURE_PATH);
	for (int i = 2; i < 4; ++i)
	{
		GetSceneResource()->AddAnimationFrame("Boss_InvisibleS", 84.f * i, 369.f, 84.f, 123.f);
	}
	GetSceneResource()->SetColorKey("Boss_InvisibleS", 255, 0, 255);

	GetSceneResource()->CreateAnimationSequence("BossExplosion", "BossExplosion", TEXT("Wave/explosion.bmp"), TEXTURE_PATH);
	for (int i = 0; i < 13; ++i)
	{
		GetSceneResource()->AddAnimationFrame("BossExplosion", 0.f, 144.f*i, 96.f, 144.f);
	}
	GetSceneResource()->SetColorKey("BossExplosion", 255, 0, 255);
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
			GetSceneResource()->AddAnimationFrame("Warning", 52.f * j, 52.f*i, 52.f, 52.f);
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
	//Wall
	GetSceneResource()->CreateAnimationSequence("Block2", "Block2", TEXT("Map/block/block_2.bmp"), TEXTURE_PATH);
	GetSceneResource()->AddAnimationFrame("Block2", 0.f, 0.f, 68.f, 67.f);
	GetSceneResource()->SetColorKey("Block2", 255, 0, 255);

	GetSceneResource()->CreateAnimationSequence("Block2_Pop", "Block2_Pop", TEXT("Map/block/block_2_pop.bmp"), TEXTURE_PATH);
	for (int i = 0; i < 5; ++i)
	{
		GetSceneResource()->AddAnimationFrame("Block2_Pop", 68.f * i, 0.f, 68.f, 67.f);
	}
	GetSceneResource()->SetColorKey("Block2_Pop", 255, 0, 255);
}
