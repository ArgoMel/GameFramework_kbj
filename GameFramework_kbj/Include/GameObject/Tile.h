#pragma once
#include "../GameInfo.h"

class CTile
{
private:
	friend class CTileMap;
	class CScene* m_scene;
	class CTileMap* m_owner;
	CSharedPtr<class CTexture>	m_texture;
	ETile_Option	m_Option;
	Vector2		m_pos;
	Vector2		m_size;
	Vector2		m_StartFrame;
	Vector2		m_EndFrame;
	int			m_IndexX;
	int			m_IndexY;
	int			m_Index;
	int			m_TileFrame;
	bool		m_Render;
	bool		m_SideCollision;
	CTile();
	~CTile();
public:
	ETile_Option GetOption()	const
	{
		return m_Option;
	}
	Vector2 GetPos()	const;
	const Vector2& GetSize()	const
	{
		return m_size;
	}
	bool GetSideCollision()	const
	{
		return m_SideCollision;
	}
	void SetTileInfo(const Vector2& pos, const Vector2& size,int indexX, int indexY, int index, class CTexture* texture);
	void SetTileOption(ETile_Option option)
	{
		m_Option = option;
	}
	void SetFrame(const Vector2& start, const Vector2& end)
	{
		m_StartFrame = start;
		m_EndFrame = end;
	}
	void SetRender(bool render)
	{
		m_Render = render;
	}
	void SetSideCollision(bool side)
	{
		m_SideCollision = side;
	}
	void Render(HDC hDC);
	void Save(FILE* file);
	void Load(FILE* file);
};

