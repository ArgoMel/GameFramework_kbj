#pragma once
#include "GameInfo.h"
#include "SingletonMacro.h"

class CGameManager
{
	DECLARE_SINGLE(CGameManager)
private:
	class CTimer* m_timer;
	HINSTANCE		m_hInst;
	HWND			m_hWnd;
	HDC				m_hDC;
	HDC				m_hBackDC;
	HBITMAP			m_hBackBmp;
	HBITMAP			m_hBackPrevBmp;
	HBRUSH			m_brush[(int)EBrush_Type::Max];
	HPEN			m_pen[(int)EBrush_Type::Max];
	Resolution		m_RS;
	float			m_frameLimitTime;
	float			m_deltaTime;
	float			m_timeScale;	// 글로벌 타임 재생 배율(게임 전체의 시간을 조절할때 씀)
	bool			m_EditMode;
	static bool		m_Loop;
	void Logic();
	void Input(float deltaTime);
	bool Update(float deltaTime);
	bool PostUpdate(float deltaTime);
	void Collision(float deltaTime);
	void Render(float deltaTime);
	void Register();
	bool Create();
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
public:
	HINSTANCE GetWindowInstance()	const
	{
		return m_hInst;
	}
	HWND GetWindowHandle()	const
	{
		return m_hWnd;
	}
	HDC GetWindowDC()	const
	{
		return m_hDC;
	}
	HBRUSH GetBrush(EBrush_Type type)	const
	{
		return m_brush[(int)type];
	}
	HPEN GetPen(EBrush_Type type)	const
	{
		return m_pen[(int)type];
	}
	Resolution GetResolution()	const
	{
		return m_RS;
	}
	float GetDeltaTime()	const
	{
		return m_deltaTime;
	}
	float GetTimeScale()	const
	{
		return m_timeScale;
	}
	bool GetEditMode()	const
	{
		return m_EditMode;
	}
	float GetFPS()	const;
	void SetTimeScale(float scale)
	{
		m_timeScale = scale;
	}
	void SetEditMode(bool mode)
	{
		m_EditMode = mode;
	}
	void Exit();
	bool Init(HINSTANCE hInst);
	int Run();
};