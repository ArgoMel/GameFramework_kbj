#include "Scene_edit.h"
#include "../GameObject/TileMap.h"
#include "SceneResource.h"
#include "Camera.h"
#include "../Input.h"
#include "../GameManager.h"
#include "EditDialog.h"
#include "../Resource/Texture/Texture.h"

CScene_edit::CScene_edit()
	: m_TileMapDlg(nullptr)
{
}

CScene_edit::~CScene_edit()
{
	CGameManager::GetInst()->SetEditMode(false);
	SAFE_DELETE(m_TileMapDlg);
}

void CScene_edit::ChangeFrame()
{
	Vector2	mousePos = CInput::GetInst()->GetMouseWorldPos();
	const AnimationFrameData* frame = m_TileMapDlg->GetTileFrameData();
	if (!frame)
	{
		return;
	}
	int index = m_TileMap->GetTileIndex(mousePos);
	if(-1==index)
	{
		return;
	}
	m_TileMap->SetTileTexture(index, m_TileMapDlg->GetSelectTexture());
	m_TileMap->SetTileRender(mousePos, m_TileMapDlg->GetCheckRender());
	m_TileMap->SetTileSideCollision(mousePos, m_TileMapDlg->GetCheckSideCollision());

}

void CScene_edit::ChangeOption()
{
	Vector2	mousePos = CInput::GetInst()->GetMouseWorldPos();
	ETile_Option selectOption = m_TileMapDlg->GetSelectOption();
	m_TileMap->ChangeTileOption(mousePos, selectOption);
	m_TileMap->SetTileRender(mousePos, m_TileMapDlg->GetCheckRender());
	m_TileMap->SetTileSideCollision(mousePos, m_TileMapDlg->GetCheckSideCollision());
}

bool CScene_edit::Init()
{
	GetCamera()->SetResolution(1280.f, 720.f);
	GetCamera()->SetWorldResolution(1920.f, 1080.f);
	GetCamera()->SetTargetPivot(0.5f, 0.5f);

	CInput::GetInst()->AddBindFunction<CScene_edit>("MoveUp",Input_Type::STAY, this, &CScene_edit::MoveUp,this);
	CInput::GetInst()->AddBindFunction<CScene_edit>("MoveDown",Input_Type::STAY, this, &CScene_edit::MoveDown, this);
	CInput::GetInst()->AddBindFunction<CScene_edit>("MoveRight",Input_Type::STAY, this, &CScene_edit::MoveRight, this);
	CInput::GetInst()->AddBindFunction<CScene_edit>("MoveLeft",Input_Type::STAY, this, &CScene_edit::MoveLeft, this);
	CInput::GetInst()->AddBindFunction<CScene_edit>("OpenTileMapEditor",Input_Type::DOWN, this, &CScene_edit::OpenTileMapEditor, this);
	CInput::GetInst()->AddBindFunction<CScene_edit>("Click",Input_Type::STAY, this, &CScene_edit::MouseLButtonDrag, this);
	
	CGameManager::GetInst()->SetEditMode(true);
	return true;
}

void CScene_edit::CreateTileMap(int countX, int countY, int sizeX, int sizeY)
{
	if (!m_TileMap)
	{
		m_TileMap = CreateObject<CTileMap>("TileMap");
	}
	m_TileMap->CreateTile(countX, countY, Vector2((float)sizeX, (float)sizeY));
}

void CScene_edit::SetTileTexture(CTexture* texture)
{
	if (m_TileMap)
	{
		m_TileMap->SetTileTexture(texture);
	}
}

void CScene_edit::LoadTileMap(const char* fullPath)
{
	if (!m_TileMap)
	{
		m_TileMap = CreateObject<CTileMap>("TileMap");
	}
	m_TileMap->LoadFullPath(fullPath);
}

void CScene_edit::MoveLeft()
{
	Vector2 cameraPos = GetCamera()->GetPos();
	GetCamera()->SetPos(cameraPos + Vector2(-500.f * DELTA_TIME, 0.f));
}

void CScene_edit::MoveRight()
{
	Vector2 cameraPos = GetCamera()->GetPos();
	GetCamera()->SetPos(cameraPos + Vector2(500.f * DELTA_TIME, 0.f));
}

void CScene_edit::MoveUp()
{
	Vector2 cameraPos = GetCamera()->GetPos();
	GetCamera()->SetPos(cameraPos + Vector2(0.f, -500.f * DELTA_TIME));
}

void CScene_edit::MoveDown()
{
	Vector2 cameraPos = GetCamera()->GetPos();
	GetCamera()->SetPos(cameraPos + Vector2(0.f, 500.f * DELTA_TIME));
}

void CScene_edit::OpenTileMapEditor()
{
	if (!m_TileMapDlg)
	{
		m_TileMapDlg = new CEditDialog;
		m_TileMapDlg->m_scene = this;
		m_TileMapDlg->Init();
	}
}

void CScene_edit::MouseLButtonDrag()
{
	if (!m_TileMap)
	{
		return;
	}
	Vector2	mousePos = CInput::GetInst()->GetMousePos();
	CCamera* camera = GetCamera();
	if (mousePos.x < 0.f || mousePos.x > camera->GetResolution().x || mousePos.y < 0.f || mousePos.y > camera->GetResolution().y)
	{
		return;
	}
	switch (m_TileMapDlg->GetBrushType())
	{
	case ETile_Brush::Frame:
		ChangeFrame();
		break;
	case ETile_Brush::Option:
		ChangeOption();
		break;
	}
}
