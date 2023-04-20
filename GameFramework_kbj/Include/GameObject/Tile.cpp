#include "Tile.h"
#include "TileMap.h"
#include "../Resource/Texture/Texture.h"
#include "../Scene/Scene.h"
#include "../Scene/Camera.h"
#include "../Scene/SceneManager.h"
#include "../Scene/SceneResource.h"
#include "../GameManager.h"

CTile::CTile()
	: m_Option(ETile_Option::Normal)
	, m_scene(nullptr)
	, m_owner(nullptr)
	, m_IndexX(0)
	, m_IndexY(0)
	, m_Index(0)
	, m_TileFrame(0)
	, m_Render(true)
	, m_SideCollision(false)
{
}

CTile::~CTile()
{
}

Vector2 CTile::GetPos() const
{
	return m_pos + m_owner->GetPos();
}

void CTile::SetTileInfo(const Vector2& pos, const Vector2& size, int indexX, int indexY, int index, CTexture* texture)
{
	m_texture = texture;
	m_pos = pos;
	m_size = size;
	m_IndexX = indexX;
	m_IndexY = indexY;
	m_Index = index;
}

void CTile::Render(HDC hDC)
{
	Vector2	pos;
	Vector2	cameraPos;
	Vector2	resolution;
	if (m_scene)
	{
		cameraPos = m_scene->GetCamera()->GetPos();
		resolution = m_scene->GetCamera()->GetResolution();
		pos = m_pos + m_owner->GetPos() - m_scene->GetCamera()->GetPos();
	}
	else
	{
		CScene* scene = CSceneManager::GetInst()->GetScene();
		pos = m_pos + m_owner->GetPos() - scene->GetCamera()->GetPos();
		cameraPos = scene->GetCamera()->GetPos();
		resolution = scene->GetCamera()->GetResolution();
	}
	if (m_Render)
	{
		if (m_texture)
		{
			if (m_texture->GetEnableColorKey())
			{
				if (m_texture->GetTextureType() == ETexture_Type::Sprite)
				{
					TransparentBlt(hDC, (int)pos.x,
						(int)pos.y,
						(int)m_size.x,
						(int)m_size.y, m_texture->GetDC(),
						(int)m_StartFrame.x,
						(int)m_StartFrame.y,
						(int)m_size.x,
						(int)m_size.y, m_texture->GetColorKey());
				}
				else
				{
					TransparentBlt(hDC, (int)pos.x,
						(int)pos.y,
						(int)m_size.x,
						(int)m_size.y, m_texture->GetDC(m_TileFrame), 0, 0,
						(int)m_size.x,
						(int)m_size.y, m_texture->GetColorKey(m_TileFrame));
				}
			}
			else
			{
				if (m_texture->GetTextureType() == ETexture_Type::Sprite)
				{
					BitBlt(hDC, (int)pos.x,
						(int)pos.y,
						(int)m_size.x,
						(int)m_size.y, m_texture->GetDC(),
						(int)m_StartFrame.x,
						(int)m_StartFrame.y, SRCCOPY);
				}
				else
				{
					BitBlt(hDC, (int)pos.x,
						(int)pos.y,
						(int)m_size.x,
						(int)m_size.y, m_texture->GetDC(m_TileFrame), 0, 0, SRCCOPY);
				}
			}
		}
	}
	//편집모드일때
	if (CGameManager::GetInst()->GetEditMode())
	{
		HBRUSH	brush = CGameManager::GetInst()->GetBrush(EBrush_Type::Green);
		switch (m_Option)
		{
		case ETile_Option::Normal:
			brush = CGameManager::GetInst()->GetBrush(EBrush_Type::Green);
			break;
		case ETile_Option::ImpossibleToMove:
			brush = CGameManager::GetInst()->GetBrush(EBrush_Type::Red);
			break;
		case ETile_Option::Slippery:
			brush = CGameManager::GetInst()->GetBrush(EBrush_Type::Blue);
			break;
		}

		RECT	rc = {};
		rc.left = (long)pos.x;
		rc.top = (long)pos.y;
		rc.right = (long)(pos.x + m_size.x);
		rc.bottom = (long)(pos.y + m_size.y);
		FrameRect(hDC, &rc, brush);
	}
}

void CTile::Save(FILE* file)
{
	fwrite(&m_Option, sizeof(ETile_Option), 1, file);
	fwrite(&m_pos, sizeof(Vector2), 1, file);
	fwrite(&m_size, sizeof(Vector2), 1, file);
	fwrite(&m_Render, sizeof(bool), 1, file);
	fwrite(&m_SideCollision, sizeof(bool), 1, file);
	fwrite(&m_IndexX, sizeof(int), 1, file);
	fwrite(&m_IndexY, sizeof(int), 1, file);
	fwrite(&m_Index, sizeof(int), 1, file);
	fwrite(&m_TileFrame, sizeof(int), 1, file);
	fwrite(&m_StartFrame, sizeof(Vector2), 1, file);
	fwrite(&m_EndFrame, sizeof(Vector2), 1, file);
	bool	texture = false;
	if (m_texture)
	{
		texture = true;
	}
	fwrite(&texture, sizeof(bool), 1, file);
	if (m_texture)
	{
		m_texture->Save(file);
	}
}

void CTile::Load(FILE* file)
{
	fread(&m_Option, sizeof(ETile_Option), 1, file);
	fread(&m_pos, sizeof(Vector2), 1, file);
	fread(&m_size, sizeof(Vector2), 1, file);
	fread(&m_Render, sizeof(bool), 1, file);
	fread(&m_SideCollision, sizeof(bool), 1, file);
	fread(&m_IndexX, sizeof(int), 1, file);
	fread(&m_IndexY, sizeof(int), 1, file);
	fread(&m_Index, sizeof(int), 1, file);
	fread(&m_TileFrame, sizeof(int), 1, file);
	fread(&m_StartFrame, sizeof(Vector2), 1, file);
	fread(&m_EndFrame, sizeof(Vector2), 1, file);
	bool	texture = false;
	fread(&texture, sizeof(bool), 1, file);
	if (texture)
	{
		m_texture = m_scene->GetSceneResource()->LoadTexture(file);
	}
}