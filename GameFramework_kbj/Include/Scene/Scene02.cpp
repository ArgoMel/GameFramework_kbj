#include "Scene02.h"
#include "SceneResource.h"
#include "Camera.h"
#include "../GameObject/Player.h"
#include "../GameObject/EmperorPenguin.h"
#include "../GameObject/BackObj.h"
#include "../GameObject/TileMap.h"
#include "../GameObject/Tile.h"
#include "../Widget/CharacterHUD.h"
#include "../Widget/ItemHUD.h"
#include "../Widget/GameStart.h"

CScene02::CScene02()
{
}

CScene02::~CScene02()
{
}

bool CScene02::Init()
{
	SetName("CScene02");

	CreateAnimationSequence();
	GetSceneResource()->LoadSound("BGM", "stage02", true, "bg_13.ogg");
	GetSceneResource()->LoadSound("Effect", "EnemySummon", false, "ef_0.ogg");
	GetSceneResource()->LoadSound("Effect", "EnemySummonError", false, "Error.mp3");
	GetSceneResource()->LoadSound("Effect", "EnemyDie", false, "enemy_die.ogg");
	GetSceneResource()->LoadSound("Effect", "BossDie", false, "boss_dead.ogg");
	GetSceneResource()->LoadSound("Effect", "BossStun", false, "Stun.wav");
	GetSceneResource()->LoadSound("Effect", "PenguinHit", false, "PenguinHit.wav");
	GetSceneResource()->LoadSound("Effect", "Freeze", false, "Freeze.mp3");
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
	GetSceneResource()->SoundPlay("stage02");
	GetSceneResource()->SetVolume(20);

	CreateObject<CBackObj>("BackObj");
	CTileMap* tileMap = CreateObject<CTileMap>("TileMap");
	tileMap->LoadFileName("scene02.tmp", MAP_PATH);
	tileMap->SetPos(199.f, -30.f);

	SetWallCount(0);

	CPlayer* player = CreateObject<CPlayer>("Player");
	SetPlayer(player);
	CreateObject<CEmperorPenguin>("Penguin");

	GetCamera()->SetResolution(1280.f, 720.f);
	GetCamera()->SetWorldResolution(1280.f, 720.f);
	GetCamera()->SetTargetPivot(0.5f, 0.5f);
	GetCamera()->SetTarget(player);

	CreateWidgetWindow<CCharacterHUD>("CharacterHUD");
	CreateWidgetWindow<CItemHUD>("ItemHUD");
	CreateWidgetWindow<CGameStart>("GameStart");
	return true;
}

void CScene02::CreateAnimationSequence()
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
	GetSceneResource()->CreateAnimationSequence("SnowMonU", "SnowMonU", TEXT("Monster/SnowMon.bmp"), TEXTURE_PATH);
	for (int i = 0; i < 2; ++i)
	{
		GetSceneResource()->AddAnimationFrame("SnowMonU", 80.f * i, 0.f, 80.f, 80.f);
	}
	GetSceneResource()->SetColorKey("SnowMonU", 255, 0, 255);

	GetSceneResource()->CreateAnimationSequence("SnowMonD", "SnowMonD", TEXT("Monster/SnowMon.bmp"), TEXTURE_PATH);
	for (int i = 2; i < 4; ++i)
	{
		GetSceneResource()->AddAnimationFrame("SnowMonD", 80.f * i, 0.f, 80.f, 80.f);
	}
	GetSceneResource()->SetColorKey("SnowMonD", 255, 0, 255);

	GetSceneResource()->CreateAnimationSequence("SnowMonR", "SnowMonR", TEXT("Monster/SnowMon.bmp"), TEXTURE_PATH);
	for (int i = 4; i < 6; ++i)
	{
		GetSceneResource()->AddAnimationFrame("SnowMonR", 80.f * i, 0.f, 80.f, 80.f);
	}
	GetSceneResource()->SetColorKey("SnowMonR", 255, 0, 255);

	GetSceneResource()->CreateAnimationSequence("SnowMonL", "SnowMonL", TEXT("Monster/SnowMon.bmp"), TEXTURE_PATH);
	for (int i = 6; i < 8; ++i)
	{
		GetSceneResource()->AddAnimationFrame("SnowMonL", 80.f * i, 0.f, 80.f, 80.f);
	}
	GetSceneResource()->SetColorKey("SnowMonL", 255, 0, 255);

	GetSceneResource()->CreateAnimationSequence("SnowMonDie", "SnowMonDie", TEXT("Monster/SnowMon.bmp"), TEXTURE_PATH);
	for (int i = 8; i < 14; ++i)
	{
		GetSceneResource()->AddAnimationFrame("SnowMonDie", 80.f * i, 0.f, 80.f, 80.f);
	}
	GetSceneResource()->SetColorKey("SnowMonDie", 255, 0, 255);
	//Boss
	GetSceneResource()->CreateAnimationSequence("PenguinU", "PenguinU", TEXT("Monster/boss_3.bmp"), TEXTURE_PATH);
	for (int i = 0; i < 2; ++i)
	{
		GetSceneResource()->AddAnimationFrame("PenguinU", 110.f * i, 0.f, 110.f, 110.f);
	}
	GetSceneResource()->SetColorKey("PenguinU", 255, 0, 255);

	GetSceneResource()->CreateAnimationSequence("PenguinD", "PenguinD", TEXT("Monster/boss_3.bmp"), TEXTURE_PATH);
	for (int i = 2; i < 4; ++i)
	{
		GetSceneResource()->AddAnimationFrame("PenguinD", 110.f * i, 0.f, 110.f, 110.f);
	}
	GetSceneResource()->SetColorKey("PenguinD", 255, 0, 255);

	GetSceneResource()->CreateAnimationSequence("PenguinR", "PenguinR", TEXT("Monster/boss_3.bmp"), TEXTURE_PATH);
	for (int i = 4; i < 6; ++i)
	{
		GetSceneResource()->AddAnimationFrame("PenguinR", 110.f * i, 0.f, 110.f, 110.f);
	}
	GetSceneResource()->SetColorKey("PenguinR", 255, 0, 255);

	GetSceneResource()->CreateAnimationSequence("PenguinL", "PenguinL", TEXT("Monster/boss_3.bmp"), TEXTURE_PATH);
	for (int i = 6; i < 8; ++i)
	{
		GetSceneResource()->AddAnimationFrame("PenguinL", 110.f * i, 0.f, 110.f, 110.f);
	}
	GetSceneResource()->SetColorKey("PenguinL", 255, 0, 255);

	GetSceneResource()->CreateAnimationSequence("PenguinDie", "PenguinDie", TEXT("Monster/boss_3.bmp"), TEXTURE_PATH);
	for (int i = 0; i < 5; ++i)
	{
		GetSceneResource()->AddAnimationFrame("PenguinDie", 110.f * i, 220.f, 110.f, 110.f);
	}
	GetSceneResource()->SetColorKey("PenguinDie", 255, 0, 255);

	GetSceneResource()->CreateAnimationSequence("PenguinCharge", "PenguinCharge", TEXT("Monster/boss_3.bmp"), TEXTURE_PATH);
	for (int i = 8; i < 10; ++i)
	{
		GetSceneResource()->AddAnimationFrame("PenguinCharge", 110.f * i, 110.f, 110.f, 110.f);
	}
	GetSceneResource()->SetColorKey("PenguinCharge", 255, 0, 255);

	GetSceneResource()->CreateAnimationSequence("PenguinStun", "PenguinStun", TEXT("Monster/boss_3.bmp"), TEXTURE_PATH);
	for (int i = 8; i < 10; ++i)
	{
		GetSceneResource()->AddAnimationFrame("PenguinStun", 110.f * i, 0.f, 110.f, 110.f);
	}
	GetSceneResource()->SetColorKey("PenguinStun", 255, 0, 255);

	GetSceneResource()->CreateAnimationSequence("PenguinUInvisible", "PenguinUInvisible", TEXT("Monster/boss_3.bmp"), TEXTURE_PATH);
	for (int i = 0; i < 2; ++i)
	{
		GetSceneResource()->AddAnimationFrame("PenguinUInvisible", 110.f * i, 110.f, 110.f, 110.f);
	}
	GetSceneResource()->SetColorKey("PenguinUInvisible", 255, 0, 255);

	GetSceneResource()->CreateAnimationSequence("PenguinDInvisible", "PenguinDInvisible", TEXT("Monster/boss_3.bmp"), TEXTURE_PATH);
	for (int i = 2; i < 4; ++i)
	{
		GetSceneResource()->AddAnimationFrame("PenguinDInvisible", 110.f * i, 110.f, 110.f, 110.f);
	}
	GetSceneResource()->SetColorKey("PenguinDInvisible", 255, 0, 255);

	GetSceneResource()->CreateAnimationSequence("PenguinRInvisible", "PenguinRInvisible", TEXT("Monster/boss_3.bmp"), TEXTURE_PATH);
	for (int i = 4; i < 6; ++i)
	{
		GetSceneResource()->AddAnimationFrame("PenguinRInvisible", 110.f * i, 110.f, 110.f, 110.f);
	}
	GetSceneResource()->SetColorKey("PenguinRInvisible", 255, 0, 255);

	GetSceneResource()->CreateAnimationSequence("PenguinLInvisible", "PenguinLInvisible", TEXT("Monster/boss_3.bmp"), TEXTURE_PATH);
	for (int i = 6; i < 8; ++i)
	{
		GetSceneResource()->AddAnimationFrame("PenguinLInvisible", 110.f * i, 110.f, 110.f, 110.f);
	}
	GetSceneResource()->SetColorKey("PenguinLInvisible", 255, 0, 255);

	GetSceneResource()->CreateAnimationSequence("PenguinCInvisible", "PenguinCInvisible", TEXT("Monster/boss_3.bmp"), TEXTURE_PATH);
	for (int i = 9; i < 11; ++i)
	{
		GetSceneResource()->AddAnimationFrame("PenguinCInvisible", 110.f * i, 110.f, 110.f, 110.f);
	}
	GetSceneResource()->SetColorKey("PenguinCInvisible", 255, 0, 255);

	GetSceneResource()->CreateAnimationSequence("PenguinSInvisible", "PenguinSInvisible", TEXT("Monster/boss_3.bmp"), TEXTURE_PATH);
	for (int i = 9; i < 11; ++i)
	{
		GetSceneResource()->AddAnimationFrame("PenguinSInvisible", 110.f * i, 0.f, 110.f, 110.f);
	}
	GetSceneResource()->SetColorKey("PenguinSInvisible", 255, 0, 255);
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

	GetSceneResource()->CreateAnimationSequence("Item_treasure", "Item_treasure", TEXT("Item/treasure.bmp"), TEXTURE_PATH);
	for (int i = 0; i < 2; ++i)
	{
		GetSceneResource()->AddAnimationFrame("Item_treasure", 56.f * i, 0, 56.f, 70.f);
	}
	GetSceneResource()->SetColorKey("Item_treasure", 255, 0, 255);
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
}