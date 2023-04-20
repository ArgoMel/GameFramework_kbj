#include "Scene.h"
#include "../GameObject/GameObject.h"
#include "SceneResource.h"
#include "Camera.h"
#include "SceneCollision.h"
#include "../GameObject/TileMap.h"
#include "../GameObject/Sewer.h"
// 오브젝트->UI->마우스->카메라 순
CScene::CScene()
	: m_WallCount(0)
{
	m_resource = new CSceneResource;
	m_camera = new CCamera;
	m_collision = new CSceneCollision;
}

CScene::~CScene()
{
	for (int i = 0; i < (int)ERender_Layer::Max; ++i)
	{
		m_objList[i].clear();
	}
	SAFE_DELETE(m_collision);
	SAFE_DELETE(m_camera);
	SAFE_DELETE(m_resource);
}

bool CScene::SortY(const CSharedPtr<class CGameObject>& src, const CSharedPtr<class CGameObject>& dest)
{
	float	srcY = src->GetPos().y + (1.f - src->GetPivot().y) * src->GetSize().y;
	float	destY = dest->GetPos().y + (1.f - dest->GetPivot().y) * dest->GetSize().y;
	return srcY < destY;
}
bool CScene::SortYWidgetComponent(const CSharedPtr<class CWidgetComponent>& src, const CSharedPtr<class CWidgetComponent>& dest)
{
	return src->GetBottom() < dest->GetBottom();
}
bool CScene::SortWidget(const CSharedPtr<CWidgetWindow>& src, const CSharedPtr<CWidgetWindow>& dest)
{
	return src->GetZOrder() < dest->GetZOrder();
}
void CScene::SetTileMap(CTileMap* tileMap)
{
	m_TileMap = tileMap;
}
void CScene::SetPlayer(CGameObject* player)
{
	m_player = player;
}
std::list<CSharedPtr<CSewer>>::iterator CScene::SewerBegin()
{
	std::list<CSharedPtr<CSewer>>::iterator iter = m_listSewer.begin();
	return iter;
	//auto	iter = m_listSewer.begin();
}

std::list<CSharedPtr<CSewer>>::iterator CScene::SewerEnd()
{
	std::list<CSharedPtr<CSewer>>::iterator iterEnd = m_listSewer.end();
	return iterEnd;
}
bool CScene::Init()
{
    return true;
}
void CScene::Update(float deltaTime)
{
	//오브젝트
	for (int i = 0; i < (int)ERender_Layer::Max; ++i)
	{
		auto	iter = m_objList[i].begin();
		auto	iterEnd = m_objList[i].end();
		for (; iter != iterEnd;)
		{
			if (!(*iter)->m_Start)
			{
				(*iter)->Start();
			}
			if (!(*iter)->GetActive())
			{
				iter = m_objList[i].erase(iter);
				iterEnd = m_objList[i].end();
				continue;
			}
			else if (!(*iter)->GetEnable())
			{
				++iter;
				continue;
			}
			(*iter)->Update(deltaTime);
			++iter;
		}
	}
	//UI
	auto	iter1 = m_vecWidgetWindow.begin();
	auto	iter1End = m_vecWidgetWindow.end();
	for (; iter1 != iter1End;)
	{
		if (!(*iter1)->GetActive())
		{
			iter1 = m_vecWidgetWindow.erase(iter1);
			iter1End = m_vecWidgetWindow.end();
			continue;
		}
		else if (!(*iter1)->GetEnable())
		{
			++iter1;
			continue;
		}
		(*iter1)->Update(deltaTime);
		++iter1;
	}
	//카메라
	m_camera->Update(deltaTime);
}
void CScene::PostUpdate(float deltaTime)
{
	//오브젝트
	for (int i = 0; i < (int)ERender_Layer::Max; ++i)
	{
		auto	iter = m_objList[i].begin();
		auto	iterEnd = m_objList[i].end();
		for (; iter != iterEnd;)
		{
			if (!(*iter)->m_Start)
			{
				(*iter)->Start();
			}
			if (!(*iter)->GetActive())
			{
				iter = m_objList[i].erase(iter);
				iterEnd = m_objList[i].end();
				continue;
			}
			else if (!(*iter)->GetEnable())
			{
				++iter;
				continue;
			}
			(*iter)->PostUpdate(deltaTime);
			++iter;
		}
	}
	//UI
	auto	iter1 = m_vecWidgetWindow.begin();
	auto	iter1End = m_vecWidgetWindow.end();
	for (; iter1 != iter1End;)
	{
		if (!(*iter1)->GetActive())
		{
			iter1 = m_vecWidgetWindow.erase(iter1);
			iter1End = m_vecWidgetWindow.end();
			continue;
		}
		else if (!(*iter1)->GetEnable())
		{
			++iter1;
			continue;
		}
		(*iter1)->PostUpdate(deltaTime);
		++iter1;
	}
	iter1 = m_vecWidgetWindow.begin();
	iter1End = m_vecWidgetWindow.end();
	for (; iter1 != iter1End;)
	{
		if (!(*iter1)->GetActive())
		{
			iter1 = m_vecWidgetWindow.erase(iter1);
			iter1End = m_vecWidgetWindow.end();
			continue;
		}
		else if (!(*iter1)->GetEnable())
		{
			++iter1;
			continue;
		}
		m_collision->AddWidgetWindow(*iter1);
		++iter1;
	}
	//마우스
	m_collision->CollisionMouse(deltaTime);
	m_collision->Collision(deltaTime);
}
void CScene::Render(HDC hDC, float deltaTime)
{
	//오브젝트
	for (int i = 0; i < (int)ERender_Layer::Max; ++i)
	{
		m_objList[i].sort(SortY);
		auto	iter = m_objList[i].begin();
		auto	iterEnd = m_objList[i].end();
		for (; iter != iterEnd;)
		{
			if (!(*iter)->m_Start)
			{
				(*iter)->Start();
			}
			if (!(*iter)->GetActive())
			{
				iter = m_objList[i].erase(iter);
				iterEnd = m_objList[i].end();
				continue;
			}
			else if (!(*iter)->GetEnable())
			{
				++iter;
				continue;
			}
			(*iter)->Render(hDC, deltaTime);
			++iter;
		}
	}
	//UI
	{
		auto	iter = m_widgetComponentList.begin();
		auto	iterEnd = m_widgetComponentList.end();
		for (; iter != iterEnd;)
		{
			if (!(*iter)->GetActive())
			{
				iter = m_widgetComponentList.erase(iter);
				iterEnd = m_widgetComponentList.end();
				continue;
			}
			++iter;
		}
		m_widgetComponentList.sort(SortYWidgetComponent);
		iter = m_widgetComponentList.begin();
		iterEnd = m_widgetComponentList.end();
		for (; iter != iterEnd; ++iter)
		{
			if (!(*iter)->GetEnable())
			{
				continue;
			}
			(*iter)->Render(hDC, deltaTime);
		}
	}
	if (m_vecWidgetWindow.size() > 1)
	{
		std::sort(m_vecWidgetWindow.begin(), m_vecWidgetWindow.end(), CScene::SortWidget);
	}
	auto	iter1 = m_vecWidgetWindow.begin();
	auto	iter1End = m_vecWidgetWindow.end();
	for (; iter1 != iter1End;)
	{
		if (!(*iter1)->GetActive())
		{
			iter1 = m_vecWidgetWindow.erase(iter1);
			iter1End = m_vecWidgetWindow.end();
			continue;
		}
		else if (!(*iter1)->GetEnable())
		{
			++iter1;
			continue;
		}
		(*iter1)->Render(hDC, deltaTime);
		++iter1;
	}
}