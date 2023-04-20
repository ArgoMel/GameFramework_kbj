#pragma once
#include "../GameInfo.h"

class CSceneCollision
{
private:
	friend class CScene;
	class CCollider* m_mouseCollision;
	class CWidget* m_mouseCollisionWidget;
	std::vector<class CCollider*>	m_vecCollider;
	std::vector<class CWidgetWindow*>	m_vecWidgetWindow;
	CSceneCollision();
	~CSceneCollision();
	static bool SortY(class CCollider* src, class CCollider* dest);
	static bool SortWidget(class CWidgetWindow* src, class CWidgetWindow* dest);
public:
	void AddCollider(class CCollider* collider);
	void AddWidgetWindow(class CWidgetWindow* window);
	void Collision(float deltaTime);
	void CollisionMouse(float deltaTime);
};

