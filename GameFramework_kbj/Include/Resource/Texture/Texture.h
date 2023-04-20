#pragma once
#include "../../Ref.h"
struct ImageInfo
{
    HDC     hMemDC;
    HBITMAP hBmp;
    HBITMAP hPrevBmp;
    BITMAP  bmpInfo;
    COLORREF colorKey;
    bool     enableColorKey;
    TCHAR   fileName[MAX_PATH];
    TCHAR   fullPath[MAX_PATH];
    std::string pathName;

    ImageInfo() 
        : hMemDC(0)
        , hBmp(0)
        , hPrevBmp(0)
        , bmpInfo{}
        , colorKey(RGB(255, 0, 255))
        , enableColorKey(false)
        , fileName{}
        , fullPath{}
    {}
    ~ImageInfo()
    {
        SelectObject(hMemDC, hPrevBmp);
        DeleteObject(hBmp);
        DeleteDC(hMemDC);
    }
};

class CTexture :public CRef
{
private:
	friend class CTextureManager;
    ETexture_Type   m_type;
    std::vector<ImageInfo*> m_vecImageInfo;
	CTexture();
	~CTexture();
    bool LoadTexture(ImageInfo* info, const TCHAR* fileName,const std::string& pathName = TEXTURE_PATH);
    bool LoadTextureFullPath(ImageInfo* info, const TCHAR* fullPath);
#ifdef UNICODE
    bool LoadTexture(std::vector<ImageInfo*>* vecInfo, const std::vector<std::wstring>& vecFileName,
        const std::string& pathName = TEXTURE_PATH);
    bool LoadTextureFullPath(std::vector<ImageInfo*>* vecInfo, const std::vector<std::wstring>& vecFullPath);
#else
    bool LoadTexture(std::vector<ImageInfo*>* vecInfo, const std::vector<std::string>& vecFileName,
        const std::string& pathName = TEXTURE_PATH);
    bool LoadTextureFullPath(std::vector<ImageInfo*>* vecInfo, const std::vector<std::string>& vecFullPath);
#endif // UNICODE
public:
    ETexture_Type GetTextureType()  const
    {
        return m_type;
    }
    HDC GetDC(int index = 0) const
    {
        return m_vecImageInfo[index]->hMemDC;
    }
    int GetWidth(int index = 0)  const
    {
        return (int)m_vecImageInfo[index]->bmpInfo.bmWidth;
    }
    int GetHeight(int index = 0)  const
    {
        return (int)m_vecImageInfo[index]->bmpInfo.bmHeight;
    }
    void SetColorKey(unsigned char r, unsigned char g, unsigned char b,int index = 0)
    {
        m_vecImageInfo[index]->colorKey = RGB(r, g, b);
        m_vecImageInfo[index]->enableColorKey = true;
    }
    void SetColorKeyAll(unsigned char r, unsigned char g, unsigned char b)
    {
        size_t  size = m_vecImageInfo.size();
        for (size_t i = 0; i < size; ++i)
        {
            m_vecImageInfo[i]->colorKey = RGB(r, g, b);
            m_vecImageInfo[i]->enableColorKey = true;
        }
    }
    bool GetEnableColorKey(int index = 0)    const
    {
        return m_vecImageInfo[index]->enableColorKey;
    }
    COLORREF GetColorKey(int index = 0)    const
    {
        return m_vecImageInfo[index]->colorKey;
    }
    void Save(FILE* file);
    void Load(FILE* file);
	bool LoadTexture(const TCHAR* fileName,const std::string& pathName = TEXTURE_PATH);
    bool LoadTextureFullPath(const TCHAR* fullPath);
#ifdef UNICODE
    bool LoadTexture(const std::vector<std::wstring>& vecFileName,const std::string& pathName = TEXTURE_PATH);
    bool LoadTextureFullPath(const std::vector<std::wstring>& vecFullPath);
#else
    bool LoadTexture(const std::vector<std::string>& vecFileName,const std::string& pathName = TEXTURE_PATH);
    bool LoadTextureFullPath(const std::vector<std::string>& vecFullPath);
#endif // UNICODE
};

