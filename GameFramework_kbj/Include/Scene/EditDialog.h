#pragma once
#include "../GameInfo.h"

enum class ETile_Brush
{
	Frame,
	Option
};

class CEditDialog
{
private:
	friend class CScene_edit;
	class CScene_edit* m_scene;
	CSharedPtr<class CTexture>	m_SelectTexture;
	std::vector<std::vector<AnimationFrameData>>	m_vecTextureFrame;
	HWND	m_hDlg;
	HWND	m_hTextureListBox;
	HWND	m_hTextureFrameListBox;
	HWND	m_hBrushTypeCombo;
	HWND	m_hOptionCombo;
	HWND	m_hRenderCheckBox;
	HWND	m_hSideCollisionCheckBox;
	TCHAR	m_SelectTextureName[128];
	TCHAR	m_SelectTextureFrameName[128];
	ETile_Brush			m_BrushType;
	ETile_Option		m_SelectOption;
	int		m_SelectTextureIndex;
	int		m_SelectTextureFrameIndex;
	CEditDialog();
	~CEditDialog();
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
public:
	class CTexture* GetSelectTexture()	const
	{
		return m_SelectTexture;
	}
	ETile_Brush GetBrushType()	const
	{
		return m_BrushType;
	}
	ETile_Option GetSelectOption()	const
	{
		return m_SelectOption;
	}
	const AnimationFrameData* GetTileFrameData();	const

	bool GetCheckRender()	const
	{
		return SendMessage(m_hRenderCheckBox, BM_GETCHECK, 0, 0) == BST_CHECKED;
	}
	bool GetCheckSideCollision()	const
	{
		return SendMessage(m_hSideCollisionCheckBox, BM_GETCHECK, 0, 0) == BST_CHECKED;
	}
	bool Init();
	void CreateTileMap();
	void LoadTexture();
	void SelectTexture();
	void CreateAll();
	void AddFrame();
	void SelectFrame();
	void SelectBrushType();
	void SelectOption();
	void Save();
	void Load();
	void LoadTextureBack();
};

