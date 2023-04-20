#include "Camera.h"
#include "../Input.h"

CCamera::CCamera()
{
}

CCamera::~CCamera()
{
}

void CCamera::Update(float deltaTime)
{
	if (m_target)
	{
		if (!m_target->GetActive())
		{
			m_target = nullptr;
		}
		else
		{
			m_pos = m_target->GetPos() - m_targetPivot * m_resolution + m_targetOffset;
		}
	}
	// 카메라가 월드를 벗어나지 못하도록 만들어준다.
	if (m_pos.x < 0.f)
	{
		m_pos.x = 0.f;
	}
	else if (m_pos.x + m_resolution.x > m_worldResolution.x)
	{
		m_pos.x = m_worldResolution.x - m_resolution.x;
	}
	if (m_pos.y < 0.f)
	{
		m_pos.y = 0.f;
	}
	else if (m_pos.y + m_resolution.y > m_worldResolution.y)
	{
		m_pos.y = m_worldResolution.y - m_resolution.y;
	}
	CInput::GetInst()->ComputeWorldMousePos(m_pos);
}
