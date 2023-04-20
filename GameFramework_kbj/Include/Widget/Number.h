#pragma once
#include "Widget.h"
class CNumber : public CWidget
{
protected:
	friend class CWidgetComponent;
	friend class CWidgetWindow;
	CSharedPtr<class CTexture>  m_texture;
	std::vector<int>			m_vecNumber;
	int							m_number;
	CNumber();
	CNumber(const CNumber& widget);
	virtual ~CNumber();
public:
	void SetNumber(int number)
	{
		m_number = number;
	}
	void AddNumber(int number)
	{
		m_number += number;
	}
	void SetTexture(const std::string& name, const TCHAR* fileName,const std::string& pathName = TEXTURE_PATH);
	void SetTextureFullPath(const std::string& name, const TCHAR* fullPath);
	void SetColorKey(unsigned char r, unsigned char g, unsigned char b);
	virtual bool Init();
	virtual void Update(float deltaTime);
	virtual void PostUpdate(float deltaTime);
	virtual void Render(HDC hDC, float deltaTime);
	virtual void Render(HDC hDC, const Vector2& pos, float deltaTime);
#ifdef UNICODE
	void SetTexture(const std::string& name, const std::vector<std::wstring>& vecFileName,const std::string& pathName = TEXTURE_PATH);
	void SetTextureFullPath(const std::string& name, const std::vector<std::wstring>& vecFullPath);
#else
	void SetTexture(const std::string& name, const std::vector<std::string>& vecFileName,const std::string& pathName = TEXTURE_PATH);
	void SetTextureFullPath(const std::string& name, const std::vector<std::string>& vecFullPath);
#endif
};

