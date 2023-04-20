#pragma once
#include "../GameObject/GameObject.h"

class CCamera
{
private:
	friend class CScene;
	Vector2	m_pos;						 // 카메라 위치
	Vector2	m_resolution;				 // 윈도우 창의 해상도
	Vector2	m_worldResolution;			 // 전체 월드의 해상도
	CSharedPtr<CGameObject>	m_target;	 // 카메라가 따라다닐 타겟
	Vector2	m_targetOffset;				 // 타겟으로부터 얼마나 떨어져 있을지
	Vector2	m_targetPivot;				 // 타겟이 화면에서 스크롤링 될때의 비율
	CCamera();
	~CCamera();
public:
	Vector2 GetPos()	const
	{
		return m_pos;
	}
	Vector2 GetResolution()	const
	{
		return m_resolution;
	}
	Vector2 GetWorldResolution()	const
	{
		return m_worldResolution;
	}
	CGameObject* GetTarget()	const
	{
		return m_target;
	}
	Vector2 GetTargetOffset()	const
	{
		return m_targetOffset;
	}
	Vector2 GetTargetPivot()	const
	{
		return m_targetPivot;
	}
	void SetPos(const Vector2& pos)
	{
		m_pos = pos;
	}
	void SetPos(float x, float y)
	{
		m_pos = Vector2(x, y);
	}
	void SetResolution(const Vector2& resolution)
	{
		m_resolution = resolution;
	}
	void SetResolution(float x, float y)
	{
		m_resolution = Vector2(x, y);
	}
	void SetWorldResolution(const Vector2& worldResolution)
	{
		m_worldResolution = worldResolution;
	}
	void SetWorldResolution(float x, float y)
	{
		m_worldResolution = Vector2(x, y);
	}
	void SetTarget(CGameObject* target)
	{
		m_target = target;
	}
	void SetTargetOffset(const Vector2& targetOffset)
	{
		m_targetOffset = targetOffset;
	}
	void SetTargetOffset(float x, float y)
	{
		m_targetOffset = Vector2(x, y);
	}
	void SetTargetPivot(const Vector2& targetPivot)
	{
		m_targetPivot = targetPivot;
	}
	void SetTargetPivot(float x, float y)
	{
		m_targetPivot = Vector2(x, y);
	}
	void Update(float deltaTime);
};

