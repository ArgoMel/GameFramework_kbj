#pragma once
#include "../GameInfo.h"
#include "../GameObject/GameObject.h"
#include "../Widget/WidgetWindow.h"
#include "../Widget/WidgetComponent.h"

class CScene
{
private:
	friend class CSceneManager;
	class CSceneResource* m_resource;
	class CCamera* m_camera;
	class CSceneCollision* m_collision;
	static bool SortY(const CSharedPtr<class CGameObject>& src, const CSharedPtr<class CGameObject>& dest);
	static bool SortYWidgetComponent(const CSharedPtr<class CWidgetComponent>& src, const CSharedPtr<class CWidgetComponent>& dest);
	static bool SortWidget(const CSharedPtr<CWidgetWindow>& src, const CSharedPtr<CWidgetWindow>& dest);
protected:
	CSharedPtr<class CGameObject>	m_player;
	CSharedPtr<class CTileMap>		m_TileMap;
	std::list<CSharedPtr<class CSewer>>	m_listSewer;
	std::list<CSharedPtr<class CGameObject>> m_objList[(int)ERender_Layer::Max];
	std::list<CSharedPtr<CWidgetComponent>>	m_widgetComponentList;
	std::vector<CSharedPtr<CWidgetWindow>>	m_vecWidgetWindow;
	std::string m_Name;
	int m_WallCount;
	CScene();
	virtual ~CScene();
public:
	class CSceneResource* GetSceneResource()	const
	{
		return m_resource;
	}
	class CCamera* GetCamera()	const
	{
		return m_camera;
	}
	class CSceneCollision* GetCollision()	const
	{
		return m_collision;
	}
	class CGameObject* GetPlayer()	const
	{
		return m_player;
	}
	class CTileMap* GetTileMap()	const
	{
		return m_TileMap;
	}
	int GetWallCount()	const
	{
		return m_WallCount;
	}
	std::string GetName()	const
	{
		return m_Name;
	}
	//여기다 한번에 다적으면 sharedptr이 여기서 레퍼런스 카운터를 올리는데 그때 에러남
	void SetTileMap(class CTileMap* tileMap);
	void SetPlayer(class CGameObject* player);
	//{
	//	m_player = player;
	//}
	void SetWallCount(int count)
	{
		m_WallCount = count;
	}
	void SetName(const std::string& name)
	{
		m_Name = name;
	}
	void AddWidgetComponent(CWidgetComponent* widget)
	{
		m_widgetComponentList.push_back(widget);
	}
	std::list<CSharedPtr<CSewer>>::iterator SewerBegin();
	std::list<CSharedPtr<CSewer>>::iterator SewerEnd();
	virtual bool Init();
	virtual void Update(float deltaTime);
	virtual void PostUpdate(float deltaTime);
	virtual void Render(HDC hDC, float deltaTime);
	template <typename T>
	T* CreateObject(const std::string& name = "GameObject")
	{
		T* obj = new T;
		obj->SetName(name);
		obj->m_scene = this;
		if (!obj->Init())
		{
			SAFE_DELETE(obj);
			return nullptr;
		}
		m_objList[(int)obj->GetRenderLayer()].push_back((CGameObject*)obj);
		return obj;
	}
	template <typename T>
	T* FindObject(const std::string& name)
	{
		for (size_t i = 0; i < (int)ERender_Layer::Max; ++i)
		{
			auto	iter = m_objList[i].begin();
			auto	iterEnd = m_objList[i].end();
			for (; iter != iterEnd; ++iter)
			{
				if ((*iter)->GetName() == name)
				{
					return (T*)(*iter).Get();
				}
			}
		}
		return nullptr;
	}
	template <typename T>
	T* CreateWidgetWindow(const std::string& name = "Window")
	{
		T* window = new T;
		window->SetName(name);
		window->m_scene = this;
		if (!window->Init())
		{
			SAFE_DELETE(window);
			return nullptr;
		}
		m_vecWidgetWindow.push_back(window);
		return (T*)window;
	}
	template <typename T>
	T* FindWidgetWindow(const std::string& name)
	{
		size_t	size = m_vecWidgetWindow.size();
		for (size_t i = 0; i < size; ++i)
		{
			if (m_vecWidgetWindow[i]->GetName() == name)
			{
				return (T*)m_vecWidgetWindow[i].Get();
			}
		}
		return nullptr;
	}
	template <typename T>
	T* FindWidget(const std::string& name)
	{
		size_t	size = m_vecWidgetWindow.size();
		for (size_t i = 0; i < size; ++i)
		{
			T* widget = m_vecWidgetWindow[i]->FindWidget<T>(name);
			if (widget)
			{
				return widget;
			}
		}
		return nullptr;
	}
};