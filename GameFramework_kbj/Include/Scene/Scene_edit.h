#pragma once
#include "Scene.h"
class CScene_edit : public CScene
{
private:
	friend class CSceneManager;
	class CEditDialog* m_TileMapDlg;
	void ChangeFrame();
	void ChangeOption();
protected:
	CScene_edit();
	virtual ~CScene_edit();
public:
	class CTileMap* GetTileMap()	const
	{
		return m_TileMap;
	}
	bool Init();
	void CreateTileMap(int countX, int countY, int sizeX, int sizeY);
	void SetTileTexture(class CTexture* texture);
	void LoadTileMap(const char* fullPath);
	void MoveLeft();
	void MoveRight();
	void MoveUp();
	void MoveDown();
	void OpenTileMapEditor();
	void MouseLButtonDrag();
};

