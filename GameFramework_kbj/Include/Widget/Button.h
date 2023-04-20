#pragma once
#include "Widget.h"
class CButton : public CWidget
{
protected:
	friend class CWidgetComponent;
	friend class CWidgetWindow;
	CSharedPtr<class CTexture>  m_texture;
	CSharedPtr<class CSound>    m_stateSound[(int)EButton_Sound_State::Max];
	AnimationFrameData      m_stateData[(int)EButton_State::Max];
	EButton_State           m_buttonState;
	std::function<void()>   m_callback[(int)EButton_Sound_State::Max];
	CButton();
	CButton(const CButton& widget);
	virtual ~CButton();
public:
	void SetTexture(const std::string& name, const TCHAR* fileName,const std::string& pathName = TEXTURE_PATH);
	void SetTextureFullPath(const std::string& name, const TCHAR* fullPath);
	bool SetColorKey(unsigned char r, unsigned char g, unsigned char b, int index = 0);
#ifdef UNICODE
	void SetTexture(const std::string& name, const std::vector<std::wstring>& vecFileName,const std::string& pathName = TEXTURE_PATH);
	void SetTextureFullPath(const std::string& name, const std::vector<std::wstring>& vecFullPath);
#else
	void SetTexture(const std::string& name, const std::vector<std::string>& vecFileName,const std::string& pathName = TEXTURE_PATH);
	void SetTextureFullPath(const std::string& name, const std::vector<std::string>& vecFullPath);
#endif
	void SetButtonStateData(EButton_State state, const Vector2& start, const Vector2& end);
	void EnableButton(bool enable)
	{
		m_buttonState = enable ? EButton_State::Normal : EButton_State::Disable;
	}
	void SetSound(EButton_Sound_State state, const std::string& name);
	virtual bool Init();
	virtual void Update(float deltaTime);
	virtual void PostUpdate(float deltaTime);
	virtual void Render(HDC hDC, float deltaTime);
	virtual void Render(HDC hDC, const Vector2& pos, float deltaTime);
	virtual void CollisionMouseHoveredCallback(const Vector2& pos);
	virtual void CollisionMouseReleaseCallback();
	template <typename T>
	void SetCallback(EButton_Sound_State state, T* obj, void(T::* func)())
	{
		m_callback[(int)state] = std::bind(func, obj);
	}
};

