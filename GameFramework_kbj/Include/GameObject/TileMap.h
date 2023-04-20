#pragma once
#include "GameObject.h"
class CTileMap : public CGameObject
{
private:
	friend class CScene;
	std::vector<class CTile*>	m_vecTile;
	CSharedPtr<class CTexture>	m_TileTexture;
	Vector2	m_TileSize;
	int		m_CountX;
	int		m_CountY;
	int		m_StartX;
	int		m_StartY;
	int		m_EndX;
	int		m_EndY;
protected:
	CTileMap();
	CTileMap(const CTileMap& obj);
	virtual ~CTileMap();
public:
	int GetCountX()	const
	{
		return m_CountX;
	}
	int GetCountY()	const
	{
		return m_CountY;
	}
	void ChangeTileOption(const Vector2& pos, ETile_Option option);
	void SetTileFrame(const Vector2& pos, const Vector2& start,	const Vector2& end);
	void SetTileRender(const Vector2& pos, bool render);
	void SetTileSideCollision(const Vector2& pos, bool side);
	class CTile* GetTile(const Vector2& pos);
	class CTile* GetTile(const float x,const float y);
	class CTile* GetTile(int index);
	class CTile* GetTile(int indexX, int indexY);
	int GetTileIndexX(float x);
	int GetTileIndexY(float y);
	int GetTileIndex(const Vector2& pos);
	int GetTileOriginIndexX(float x);
	int GetTileOriginIndexY(float y);
	bool CreateTile(int countX, int countY, const Vector2& tileSize);
	void SetTileTexture(const std::string& name);
	void SetTileTexture(int index, class CTexture* texture);
	void SetTileTexture(class CTexture* texture);
	void SetTileTexture(const std::string& name, const TCHAR* fileName,	const std::string& pathName = TEXTURE_PATH);
	void SetTileTextureFullPath(const std::string& name, const TCHAR* fullPath);
	bool SetTileColorKey(unsigned char r, unsigned char g, unsigned char b,	int index = 0);
	bool SetTileColorKeyAll(unsigned char r, unsigned char g, unsigned char b);
	virtual bool Init();
	virtual void Update(float deltaTime);
	virtual void Render(HDC hDC, float deltaTime);
	virtual void Save(FILE* file);
	virtual void Load(FILE* file);
#ifdef UNICODE
	void SetTileTexture(const std::string& name, const std::vector<std::wstring>& vecFileName,
		const std::string& pathName = TEXTURE_PATH);
	void SetTileTextureFullPath(const std::string& name, const std::vector<std::wstring>& vecFullPath);
#else
	void SetTileTexture(const std::string& name, const std::vector<std::string>& vecFileName,
		const std::string& pathName = TEXTURE_PATH);
	void SetTileTextureFullPath(const std::string& name, const std::vector<std::string>& vecFullPath);
#endif // UNICODE
};

