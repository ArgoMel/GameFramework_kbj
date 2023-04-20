#pragma once
#include "../GameObject/GameObject.h"

class CCamera
{
private:
	friend class CScene;
	Vector2	m_pos;						 // ī�޶� ��ġ
	Vector2	m_resolution;				 // ������ â�� �ػ�
	Vector2	m_worldResolution;			 // ��ü ������ �ػ�
	CSharedPtr<CGameObject>	m_target;	 // ī�޶� ����ٴ� Ÿ��
	Vector2	m_targetOffset;				 // Ÿ�����κ��� �󸶳� ������ ������
	Vector2	m_targetPivot;				 // Ÿ���� ȭ�鿡�� ��ũ�Ѹ� �ɶ��� ����
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

