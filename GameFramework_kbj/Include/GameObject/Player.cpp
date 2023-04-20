#include "Player.h"
#include "Bomb.h"
#include "Bullet.h"
#include "Wall.h"
#include "UIObject.h"
#include "TileMap.h"
#include "Tile.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"
#include "../Scene/Camera.h"
#include "../Input.h"
#include "../GameManager.h"
#include "../Collision/ColliderBox.h"
#include "../Widget/GameOver.h"
#include "../Widget/GameWin.h"
#include "../Widget/GamePause.h"
#include "../Widget/ItemHUD.h"
#include "../Widget/Button.h"

CPlayer::CPlayer()
    : m_playerDir(1)
    , m_bombCount(1)
    , m_bombPower(1)
    , m_speedCount(1)
    , m_maxCount(8)
    , m_KeyCount(0)
    , m_canHorizon(true)
    , m_canVertical(true)
    , m_HaveNeedle(true)
    , m_HaveDart(false)
    , m_IsCheat(false)
    , m_CoolTime(2.f)
    , m_InvisibleTime(0.f)
{
    SetTypeID<CPlayer>();
    m_ColliderSize = Vector2(50.f, 50.f);
    //m_OffsetSize = Vector2(0.f, 8.f);
}

CPlayer::CPlayer(const CPlayer& obj)
    :CCharacter(obj)
    , m_playerDir(1)
    , m_bombCount(obj.m_bombCount)
    , m_bombPower(obj.m_bombPower)
    , m_speedCount(obj.m_speedCount)
    , m_maxCount(9)
    , m_KeyCount(0)
    , m_canHorizon(true)
    , m_canVertical(true)
    , m_HaveNeedle(obj.m_HaveNeedle)
    , m_HaveDart(obj.m_HaveDart)
    , m_IsCheat(obj.m_IsCheat)
    , m_CoolTime(2.f)
    , m_InvisibleTime(2.f)
{
}

CPlayer::~CPlayer()
{
}

bool CPlayer::Init()
{
    CGameObject::Init();
    SetSpeed();
    SetPos(START_TILE.x, START_TILE.y + TILE.y * 12);
    SetPivot(0.5f, 0.5f);

    CreateAnimation();
    AddAnimation("PlayerStart", false);
    AddAnimation("PlayerIdle");
    AddAnimation("PlayerUp");
    AddAnimation("PlayerDown");
    AddAnimation("PlayerLeft");
    AddAnimation("PlayerRight");
    AddAnimation("PlayerBubble", false, 3.0f);
    AddAnimation("PlayerDie", false);
    AddAnimation("PlayerEscape", false,0.4f);
    AddAnimation("PlayerInvisibleD",true,0.1f);
    AddAnimation("PlayerInvisibleU",true,0.1f);
    AddAnimation("PlayerInvisibleL",true,0.1f);
    AddAnimation("PlayerInvisibleR",true,0.1f);

    SetEndFunction<CPlayer>("PlayerStart", this, &CPlayer::Idle);
    SetEndFunction<CPlayer>("PlayerBubble", this, &CPlayer::Die);
    SetEndFunction<CPlayer>("PlayerEscape", this, &CPlayer::Idle);
    AddNotify<CPlayer>("PlayerDie", 7, this, &CPlayer::Result);

    m_vecSequenceKey[0].push_back("PlayerUp");
    m_vecSequenceKey[0].push_back("PlayerInvisibleU");
    m_vecSequenceKey[1].push_back("PlayerDown");
    m_vecSequenceKey[1].push_back("PlayerInvisibleD");
    m_vecSequenceKey[2].push_back("PlayerLeft");
    m_vecSequenceKey[2].push_back("PlayerInvisibleL");
    m_vecSequenceKey[3].push_back("PlayerRight");
    m_vecSequenceKey[3].push_back("PlayerInvisibleR");
    // 충돌체 추가
    box = AddCollider<CColliderBox>("Player");
    box->SetExtent(m_ColliderSize.x, m_ColliderSize.y);
    box->SetOffset(m_OffsetSize);
    box->SetCollisionProfile("Player");
    box->SetCollisionBeginFunction<CPlayer>(this, &CPlayer::CollisionBegin);
    box->SetCollisionEndFunction<CPlayer>(this, &CPlayer::CollisionEnd);

    CInput::GetInst()->AddBindFunction<CPlayer>("MoveUp", Input_Type::DOWN, this, &CPlayer::NoHorizontal,m_scene);
    CInput::GetInst()->AddBindFunction<CPlayer>("MoveDown", Input_Type::DOWN, this, &CPlayer::NoHorizontal, m_scene);
    CInput::GetInst()->AddBindFunction<CPlayer>("MoveLeft", Input_Type::DOWN, this, &CPlayer::NoVertical, m_scene);
    CInput::GetInst()->AddBindFunction<CPlayer>("MoveRight", Input_Type::DOWN, this, &CPlayer::NoVertical, m_scene);
    CInput::GetInst()->AddBindFunction<CPlayer>("MoveUp",Input_Type::STAY, this, &CPlayer::MoveUp, m_scene);
    CInput::GetInst()->AddBindFunction<CPlayer>("MoveDown", Input_Type::STAY, this, &CPlayer::MoveDown, m_scene);
    CInput::GetInst()->AddBindFunction<CPlayer>("MoveLeft",Input_Type::STAY, this, &CPlayer::MoveLeft, m_scene);
    CInput::GetInst()->AddBindFunction<CPlayer>("MoveRight",Input_Type::STAY, this, &CPlayer::MoveRight, m_scene);
    CInput::GetInst()->AddBindFunction<CPlayer>("MoveUp", Input_Type::UP, this, &CPlayer::YesHorizontal, m_scene);
    CInput::GetInst()->AddBindFunction<CPlayer>("MoveDown", Input_Type::UP, this, &CPlayer::YesHorizontal, m_scene);
    CInput::GetInst()->AddBindFunction<CPlayer>("MoveLeft", Input_Type::UP, this, &CPlayer::YesVertical, m_scene);
    CInput::GetInst()->AddBindFunction<CPlayer>("MoveRight", Input_Type::UP, this, &CPlayer::YesVertical, m_scene);
    CInput::GetInst()->AddBindFunction<CPlayer>("Bomb",Input_Type::DOWN, this, &CPlayer::Bomb, m_scene);
    CInput::GetInst()->AddBindFunction<CPlayer>("Skill1",Input_Type::DOWN, this, &CPlayer::Skill1, m_scene);
    CInput::GetInst()->AddBindFunction<CPlayer>("Skill2",Input_Type::DOWN, this, &CPlayer::Skill2, m_scene);
    CInput::GetInst()->AddBindFunction<CPlayer>("PositionReset",Input_Type::DOWN, this, &CPlayer::PositionReset, m_scene);
    CInput::GetInst()->AddBindFunction<CPlayer>("CheatMode",Input_Type::DOWN, this, &CPlayer::CheatMode, m_scene);
    CInput::GetInst()->AddBindFunction<CPlayer>("Pause",Input_Type::DOWN, this, &CPlayer::Pause, m_scene);

    m_GamePause = m_scene->CreateWidgetWindow<CGamePause>("GamePause");
    m_GamePause->SetEnable(false);
   
    m_UIObj = m_scene->CreateObject<CUIObject>("UIObject");
    m_UIObj->SetCount(0, m_bombCount);
    m_UIObj->SetCount(1, m_bombPower);
    m_UIObj->SetCount(2, m_speedCount);
    if (m_scene->GetName() == "CScene00")
    {
        m_UIObj->FindWidgetComponent("ItemIcon_4")->SetEnable(false);
    }
    else
    {
        m_HaveShoes = true;
    }
    if(m_scene->GetName()!="CScene02")
    {
        m_UIObj->FindWidgetComponent("ItemIcon_5")->SetEnable(false);
    }
    else
    {
        m_HaveDart = true;
    }
    m_UIObj->FindWidgetComponent("ItemIcon_6")->SetEnable(false);
    SetSideWallCheck(true);

    char widgetName[64] = {};
    int m_WallCount = m_scene->GetWallCount();
    int j = 1;
    for (int i = 0; i < m_WallCount; ++j)
    {
        sprintf_s(widgetName, "Wall%d", j);
        if (widgetName == "Wall99")
        {
            break;
        }
        if (!m_scene->FindObject<CWall>(widgetName))
        {
            continue;
        }
        m_listWall.push_back(m_scene->FindObject<CWall>(widgetName));
        ++i;
    }
    return true;
}

void CPlayer::Update(float deltaTime)
{
    CCharacter::Update(deltaTime);
    deltaTime *= m_timeScale;
    m_CoolTime += deltaTime;
    if(!m_IsCheat)
    {
        m_InvisibleTime += deltaTime;
    }
    {
        auto	iter = m_listBomb.begin();
        auto	iterEnd = m_listBomb.end();
        for (; iter != iterEnd;)
        {
            if ((*iter)->GetIsBomb())
            {
                iter = m_listBomb.erase(iter);
                continue;
            }
            ++iter;
        }
    }
    auto	iter = m_listWall.begin();
    auto	iterEnd = m_listWall.end();
    for (; iter != iterEnd;)
    {
        if (!(*iter)->GetActive())
        {
            iter = m_listWall.erase(iter);
            continue;
        }
        ++iter;
    }
    if (m_IsSlip&& !CheckCurrentAnimation("PlayerBubble"))
    {
        Slippery();
    }
}

void CPlayer::PostUpdate(float deltaTime)
{
    CCharacter::PostUpdate(deltaTime);
    if (m_InvisibleTime > 2.f && m_EnemyCollider)
    {
        m_EnemyCollider = nullptr;
        box->ClearCollisionList();
    }
    if (box->GetProfile()->channel == ECollision_Channel::Bubble)
    {
        return;
    }
    if (CheckCurrentAnimation("PlayerEscape"))
    {
        return;
    }
    if (m_move.x != 0.f || m_move.y != 0.f)
    {
        if (m_InvisibleTime < 2.f)
        {
            ChangeAnimation(m_vecSequenceKey[m_playerDir][1]);
        }
        else
        {
            ChangeAnimation(m_vecSequenceKey[m_playerDir][0]);
        }
    }
    else if(!CheckCurrentAnimation("PlayerStart"))
    {
        m_playerDir = (int)Direction::Down;
        if (m_InvisibleTime < 2.f)
        {
            ChangeAnimation("PlayerInvisibleD");
        }
        else
        {
            ChangeAnimation("PlayerIdle");
        }
    }
}

void CPlayer::Render(HDC hDC,float deltaTime)
{
    CCharacter::Render(hDC, deltaTime);
}

void CPlayer::SetSpeed()
{
    m_moveSpeed = 200.f + 20 * m_speedCount;
}

void CPlayer::MoveUp()
{   
    if (!m_canVertical)
    {
        return;
    }
    m_playerDir = (int)Direction::Up;
    MoveDir(Vector2(0.f, -1.f));
}

void CPlayer::MoveDown()
{
    if (!m_canVertical)
    {
        return;
    }
    m_playerDir = (int)Direction::Down;
    MoveDir(Vector2(0.f, 1.f));
}

void CPlayer::MoveLeft()
{
    if (!m_canHorizon)
    {
        return;
    }
    m_playerDir = (int)Direction::Left;
    MoveDir(Vector2(-1.f, 0.f));
}

void CPlayer::MoveRight()
{
    if (!m_canHorizon)
    {
        return;
    }
    m_playerDir = (int)Direction::Right;
    MoveDir(Vector2(1.f, 0.f));
}

void CPlayer::Bomb()
{
    if (box->GetProfile()->channel == ECollision_Channel::Bubble || m_listBomb.size() >= m_bombCount||
        0.f==GetTimeScale())
    {
        return;
    }
    CTileMap* tileMap = m_scene->GetTileMap();
    Vector2 tilePos = tileMap->GetTile(m_pos)->GetPos();
    Vector2 differ = m_pos - (tilePos + TILE * 0.5f);
    Vector2 tileDifferPos = tileMap->GetTile(m_pos + differ)->GetPos();
    {
        auto	iter = m_listBomb.begin();
        auto	iterEnd = m_listBomb.end();
        for (; iter != iterEnd;++iter)
        {
            if (tileDifferPos == tileMap->GetTile((*iter)->GetPos())->GetPos()||
                tilePos == tileMap->GetTile((*iter)->GetPos())->GetPos())
            {
                return;
            }
        }
    }
    m_scene->GetSceneResource()->SoundPlay("Bomb_set");
    CBomb* bomb = m_scene->CreateObject<CBomb>("Bomb");
    int playerIndexX = tileMap->GetTileIndexX(tilePos.x);
    int playerIndexY = tileMap->GetTileIndexY(tilePos.y);
    int differIndexX = tileMap->GetTileIndexX(tileDifferPos.x)- playerIndexX;
    int differIndexY = tileMap->GetTileIndexY(tileDifferPos.y)- playerIndexY;
    Vector2 tileHorizontalPos;
    Vector2 tileVerticalPos;
    if(differIndexX !=0&& differIndexY != 0)
    {
        tileHorizontalPos= tileMap->GetTile(playerIndexX+ differIndexX, playerIndexY)->GetPos();
        tileVerticalPos = tileMap->GetTile(playerIndexX, playerIndexY+ differIndexY)->GetPos();
    }
    int wallCount=0;
    bool isWall = false;
    auto	iter = m_listWall.begin();
    auto	iterEnd = m_listWall.end();
    for (; iter != iterEnd; ++iter)
    {
        if (tileHorizontalPos == tileMap->GetTile((*iter)->GetPos())->GetPos())
        {
            ++wallCount;
        }
        if (tileVerticalPos == tileMap->GetTile((*iter)->GetPos())->GetPos())
        {
            ++wallCount;
        }
        if (tileDifferPos == tileMap->GetTile((*iter)->GetPos())->GetPos())
        {
            isWall = true;
            break;
        }
    }
    if(wallCount ==2)
    {
        isWall = true;
    }
    if(isWall)
    {
        bomb->SetPos(tilePos + TILE * 0.5f);
    }
    else
    {
        bomb->SetPos(tileDifferPos + TILE * 0.5f);
    }
    bomb->SetDistance(m_bombPower);
    CCollider* bombCol = bomb->FindCollider("Bomb");
    bombCol->SetCollisionProfile("PlayerAttack");
    m_listBomb.push_back(bomb);
}

void CPlayer::Skill1()
{
    if (box->GetProfile()->channel != ECollision_Channel::Bubble || !m_HaveNeedle|| CheckCurrentAnimation("PlayerDie"))
    {
        return;
    }
    m_InvisibleTime = 0.f;
    box->SetCollisionProfile("Player");
    m_HaveNeedle = false;
    SetSpeed();
    m_scene->GetSceneResource()->SoundPlay("Escape");
    ChangeAnimation("PlayerEscape");
    m_UIObj->FindWidgetComponent("ItemIcon_3")->SetEnable(false);
}

void CPlayer::Skill2()
{
    if (box->GetProfile()->channel == ECollision_Channel::Bubble || !m_HaveDart|| 2.f>m_CoolTime)
    {
        return;
    }
    m_CoolTime = 0;
    m_UIObj->StartCT();
    m_scene->GetSceneResource()->SoundPlay("Dart");
    CBullet* dart = m_scene->CreateObject<CBullet>("Dart");
    CCollider* dartCol = dart->FindCollider("Bullet");
    dartCol->SetCollisionProfile("PlayerAttack");
    float	dartX= m_pos.x;
    float	dartY= m_pos.y;
    Vector2 direction;
    if (m_playerDir == 2)
    {
        dartX -= m_pivot.x * m_size.x + (1.f - dart->GetPivot().x) * dart->GetSize().x;
        dart->SetTexture("DartL", TEXT("Attack/Dart_left.bmp"));
        dart->SetAngle(Vector2(-1, 0));
        dartCol->SetOffset(-10.f,0);
    }
    else if(m_playerDir==3)
    {
        dartX += m_pivot.x * m_size.x + (1.f - dart->GetPivot().x) * dart->GetSize().x;
        dart->SetTexture("DartR", TEXT("Attack/Dart_right.bmp"));
        dart->SetAngle(Vector2(1, 0));
        dartCol->SetOffset(10.f, 0);
    }
    else if (m_playerDir == 0)
    {
        dartY -= m_pivot.y * m_size.y + (1.f - dart->GetPivot().y) * dart->GetSize().y;
        dart->SetTexture("DartU", TEXT("Attack/Dart_up.bmp"));
        dart->SetAngle(Vector2(0, -1));
        dartCol->SetOffset(0, -10.f);
    }
    else
    {
        dartY += m_pivot.y * m_size.y + (1.f - dart->GetPivot().y) * dart->GetSize().y;
        dart->SetTexture("DartD", TEXT("Attack/Dart_down.bmp"));
        dart->SetAngle(Vector2(0, 1));
        dartCol->SetOffset(0, 10.f);
    }
    dart->SetSize(50.f, 50.f);
    dart->SetDistance(52.f*7);
    dart->SetMoveSpeed(500.f);
    dart->SetColorKey(255, 0, 255);
    dart->SetPos(dartX, dartY); 
}

void CPlayer::Die()
{
    m_moveSpeed = 0;
    m_scene->GetSceneResource()->SoundPlay("Pop");
    ChangeAnimation("PlayerDie");
}

void CPlayer::Result()
{
    m_scene->CreateWidgetWindow<CGameOver>("GameOver");
}

void CPlayer::Idle()
{
    ChangeAnimation("PlayerIdle");
}

void CPlayer::YesVertical()
{
    m_canVertical = true;
    if(m_KeyCount>=3)
    {
        m_canHorizon = false; 
    }
    --m_KeyCount;
    if (m_KeyCount == 0)
    {
        m_IsSlip = true;
        m_jumpVelocity = 100.f;
    }
}

void CPlayer::NoVertical()
{
    ++m_KeyCount;
    m_canVertical = false;
    m_canHorizon = true;
    m_jumpVelocity = 0.f;
    m_IsSlip = false;
}

void CPlayer::PositionReset()
{
    //m_move때문에 기본애니메이션 설정하면 바로 다른애니메이션으로 전환된다
    SetPos(START_TILE.x, START_TILE.y + TILE.y * 12);
    m_InvisibleTime = 0;
}

void CPlayer::CheatMode()
{
    m_InvisibleTime = 0.f;
    m_IsCheat = true;
    m_bombCount = m_maxCount;
    m_UIObj->SetCount(0, m_maxCount);
    m_bombPower = m_maxCount;
    m_UIObj->SetCount(1, m_maxCount);
    m_speedCount = m_maxCount;
    SetSpeed();
    m_UIObj->SetCount(2, m_maxCount);
    m_HaveNeedle = true;
    m_UIObj->FindWidgetComponent("ItemIcon_3")->SetEnable(true);
    m_HaveShoes = true;
    m_UIObj->FindWidgetComponent("ItemIcon_4")->SetEnable(true);
    m_HaveDart = true;
    m_UIObj->FindWidgetComponent("ItemIcon_5")->SetEnable(true);
}

void CPlayer::Pause()
{
    if (CheckCurrentAnimation("PlayerDie")|| m_scene->FindWidgetWindow<CGameWin>("GameWin"))
    {
        return;
    }
    m_scene->GetSceneResource()->SoundPlay("PopWindow");
    if(1.f==CGameManager::GetInst()->GetTimeScale())
    {
        m_scene->FindWidgetWindow<CItemHUD>("ItemHUD")->FindWidget<CButton>("QuitButton")->SetEnable(false);
        m_GamePause->SetEnable(true);
        CGameManager::GetInst()->SetTimeScale(0.f);
        return;
    }
    m_scene->FindWidgetWindow<CItemHUD>("ItemHUD")->FindWidget<CButton>("QuitButton")->SetEnable(true);
    m_GamePause->SetEnable(false);
    CGameManager::GetInst()->SetTimeScale(1.f);
}

void CPlayer::YesHorizontal()
{
    if (m_KeyCount >= 3)
    {
        m_canVertical = false;
    }
    m_canHorizon = true;
    --m_KeyCount;
    if (m_KeyCount == 0)
    {
        m_IsSlip = true;
        m_jumpVelocity = 100.f;
    }
}

void CPlayer::NoHorizontal()
{
    ++m_KeyCount;
    m_canVertical = true;
    m_canHorizon = false;
    m_jumpVelocity = 0.f;
    m_IsSlip = false;
}

void CPlayer::CollisionBegin(CCollider* src, CCollider* dest)
{ 
    //다트랑 겹칠수 있으니까 이름으로 받아야 한다.
    //플레이어랑 풍선이 박았을때 풍선이 먼저 처리된다.
    if (dest->GetOwner()->GetName() == "Bomb")
    {
        //m_BombCollider = dest;
        CTileMap* tileMap = m_scene->GetTileMap();
		Vector2 tilePos = tileMap->GetTile(m_pos)->GetPos() + TILE * 0.5f;
		Vector2 tilePrevPos = tileMap->GetTile(m_prevPos)->GetPos() + TILE * 0.5f;
        Vector2 destPos = dest->GetOwner()->GetPos();
        Vector2 m_Dir;
		//플레이어의 위치가 콜라이더 안에 있을때는 풍선을 차지않도록 해야한다.
		if (tilePrevPos == tilePos)
		{
			return;
		}
		//신발이 없으면 플레이어 밀어내기
		if (tilePrevPos != tilePos)
		{
			//플레이어가 왼쪽
			if (tilePos.x - tilePrevPos.x > 0)
			{
                m_prevPos.x = tilePrevPos.x + m_ColliderSize.x * m_pivot.x - 1.f;
                m_Dir = Vector2(1.f,0);
			}
			//플레이어가 오른쪽
			if (tilePos.x - tilePrevPos.x < 0)
			{
                m_prevPos.x = tilePrevPos.x - m_ColliderSize.x * m_pivot.x + 1.f;
                m_Dir = Vector2(-1.f, 0);
			}
			//플레이어가 위쪽
			if (tilePos.y - tilePrevPos.y > 0)
			{
                m_prevPos.y = tilePrevPos.y + m_ColliderSize.y * m_pivot.y - 1.f;
                m_Dir = Vector2(0.f, 1.f);
			}
			//플레이어가 아래쪽
			if (tilePos.y - tilePrevPos.y < 0)
			{
                m_prevPos.y = tilePrevPos.y - m_ColliderSize.y * m_pivot.y + 1.f;
                m_Dir = Vector2(0.f, -1.f);
			}
			m_pos=m_prevPos;
		}
        //신발을 가지고 있어도 풍선앞에 풍선이있으면 차지않는다
        auto	iter = m_listBomb.begin();
        auto	iterEnd = m_listBomb.end();
        for (; iter != iterEnd;++iter)
        {
            if (tileMap->GetTile(destPos + m_Dir * TILE)->GetPos() == tileMap->GetTile((*iter)->GetPos())->GetPos())
            {
                return;
            }

        }
		//플레이어가 신발아이템을 가지고 있을때 플레이어가 바라보는 방향으로 이동
		if(m_HaveShoes)
		{
            dest->GetOwner()->SetMove(m_move);
			auto	iter = m_listWall.begin();
			auto	iterEnd = m_listWall.end();
			for (; iter != iterEnd; ++iter)
			{
				if (tileMap->GetTile(destPos +m_Dir*TILE)->GetPos() == tileMap->GetTile((*iter)->GetPos())->GetPos())
				{
                    dest->GetOwner()->SetMove(0,0);
					break;
				}
			}
			return;
		}
    }
    if (dest->GetProfile()->channel == ECollision_Channel::Item)
    {
        if (dest->GetOwner()->GetName() == "Ballon")
        {
            if (++m_bombCount > m_maxCount)
            {
                m_bombCount = m_maxCount;
            }
            m_UIObj->SetCount(0, m_bombCount);
            return;
        }
        if (dest->GetOwner()->GetName() == "Potion")
        {
            if (++m_bombPower > m_maxCount)
            {
                m_bombPower = m_maxCount;
            }
            m_UIObj->SetCount(1, m_bombPower);
            return;
        }
        if (dest->GetOwner()->GetName() == "PotionMax")
        {
            m_bombPower = m_maxCount;
            m_UIObj->SetCount(1, m_maxCount);
            return;
        }
        if (dest->GetOwner()->GetName() == "Skate")
        {
            if (++m_speedCount > m_maxCount)
            {
                m_speedCount = m_maxCount;
            }
            SetSpeed();
            m_UIObj->SetCount(2, m_speedCount);
            return;
        }
        if (dest->GetOwner()->GetName() == "Needle")
        {
            m_HaveNeedle = true;
            m_UIObj->FindWidgetComponent("ItemIcon_3")->SetEnable(true);
            return;
        }
        if (dest->GetOwner()->GetName() == "Shoes")
        {
            m_HaveShoes = true;
            m_UIObj->FindWidgetComponent("ItemIcon_4")->SetEnable(true);
            SetTimeScale(0.f);
            box->SetEnable(false);
            m_scene->CreateWidgetWindow<CGameWin>("GameWin");
            return;
        }
        if (dest->GetOwner()->GetName() == "Dart")
        {
            m_HaveDart = true;
            m_UIObj->FindWidgetComponent("ItemIcon_5")->SetEnable(true);
            SetTimeScale(0.f);
            box->SetEnable(false);
            m_scene->CreateWidgetWindow<CGameWin>("GameWin");
            return;
        }
        if (dest->GetOwner()->GetName() == "Treasure")
        {
            SetTimeScale(0.f);
            box->SetEnable(false);
            m_UIObj->FindWidgetComponent("ItemIcon_6")->SetEnable(true);
            m_scene->CreateWidgetWindow<CGameWin>("GameWin");
            return;
        }
    }
    if (dest->GetProfile()->channel == ECollision_Channel::Monster || 
        dest->GetProfile()->channel == ECollision_Channel::Default|| 
        dest->GetProfile()->channel == ECollision_Channel::MonsterAttack)
    {
        if(m_InvisibleTime<2.f)
        {
            return;
        }
        m_EnemyCollider = dest;
        box->SetCollisionProfile("Bubble");
        m_scene->GetSceneResource()->SoundPlay("Bubble");
        ChangeAnimation("PlayerBubble");
        m_moveSpeed = 20.f;
        return;
    }
}

void CPlayer::CollisionEnd(CCollider* src, CCollider* dest)
{
    
}