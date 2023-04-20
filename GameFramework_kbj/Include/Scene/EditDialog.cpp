#include "EditDialog.h"
#include "../GameManager.h"
#include "../resource.h"
#include "Scene_edit.h"
#include "../PathManager.h"
#include "SceneResource.h"
#include "../Resource/Texture/Texture.h"
#include "../GameObject/TileMap.h"

CEditDialog* g_Dlg = nullptr;
CEditDialog::CEditDialog()
	: m_SelectTextureName{}
	, m_SelectTextureFrameName{}
	, m_scene(nullptr)
{
	g_Dlg = this;
	m_SelectTextureIndex = -1;
	m_SelectTextureFrameIndex = -1;
	m_BrushType = ETile_Brush::Frame;
	m_SelectOption = ETile_Option::Normal;
	m_hDlg = CreateDialog(CGameManager::GetInst()->GetWindowInstance(), MAKEINTRESOURCE(IDD_DIALOG_EDIT),
		CGameManager::GetInst()->GetWindowHandle(), CEditDialog::WndProc);
	m_hTextureListBox = GetDlgItem(m_hDlg, IDC_LIST_TEXTURE);
	m_hTextureFrameListBox = GetDlgItem(m_hDlg, IDC_LIST_TEXTURE_FRAME);
	m_hBrushTypeCombo = GetDlgItem(m_hDlg, IDC_COMBO_BRUSH_TYPE);
	m_hOptionCombo = GetDlgItem(m_hDlg, IDC_COMBO_OPTION);
	m_hRenderCheckBox = GetDlgItem(m_hDlg, IDC_CHECK_RENDER);
	m_hSideCollisionCheckBox = GetDlgItem(m_hDlg, IDC_CHECK_SIDECOLLISION);
}

CEditDialog::~CEditDialog()
{
}

LRESULT CEditDialog::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CLOSE:
		DestroyWindow(hWnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDC_BUTTON_CREATE_TILEMAP:
			g_Dlg->CreateTileMap();
			break;
		case IDC_BUTTON_LOADTEXTURE:
			g_Dlg->LoadTexture();
			break;
		case IDC_BUTTON_ADD_FRAME:
			g_Dlg->AddFrame();
			break;
		case IDC_BUTTON_LOADTEXTURE_BACK:
			g_Dlg->LoadTextureBack();
			break;
		case IDC_BUTTON_CREATE_ALL:
			g_Dlg->CreateAll();
			break;
		case IDC_LIST_TEXTURE:
			switch (HIWORD(wParam))
			{
			case LBN_SELCHANGE:
				g_Dlg->SelectTexture();
				break;
			}
			break;
		case IDC_LIST_TEXTURE_FRAME:
			switch (HIWORD(wParam))
			{
			case LBN_SELCHANGE:
				g_Dlg->SelectFrame();
				break;
			}
			break;
		case IDC_COMBO_BRUSH_TYPE:
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
				g_Dlg->SelectBrushType();
				break;
			}
			break;
		case IDC_COMBO_OPTION:
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
				g_Dlg->SelectOption();
				break;
			}
			break;
		case IDC_BUTTON_SAVE:
			g_Dlg->Save();
			break;
		case IDC_BUTTON_LOAD:
			g_Dlg->Load();
			break;
		case IDCANCEL:
			DestroyWindow(hWnd);
			break;
		}
		break;
	default:
		break;
	}
	return 0;
}

const AnimationFrameData* CEditDialog::GetTileFrameData()
{
	if (m_SelectTextureIndex == -1 || m_SelectTextureFrameIndex == -1)
	{
		return nullptr;
	}
	memset(m_SelectTextureFrameName, 0, sizeof(TCHAR) * 128);
	SendMessage(m_hTextureFrameListBox, LB_GETTEXT, m_SelectTextureFrameIndex, (LPARAM)m_SelectTextureFrameName);
	SendMessage(m_hTextureFrameListBox, LB_GETTEXT, m_SelectTextureFrameIndex, (LPARAM)m_SelectTextureFrameName);
	return &m_vecTextureFrame[m_SelectTextureIndex][_ttoi(m_SelectTextureFrameName)];
}

bool CEditDialog::Init()
{
	CGameManager::GetInst()->SetEditMode(true);
	ShowWindow(m_hDlg, SW_SHOW);
	SetDlgItemInt(m_hDlg, IDC_EDIT_COUNTX, 17, TRUE);
	SetDlgItemInt(m_hDlg, IDC_EDIT_COUNTY, 15, TRUE);
	SetDlgItemInt(m_hDlg, IDC_EDIT_SIZEX, 52, TRUE);
	SetDlgItemInt(m_hDlg, IDC_EDIT_SIZEY, 52, TRUE);

	SendMessage(m_hBrushTypeCombo, CB_ADDSTRING, 0, (LPARAM)TEXT("Frame"));
	SendMessage(m_hBrushTypeCombo, CB_ADDSTRING, 0, (LPARAM)TEXT("Option"));
	SendMessage(m_hOptionCombo, CB_ADDSTRING, 0, (LPARAM)TEXT("Normal"));
	SendMessage(m_hOptionCombo, CB_ADDSTRING, 0, (LPARAM)TEXT("ImpossibleToMove"));
	SendMessage(m_hOptionCombo, CB_ADDSTRING, 0, (LPARAM)TEXT("Slippery"));
	SendMessage(m_hBrushTypeCombo, CB_SETCURSEL, 0, 0);
	SendMessage(m_hOptionCombo, CB_SETCURSEL, 0, 0);
	SendMessage(m_hRenderCheckBox, BM_SETCHECK, (WPARAM)BST_CHECKED, 0);
	return true;
}

void CEditDialog::CreateTileMap()
{
	BOOL	transfer = FALSE;
	int	countX = GetDlgItemInt(m_hDlg, IDC_EDIT_COUNTX, &transfer, TRUE);
	int	countY = GetDlgItemInt(m_hDlg, IDC_EDIT_COUNTY, &transfer, TRUE);
	int	sizeX = GetDlgItemInt(m_hDlg, IDC_EDIT_SIZEX, &transfer, TRUE);
	int	sizeY = GetDlgItemInt(m_hDlg, IDC_EDIT_SIZEY, &transfer, TRUE);
	m_scene->CreateTileMap(countX, countY, sizeX, sizeY);
}

void CEditDialog::LoadTexture()
{
	TCHAR	filePath[MAX_PATH] = {};
	OPENFILENAME	openFile = {};
	openFile.lStructSize = sizeof(OPENFILENAME);
	openFile.hwndOwner = m_hDlg;
	openFile.lpstrFilter = TEXT("모든파일\0*.*\0BmpFile\0*.bmp");
	openFile.lpstrFile = filePath;	// FilePath 에 풀경로가 들어온다.
	openFile.nMaxFile = MAX_PATH;
	openFile.lpstrInitialDir = CPathManager::GetInst()->FindPath(TEXTURE_PATH)->path;

	if (GetOpenFileName(&openFile) != 0)
	{
		TCHAR	fileName[128] = {};
		_wsplitpath_s(filePath, nullptr, 0, nullptr, 0, fileName, 128, nullptr, 0);
		char	textureName[128] = {};
#ifdef UNICODE
		int	pathLength = WideCharToMultiByte(CP_ACP, 0, fileName, -1,0, 0, 0, 0);
		WideCharToMultiByte(CP_ACP, 0, fileName, -1,textureName, pathLength, 0, 0);
#else
		strcpy_s(textureName, fileName);
#endif // UNICODE
		SendMessage(m_hTextureListBox, LB_ADDSTRING, 0, (LPARAM)fileName);
		if (!m_scene->GetSceneResource()->LoadTextureFullPath(textureName, filePath))
		{
			return;
		}
		m_scene->GetSceneResource()->SetColorKey(textureName, 255, 0, 255);
		std::vector<AnimationFrameData>	vecData;
		m_vecTextureFrame.push_back(vecData);
	}
}

void CEditDialog::SelectTexture()
{
	m_SelectTextureIndex = (int)SendMessage(m_hTextureListBox, LB_GETCURSEL, 0, 0);
	if (m_SelectTextureIndex != -1)
	{
		memset(m_SelectTextureName, 0, sizeof(TCHAR) * 128);
		SendMessage(m_hTextureListBox, LB_GETTEXT, m_SelectTextureIndex, (LPARAM)m_SelectTextureName);
	}
	char	textureName[128] = {};
#ifdef UNICODE
	int	pathLength = WideCharToMultiByte(CP_ACP, 0, m_SelectTextureName, -1, 0, 0, 0, 0);
	WideCharToMultiByte(CP_ACP, 0, m_SelectTextureName, -1, textureName, pathLength, 0, 0);
#else
	strcpy_s(textureName, fileName);
#endif // UNICODE
	m_SelectTexture = m_scene->GetSceneResource()->FindTexture(textureName);
}

void CEditDialog::CreateAll()
{
	m_scene->SetTileTexture(m_SelectTexture);
	m_SelectTextureFrameIndex = -1;
}

void CEditDialog::AddFrame()
{
	if (m_SelectTextureIndex == -1)
	{
		return;
	}
	BOOL	transfer = FALSE;
	int	startX = GetDlgItemInt(m_hDlg, IDC_EDIT_STARTFRAMEX, &transfer, TRUE);
	int	startY = GetDlgItemInt(m_hDlg, IDC_EDIT_STARTFRAMEY, &transfer, TRUE);
	int	endX = GetDlgItemInt(m_hDlg, IDC_EDIT_ENDFRAMEX, &transfer, TRUE);
	int	endY = GetDlgItemInt(m_hDlg, IDC_EDIT_ENDFRAMEY, &transfer, TRUE);

	AnimationFrameData	data;
	data.start.x = (float)startX;
	data.start.y = (float)startY;
	data.end.x = (float)endX;
	data.end.y = (float)endY;

	TCHAR	listData[32] = {};
	wsprintf(listData, TEXT("%d"), (int)m_vecTextureFrame[m_SelectTextureIndex].size());
	SendMessage(m_hTextureFrameListBox, LB_ADDSTRING, 0, (LPARAM)listData);
	m_vecTextureFrame[m_SelectTextureIndex].push_back(data);
}

void CEditDialog::SelectFrame()
{
	if (m_SelectTextureIndex == -1)
	{
		return;
	}
	m_SelectTextureFrameIndex = (int)SendMessage(m_hTextureFrameListBox, LB_GETCURSEL, 0, 0);
	if (m_SelectTextureFrameIndex != -1)
	{
		memset(m_SelectTextureFrameName, 0, sizeof(TCHAR) * 128);
		SendMessage(m_hTextureFrameListBox, LB_GETTEXT, m_SelectTextureFrameIndex, (LPARAM)m_SelectTextureFrameName);
		AnimationFrameData	data = m_vecTextureFrame[m_SelectTextureIndex][_ttoi(m_SelectTextureFrameName)];
		SetDlgItemInt(m_hDlg, IDC_EDIT_STARTFRAMEX, (int)data.start.x, TRUE);
		SetDlgItemInt(m_hDlg, IDC_EDIT_STARTFRAMEY, (int)data.start.y, TRUE);
		SetDlgItemInt(m_hDlg, IDC_EDIT_ENDFRAMEX, (int)data.end.x, TRUE);
		SetDlgItemInt(m_hDlg, IDC_EDIT_ENDFRAMEY, (int)data.end.y, TRUE);
	}
}

void CEditDialog::SelectBrushType()
{
	m_BrushType = (ETile_Brush)SendMessage(m_hBrushTypeCombo, CB_GETCURSEL, 0, 0);
}

void CEditDialog::SelectOption()
{
	m_SelectOption = (ETile_Option)SendMessage(m_hOptionCombo, CB_GETCURSEL, 0, 0);
}

void CEditDialog::Save()
{
	if (!m_scene->GetTileMap())
	{
		return;
	}
	TCHAR	filePath[MAX_PATH] = {};
	OPENFILENAME	openFile = {};
	openFile.lStructSize = sizeof(OPENFILENAME);
	openFile.hwndOwner = m_hDlg;
	openFile.lpstrFilter = TEXT("모든파일\0*.*\0TileMapFile\0*.tmp");
	openFile.lpstrFile = filePath;	// FilePath 에 풀경로가 들어온다.
	openFile.nMaxFile = MAX_PATH;
	openFile.lpstrInitialDir = CPathManager::GetInst()->FindPath(TEXTURE_PATH)->path;

	if (GetSaveFileName(&openFile) != 0)
	{
		char	fullPath[MAX_PATH] = {};
#ifdef UNICODE
		int	pathLength = WideCharToMultiByte(CP_ACP, 0, filePath, -1,0, 0, 0, 0);
		WideCharToMultiByte(CP_ACP, 0, filePath, -1,fullPath, pathLength, 0, 0);
#else
		strcpy_s(fullPath, filePath);
#endif // UNICODE
		m_scene->GetTileMap()->SaveFullPath(fullPath);
	}
}

void CEditDialog::Load()
{
	TCHAR	filePath[MAX_PATH] = {};
	OPENFILENAME	openFile = {};
	openFile.lStructSize = sizeof(OPENFILENAME);
	openFile.hwndOwner = m_hDlg;
	openFile.lpstrFilter = TEXT("모든파일\0*.*\0TileMapFile\0*.tmp");
	openFile.lpstrFile = filePath;	// FilePath 에 풀경로가 들어온다.
	openFile.nMaxFile = MAX_PATH;
	openFile.lpstrInitialDir = CPathManager::GetInst()->FindPath(TEXTURE_PATH)->path;

	if (GetSaveFileName(&openFile) != 0)
	{
		char	fullPath[MAX_PATH] = {};
#ifdef UNICODE
		int	pathLength = WideCharToMultiByte(CP_ACP, 0, filePath, -1,0, 0, 0, 0);
		WideCharToMultiByte(CP_ACP, 0, filePath, -1,fullPath, pathLength, 0, 0);
#else
		strcpy_s(fullPath, filePath);
#endif // UNICODE
		m_scene->LoadTileMap(fullPath);
	}
}

void CEditDialog::LoadTextureBack()
{
	if (!m_scene->GetTileMap())
	{
		return;
	}
	TCHAR	filePath[MAX_PATH] = {};
	OPENFILENAME	openFile = {};
	openFile.lStructSize = sizeof(OPENFILENAME);
	openFile.hwndOwner = m_hDlg;
	openFile.lpstrFilter = TEXT("모든파일\0*.*\0BmpFile\0*.bmp");
	openFile.lpstrFile = filePath;	// FilePath 에 풀경로가 들어온다.
	openFile.nMaxFile = MAX_PATH;
	openFile.lpstrInitialDir = CPathManager::GetInst()->FindPath(TEXTURE_PATH)->path;

	if (GetOpenFileName(&openFile) != 0)
	{
		TCHAR	fileName[128] = {};
		_wsplitpath_s(filePath, nullptr, 0, nullptr, 0, fileName, 128, nullptr, 0);
		char	textureName[128] = {};
#ifdef UNICODE
		int	pathLength = WideCharToMultiByte(CP_ACP, 0, fileName, -1,0, 0, 0, 0);
		WideCharToMultiByte(CP_ACP, 0, fileName, -1,textureName, pathLength, 0, 0);
#else
		strcpy_s(textureName, fileName);
#endif // UNICODE
		m_scene->GetTileMap()->SetTextureFullPath(textureName, filePath);
		m_scene->GetTileMap()->SetColorKey(255, 0, 255);
	}
}
