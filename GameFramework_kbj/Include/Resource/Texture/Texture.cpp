#include "Texture.h"
#include "../../PathManager.h"
#include "../../GameManager.h"

CTexture::CTexture()
	:m_type(ETexture_Type::Sprite)
{
	SetTypeID<CTexture>();
}

CTexture::~CTexture()
{
	size_t	size = m_vecImageInfo.size();
	for (size_t i = 0; i < size; ++i)
	{
		SAFE_DELETE(m_vecImageInfo[i]);
	}
}

bool CTexture::LoadTexture(ImageInfo* info, const TCHAR* fileName, const std::string& pathName)
{
	const PathInfo* path = CPathManager::GetInst()->FindPath(pathName);
	TCHAR	fullPath[MAX_PATH] = {};
	if (path)
	{
		lstrcpy(fullPath, path->path);
	}
	lstrcat(fullPath, fileName);
	bool result = LoadTextureFullPath(info, fullPath);
	if (result)
	{
		lstrcpy(m_vecImageInfo.back()->fileName, fileName);
		m_vecImageInfo.back()->pathName = pathName;
	}
	return result;
}

bool CTexture::LoadTextureFullPath(ImageInfo* info, const TCHAR* fullPath)
{
	HDC	hDC = CreateCompatibleDC(CGameManager::GetInst()->GetWindowDC());
	HBITMAP	hBmp = (HBITMAP)LoadImage(CGameManager::GetInst()->GetWindowInstance(),fullPath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	if (!hBmp)
	{
		return false;
	}
	HBITMAP hPrevBmp = (HBITMAP)SelectObject(hDC, hBmp);
	BITMAP	bmpInfo;
	GetObject(hBmp, sizeof(BITMAP), &bmpInfo);
	info->hMemDC = hDC;
	info->hBmp = hBmp;
	info->hPrevBmp = hPrevBmp;
	info->bmpInfo = bmpInfo;
	lstrcpy(info->fullPath, fullPath);
	return true;
}

void CTexture::Save(FILE* file)
{
	CRef::Save(file);
	fwrite(&m_type, sizeof(ETexture_Type), 1, file);
	int	count = (int)m_vecImageInfo.size();
	fwrite(&count, sizeof(int), 1, file);
	TCHAR	folderName[8] = {};
	lstrcpy(folderName, TEXT("Texture"));
	int folderCount = 0;
	for (int i = 0; i < count; ++i)
	{
		fwrite(&m_vecImageInfo[i]->enableColorKey, sizeof(bool), 1, file);
		fwrite(&m_vecImageInfo[i]->colorKey, sizeof(COLORREF), 1, file);
		if (lstrlen(m_vecImageInfo[i]->fileName) == 0)
		{
			int	length = lstrlen(m_vecImageInfo[i]->fullPath);
			for (int j = length - 1; j >= 0; --j)
			{
				if ((m_vecImageInfo[i]->fullPath[j] == '/' || m_vecImageInfo[i]->fullPath[j] == '\\'))
				{
					bool	find = true;
					for (int k = 0; k < 7; ++k)
					{
						if (folderName[6 - k] != m_vecImageInfo[i]->fullPath[j - k - 1])
						{
							find = false;
							break;
						}
					}
					if (find)
					{
						lstrcpy(m_vecImageInfo[i]->fileName, &m_vecImageInfo[i]->fullPath[j + 1]);
					}
					else if(folderCount != 2)
					{
						++folderCount;
						continue;
					}
					break;
				}
			}
			m_vecImageInfo[i]->pathName = TEXTURE_PATH;
		}
		fwrite(&m_vecImageInfo[i]->fileName, sizeof(TCHAR), MAX_PATH, file);
		fwrite(&m_vecImageInfo[i]->fullPath, sizeof(TCHAR), MAX_PATH, file);
		int length = (int)m_vecImageInfo[i]->pathName.length();
		fwrite(&length, sizeof(int), 1, file);
		fwrite(m_vecImageInfo[i]->pathName.c_str(), sizeof(char), length, file);
	}
}

void CTexture::Load(FILE* file)
{
	CRef::Load(file);
	fread(&m_type, sizeof(ETexture_Type), 1, file);
	int	count = 0;
	fread(&count, sizeof(int), 1, file);
	for (int i = 0; i < count; ++i)
	{
		ImageInfo* info = new ImageInfo;
		m_vecImageInfo.push_back(info);
		fread(&info->enableColorKey, sizeof(bool), 1, file);
		fread(&info->colorKey, sizeof(COLORREF), 1, file);
		fread(&info->fileName, sizeof(TCHAR), MAX_PATH, file);
		fread(&info->fullPath, sizeof(TCHAR), MAX_PATH, file);
		int length = 0;
		fread(&length, sizeof(int), 1, file);
		char	pathName[256] = {};
		assert(length > sizeof(char));
		fread(pathName, sizeof(char), length, file);
		info->pathName = pathName;
	}
	if (m_vecImageInfo.size() == 1)
	{
		if (lstrlen(m_vecImageInfo[0]->fileName) > 0)
		{
			LoadTexture(m_vecImageInfo[0], m_vecImageInfo[0]->fileName, m_vecImageInfo[0]->pathName);
		}
		else
		{
			LoadTextureFullPath(m_vecImageInfo[0], m_vecImageInfo[0]->fullPath);
		}
	}
	else
	{
		if (lstrlen(m_vecImageInfo[0]->fileName) > 0)
		{
			std::vector<std::wstring>	vecFileName;
			size_t	size = m_vecImageInfo.size();
			for (size_t i = 0; i < size; ++i)
			{
				vecFileName.push_back(m_vecImageInfo[i]->fileName);
			}
			LoadTexture(&m_vecImageInfo, vecFileName, m_vecImageInfo[0]->pathName);
		}
		else
		{
			std::vector<std::wstring>	vecFileName;
			size_t	size = m_vecImageInfo.size();
			for (size_t i = 0; i < size; ++i)
			{
				vecFileName.push_back(m_vecImageInfo[i]->fullPath);
			}
			LoadTextureFullPath(&m_vecImageInfo, vecFileName);
		}
	}
}

bool CTexture::LoadTexture(const TCHAR* fileName, const std::string& pathName)
{
	const PathInfo* path = CPathManager::GetInst()->FindPath(pathName);
	TCHAR	fullPath[MAX_PATH] = {};
	if (path)
	{
		lstrcpy(fullPath, path->path);
	}
	lstrcat(fullPath, fileName);
	bool result = LoadTextureFullPath(fullPath);
	if (result)
	{
		lstrcpy(m_vecImageInfo.back()->fileName, fileName);
		m_vecImageInfo.back()->pathName = pathName;
	}
	return result;
}

bool CTexture::LoadTextureFullPath(const TCHAR* fullPath)
{
	HDC	hDC = CreateCompatibleDC(CGameManager::GetInst()->GetWindowDC());
	HBITMAP	hBmp = (HBITMAP)LoadImage(CGameManager::GetInst()->GetWindowInstance(),fullPath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	if (!hBmp)
	{
		return false;
	}
	HBITMAP hPrevBmp = (HBITMAP)SelectObject(hDC, hBmp);
	BITMAP	bmpInfo;
	GetObject(hBmp, sizeof(BITMAP), &bmpInfo);
	ImageInfo* info = new ImageInfo;
	info->hMemDC = hDC;
	info->hBmp = hBmp;
	info->hPrevBmp = hPrevBmp;
	info->bmpInfo = bmpInfo;
	lstrcpy(info->fullPath, fullPath);
	m_vecImageInfo.push_back(info);
	return true;
}
#ifdef UNICODE
bool CTexture::LoadTexture(std::vector<ImageInfo*>* vecInfo, const std::vector<std::wstring>& vecFileName,
	const std::string& pathName)
{
	m_type = ETexture_Type::Frame;
	const PathInfo* path = CPathManager::GetInst()->FindPath(pathName);
	std::vector<std::wstring>	vecFullPath;
	size_t	size = vecFileName.size();
	vecFullPath.resize(size);
	for (size_t i = 0; i < size; ++i)
	{
		if (path)
		{
			vecFullPath[i] = path->path;
		}
		vecFullPath[i] += vecFileName[i];
	}
	bool result = LoadTextureFullPath(vecInfo, vecFullPath);
	if (result)
	{
		for (size_t i = 0; i < size; ++i)
		{
			lstrcpy(m_vecImageInfo[i]->fileName, vecFileName[i].c_str());
			m_vecImageInfo[i]->pathName = pathName;
		}
	}
	return result;
}
bool CTexture::LoadTextureFullPath(std::vector<ImageInfo*>* vecInfo, const std::vector<std::wstring>& vecFullPath)
{
	m_type = ETexture_Type::Frame;
	size_t	size = vecFullPath.size();
	for (size_t i = 0; i < size; ++i)
	{
		HDC	hDC = CreateCompatibleDC(CGameManager::GetInst()->GetWindowDC());
		HBITMAP	hBmp = (HBITMAP)LoadImage(CGameManager::GetInst()->GetWindowInstance(),
			vecFullPath[i].c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		if (!hBmp)
		{
			return false;
		}
		HBITMAP hPrevBmp = (HBITMAP)SelectObject(hDC, hBmp);
		BITMAP	bmpInfo;
		GetObject(hBmp, sizeof(BITMAP), &bmpInfo);
		ImageInfo* info = *(vecInfo->begin() + i);
		info->hMemDC = hDC;
		info->hBmp = hBmp;
		info->hPrevBmp = hPrevBmp;
		info->bmpInfo = bmpInfo;
		lstrcpy(info->fullPath, vecFullPath[i].c_str());
	}
	return true;
}
bool CTexture::LoadTexture(const std::vector<std::wstring>& vecFileName, const std::string& pathName)
{
	m_type = ETexture_Type::Frame;
	const PathInfo* path = CPathManager::GetInst()->FindPath(pathName);
	std::vector<std::wstring>	vecFullPath;
	size_t	size = vecFileName.size();
	vecFullPath.resize(size);
	for (size_t i = 0; i < size; ++i)
	{
		if (path)
		{
			vecFullPath[i] = path->path;
		}
		vecFullPath[i] += vecFileName[i];
	}
	bool result = LoadTextureFullPath(vecFullPath);
	if (result)
	{
		for (size_t i = 0; i < size; ++i)
		{
			lstrcpy(m_vecImageInfo[i]->fileName, vecFileName[i].c_str());
			m_vecImageInfo[i]->pathName = pathName;
		}
	}
	return result;
}

bool CTexture::LoadTextureFullPath(const std::vector<std::wstring>& vecFullPath)
{
	m_type = ETexture_Type::Frame;
	size_t	size = vecFullPath.size();
	for (size_t i = 0; i < size; ++i)
	{
		HDC	hDC = CreateCompatibleDC(CGameManager::GetInst()->GetWindowDC());
		HBITMAP	hBmp = (HBITMAP)LoadImage(CGameManager::GetInst()->GetWindowInstance(),
			vecFullPath[i].c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		if (!hBmp)
		{
			return false;
		}
		HBITMAP hPrevBmp = (HBITMAP)SelectObject(hDC, hBmp);
		BITMAP	bmpInfo;
		GetObject(hBmp, sizeof(BITMAP), &bmpInfo);
		ImageInfo* info = new ImageInfo;
		info->hMemDC = hDC;
		info->hBmp = hBmp;
		info->hPrevBmp = hPrevBmp;
		info->bmpInfo = bmpInfo;
		lstrcpy(info->fullPath, vecFullPath[i].c_str());
		m_vecImageInfo.push_back(info);
	}
	return true;
}
#else
bool CTexture::LoadTexture(std::vector<ImageInfo*>* vecInfo, const std::vector<std::string>& vecFileName,
	const std::string& pathName)
{
	m_type = ETexture_Type::Frame;
	const PathInfo* path = CPathManager::GetInst()->FindPath(pathName);
	std::vector<std::string>	vecFullPath;
	size_t	size = vecFileName.size();
	vecFullPath.resize(size);
	for (size_t i = 0; i < size; ++i)
	{
		if (path)
		{
			vecFullPath[i] = path->path;
		}
		vecFullPath[i] += vecFileName[i];
	}
	return LoadTextureFullPath(vecInfo, vecFullPath);
}
bool CTexture::LoadTextureFullPath(std::vector<ImageInfo*>* vecInfo, const std::vector<std::string>& vecFullPath)
{
	m_type = ETexture_Type::Frame;
	size_t	size = vecFullPath.size();
	for (size_t i = 0; i < size; ++i)
	{
		HDC	hDC = CreateCompatibleDC(CGameManager::GetInst()->GetWindowDC());
		HBITMAP	hBmp = (HBITMAP)LoadImage(CGameManager::GetInst()->GetWindowInstance(),
			vecFullPath[i].c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		if (!hBmp)
		{
			return false;
		}
		HBITMAP hPrevBmp = (HBITMAP)SelectObject(hDC, hBmp);
		BITMAP	bmpInfo;
		GetObject(hBmp, sizeof(BITMAP), &bmpInfo);
		ImageInfo* info = *(vecInfo->begin() + i);
		info->hMemDC = hDC;
		info->hBmp = hBmp;
		info->hPrevBmp = hPrevBmp;
		info->bmpInfo = bmpInfo;
	}
	return true;
}
bool CTexture::LoadTexture(const std::vector<std::string>& vecFileName,const std::string& pathName)
{
	m_type = ETexture_Type::Frame;
	const PathInfo* path = CPathManager::GetInst()->FindPath(pathName);
	std::vector<std::string>	vecFullPath;
	size_t	size = vecFileName.size();
	vecFullPath.resize(size);
	for (size_t i = 0; i < size; ++i)
	{
		if (path)
		{
			vecFullPath[i] = path->path;
		}
		vecFullPath[i] += vecFileName[i];
	}
	return LoadTextureFullPath(vecFullPath);
}
bool CTexture::LoadTextureFullPath(const std::vector<std::string>& vecFullPath)
{
	m_type = ETexture_Type::Frame;
	size_t	size = vecFullPath.size();
	for (size_t i = 0; i < size; ++i)
	{
		HDC	hDC = CreateCompatibleDC(CGameManager::GetInst()->GetWindowDC());
		HBITMAP	hBmp = (HBITMAP)LoadImage(CGameManager::GetInst()->GetWindowInstance(),
			vecFullPath[i].c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		if (!hBmp)
		{
			return false;
		}
		HBITMAP hPrevBmp = (HBITMAP)SelectObject(hDC, hBmp);
		BITMAP	bmpInfo;
		GetObject(hBmp, sizeof(BITMAP), &bmpInfo);
		ImageInfo* info = new ImageInfo;
		info->hMemDC = hDC;
		info->hBmp = hBmp;
		info->hPrevBmp = hPrevBmp;
		info->bmpInfo = bmpInfo;
		m_vecImageInfo.push_back(info);
	}
	return true;
}
#endif // UNICODE
