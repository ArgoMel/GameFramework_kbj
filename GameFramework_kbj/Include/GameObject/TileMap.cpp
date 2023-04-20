#include "TileMap.h"
#include "../Resource/Texture/Texture.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"
#include "Tile.h"
#include "../Scene/Camera.h"
#include "../Scene/SceneManager.h"

CTileMap::CTileMap()
	: m_CountX(0)
	, m_CountY(0)
	, m_StartX(-1)
	, m_StartY(-1)
	, m_EndX(-1)
	, m_EndY(-1)
{
	SetTypeID<CTileMap>();
	m_renderLayer = ERender_Layer::Tile;
}

CTileMap::CTileMap(const CTileMap& obj) 
	: CGameObject(obj)
	, m_CountX(obj.m_CountX)
	, m_CountY(obj.m_CountY)
	, m_StartX(obj.m_StartX)
	, m_StartY(obj.m_StartY)
	, m_EndX(obj.m_EndX)
	, m_EndY(obj.m_EndY)
{
}

CTileMap::~CTileMap()
{
	size_t	size = m_vecTile.size();
	for (size_t i = 0; i < size; ++i)
	{
		SAFE_DELETE(m_vecTile[i]);
	}
}

void CTileMap::ChangeTileOption(const Vector2& pos, ETile_Option option)
{
	int	index = GetTileIndex(pos);
	if (index == -1)
	{
		return;
	}
	m_vecTile[index]->SetTileOption(option);
}

void CTileMap::SetTileFrame(const Vector2& pos, const Vector2& start, const Vector2& end)
{
	int	index = GetTileIndex(pos);
	if (index == -1)
	{
		return;
	}
	m_vecTile[index]->SetFrame(start, end);
}

void CTileMap::SetTileRender(const Vector2& pos, bool render)
{
	int	index = GetTileIndex(pos);
	if (index == -1)
	{
		return;
	}
	m_vecTile[index]->SetRender(render);
}

void CTileMap::SetTileSideCollision(const Vector2& pos, bool side)
{
	int	index = GetTileIndex(pos);
	if (index == -1)
	{
		return;
	}
	m_vecTile[index]->SetSideCollision(side);
}

CTile* CTileMap::GetTile(const Vector2& pos)
{
	int	index = GetTileIndex(pos);
	if (index == -1)
	{
		return nullptr;
	}
	return m_vecTile[index];
}

CTile* CTileMap::GetTile(const float x, const float y)
{
	Vector2 pos;
	pos.x = x;
	pos.y = y;
	int	index = GetTileIndex(pos);
	if (index == -1)
	{
		return nullptr;
	}
	return m_vecTile[index];
}

CTile* CTileMap::GetTile(int index)
{
	return m_vecTile[index];
}

CTile* CTileMap::GetTile(int indexX, int indexY)
{
	int num = indexY * m_CountX + indexX;
	if(num<0)
	{
		return nullptr;
	}
	return m_vecTile[num];
}

int CTileMap::GetTileIndexX(float x)
{
	float	convertX = x - m_pos.x;
	int	indexX = (int)(convertX / m_TileSize.x);
	if (indexX < 0 || indexX >= m_CountX)
	{
		return -1;
	}
	return indexX;
}

int CTileMap::GetTileIndexY(float y)
{
	float	convertY = y - m_pos.y;
	int	indexY = (int)(convertY / m_TileSize.y);
	if (indexY < 0 || indexY >= m_CountY)
	{
		return -1;
	}
	return indexY;
}

int CTileMap::GetTileIndex(const Vector2& pos)
{
	int	indexX = GetTileIndexX(pos.x);
	int	indexY = GetTileIndexY(pos.y);
	if (indexX == -1 || indexY == -1)
	{
		return -1;
	}
	return indexY * m_CountX + indexX;
}

int CTileMap::GetTileOriginIndexX(float x)
{
	float	convertX = x - m_pos.x;
	return (int)(convertX / m_TileSize.x);
}

int CTileMap::GetTileOriginIndexY(float y)
{
	float	convertY = y - m_pos.y;
	return (int)(convertY / m_TileSize.y);
}

bool CTileMap::CreateTile(int countX, int countY, const Vector2& tileSize)
{
	m_CountX = countX;
	m_CountY = countY;
	m_TileSize = tileSize;
	size_t	size = m_vecTile.size();
	for (size_t i = 0; i < size; ++i)
	{
		SAFE_DELETE(m_vecTile[i]);
	}
	m_vecTile.clear();
	m_size = m_TileSize * Vector2((float)m_CountX, (float)m_CountY);
	//Vector2 worldSize = m_scene->GetCamera()->GetResolution();
	//if (worldSize.x < m_size.x)
	//{
	//	m_scene->GetCamera()->SetWorldResolution(m_size.x, worldSize.y);
	//}
	//if (worldSize.y < m_size.y)
	//{
	//	m_scene->GetCamera()->SetWorldResolution(worldSize.x, m_size.y);
	//}
	for (int i = 0; i < m_CountY; ++i)
	{
		for (int j = 0; j < m_CountX; ++j)
		{
			CTile* tile = new CTile;
			tile->m_scene = m_scene;
			tile->m_owner = this;
			Vector2	pos = m_TileSize * Vector2((float)j, (float)i);//+Vector2(199.f,-30.f);
			tile->SetTileInfo(pos, m_TileSize, j, i, i * m_CountX + j,m_TileTexture);
			m_vecTile.push_back(tile);
		}
	}
	return true;
}

void CTileMap::SetTileTexture(const std::string& name)
{
	m_TileTexture = m_scene->GetSceneResource()->FindTexture(name);
	size_t	size = m_vecTile.size();
	for (size_t i = 0; i < size; ++i)
	{
		m_vecTile[i]->m_texture = m_TileTexture;
	}
}

void CTileMap::SetTileTexture(int index, class CTexture* texture)
{
	m_TileTexture = texture;
	m_vecTile[index]->m_texture = m_TileTexture;
}

void CTileMap::SetTileTexture(CTexture* texture)
{
	m_TileTexture = texture;
	size_t	size = m_vecTile.size();
	for (size_t i = 0; i < size; ++i)
	{
		m_vecTile[i]->m_texture = m_TileTexture;
	}
}

void CTileMap::SetTileTexture(const std::string& name, const TCHAR* fileName, const std::string& pathName)
{
	m_scene->GetSceneResource()->LoadTexture(name, fileName, pathName);
	m_TileTexture = m_scene->GetSceneResource()->FindTexture(name);
	size_t	size = m_vecTile.size();
	for (size_t i = 0; i < size; ++i)
	{
		m_vecTile[i]->m_texture = m_TileTexture;
	}
}

void CTileMap::SetTileTextureFullPath(const std::string& name, const TCHAR* fullPath)
{
	m_scene->GetSceneResource()->LoadTextureFullPath(name, fullPath);
	m_TileTexture = m_scene->GetSceneResource()->FindTexture(name);
	size_t	size = m_vecTile.size();
	for (size_t i = 0; i < size; ++i)
	{
		m_vecTile[i]->m_texture = m_TileTexture;
	}
}

bool CTileMap::SetTileColorKey(unsigned char r, unsigned char g, unsigned char b, int index)
{
	if (!m_TileTexture)
	{
		return false;
	}
	m_TileTexture->SetColorKey(r, g, b, index);
	return true;
}

bool CTileMap::SetTileColorKeyAll(unsigned char r, unsigned char g, unsigned char b)
{
	if (!m_TileTexture)
	{
		return false;
	}
	m_TileTexture->SetColorKeyAll(r, g, b);
	return true;
}

bool CTileMap::Init()
{
	m_scene->SetTileMap(this);
	return true;
}

void CTileMap::Update(float deltaTime)
{
	CGameObject::Update(deltaTime);
	if (!m_vecTile.empty())
	{
		Vector2	pos;
		Vector2	cameraPos;
		Vector2	resolution;
		if (m_scene)
		{
			cameraPos = m_scene->GetCamera()->GetPos();
			resolution = m_scene->GetCamera()->GetResolution();
			pos = m_pos - m_scene->GetCamera()->GetPos();
		}
		else
		{
			CScene* scene = CSceneManager::GetInst()->GetScene();
			pos = m_pos - scene->GetCamera()->GetPos();
			cameraPos = scene->GetCamera()->GetPos();
			resolution = scene->GetCamera()->GetResolution();
		}
		m_StartX = (int)(cameraPos.x / m_TileSize.x);
		m_StartY = (int)(cameraPos.y / m_TileSize.y);
		m_EndX = (int)((cameraPos.x + resolution.x) / m_TileSize.x);
		m_EndY = (int)((cameraPos.y + resolution.y) / m_TileSize.y);
		m_StartX = m_StartX < 0 ? 0 : m_StartX;
		m_StartY = m_StartY < 0 ? 0 : m_StartY;
		m_EndX = m_EndX >= m_CountX ? m_CountX - 1 : m_EndX;
		m_EndY = m_EndY >= m_CountY ? m_CountY - 1 : m_EndY;
	}
}

void CTileMap::Render(HDC hDC, float deltaTime)
{
	CGameObject::Render(hDC, deltaTime);
	for (int i = m_StartY; i <= m_EndY; ++i)
	{
		for (int j = m_StartX; j <= m_EndX; ++j)
		{
			int num = i * m_CountX + j;
			m_vecTile[num]->Render(hDC);
		}
	}
}

void CTileMap::Save(FILE* file)
{
	CGameObject::Save(file);
	bool	texture = false;
	if (m_TileTexture)
	{
		texture = true;
	}
	fwrite(&texture, sizeof(bool), 1, file);
	if (m_TileTexture)
	{
		m_TileTexture->Save(file);
	}
	fwrite(&m_CountX, sizeof(int), 1, file);
	fwrite(&m_CountY, sizeof(int), 1, file);
	fwrite(&m_TileSize, sizeof(Vector2), 1, file);\
	int	tileCount = (int)m_vecTile.size();
	fwrite(&tileCount, sizeof(int), 1, file);
	for (int i = 0; i < tileCount; ++i)
	{
		m_vecTile[i]->Save(file);
	}
}

void CTileMap::Load(FILE* file)
{
	CGameObject::Load(file);
	bool	texture = false;
	fread(&texture, sizeof(bool), 1, file);
	if (texture)
	{
		m_TileTexture = m_scene->GetSceneResource()->LoadTexture(file);
	}
	fread(&m_CountX, sizeof(int), 1, file);
	fread(&m_CountY, sizeof(int), 1, file);
	fread(&m_TileSize, sizeof(Vector2), 1, file);
	int	tileCount = 0;
	fread(&tileCount, sizeof(int), 1, file);
	for (int i = 0; i < tileCount; ++i)
	{
		CTile* tile = new CTile;
		tile->m_owner = this;
		tile->m_scene = m_scene;
		tile->Load(file);
		m_vecTile.push_back(tile);
	}
	//m_scene->GetCamera()->SetWorldResolution(m_size);
}

#ifdef UNICODE
void CTileMap::SetTileTexture(const std::string& name, const std::vector<std::wstring>& vecFileName, const std::string& pathName)
{
	m_scene->GetSceneResource()->LoadTexture(name, vecFileName, pathName);
	m_TileTexture = m_scene->GetSceneResource()->FindTexture(name);
	size_t	size = m_vecTile.size();
	for (size_t i = 0; i < size; ++i)
	{
		m_vecTile[i]->m_texture = m_TileTexture;
	}
}
void CTileMap::SetTileTextureFullPath(const std::string& name, const std::vector<std::wstring>& vecFullPath)
{
	m_scene->GetSceneResource()->LoadTextureFullPath(name, vecFullPath);
	m_TileTexture = m_scene->GetSceneResource()->FindTexture(name);
	size_t	size = m_vecTile.size();
	for (size_t i = 0; i < size; ++i)
	{
		m_vecTile[i]->m_texture = m_TileTexture;
	}
}
#else
void CTileMap::SetTileTexture(const std::string& name,const std::vector<std::string>& vecFileName, const std::string& pathName)
{
	m_scene->GetSceneResource()->LoadTexture(name, vecFileName, pathName);
	m_TileTexture = m_scene->GetSceneResource()->FindTexture(name);
	size_t	size = m_vecTile.size();
	for (size_t i = 0; i < size; ++i)
	{
		m_vecTile[i]->m_texture = m_TileTexture;
	}
}
void CTileMap::SetTileTextureFullPath(const std::string& name,const std::vector<std::string>& vecFullPath)
{
	m_scene->GetSceneResource()->LoadTextureFullPath(name, vecFullPath);
	m_TileTexture = m_scene->GetSceneResource()->FindTexture(name);
	size_t	size = m_vecTile.size();
	for (size_t i = 0; i < size; ++i)
	{
		m_vecTile[i]->m_texture = m_TileTexture;
	}
}
#endif