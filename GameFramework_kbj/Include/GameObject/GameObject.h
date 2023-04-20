#pragma once
#include "../Ref.h"
#include "../Animation/Animation.h"
#include "../Widget/WidgetComponent.h"

class CGameObject : public CRef
{
protected:
	friend class CScene;
	friend class CInput;
	class CScene*	m_scene;
	CAnimation*		m_animation;
	CSharedPtr<class CTexture>	m_texture;
	ERender_Layer	m_renderLayer;
	Vector2			m_prevPos;
	Vector2			m_move;
	Vector2			m_pos;
	Vector2			m_size;
	Vector2			m_pivot;
	Vector2			m_ColliderSize;
	Vector2			m_OffsetSize;
	std::list<CSharedPtr<class CCollider>>	m_colliderList;
	std::list<CSharedPtr<CWidgetComponent>>	m_widgetComponentList;
	float		m_timeScale;			//오브젝트의 움직이는 속도를 조절할때 사용
	float		m_moveSpeed;
	//점프구현
	bool		m_physicsSimulate;
	bool		m_ground;	// 땅을 밟고 있는 상태인지 아닌지
	float		m_gravityAccel;
	float		m_fallTime;
	float		m_fallStartY;
	bool		m_jump;
	float		m_jumpVelocity;
	bool		m_SideWallCheck;
	bool		m_Start;
	bool		m_HaveShoes;
	bool		m_IsSlip;
	CGameObject();
	CGameObject(const CGameObject& obj);
	virtual ~CGameObject();
public:
	ERender_Layer GetRenderLayer()	const
	{
		return m_renderLayer;
	}
	const Vector2& GetPrevPos()	const
	{
		return m_prevPos;
	}
	const Vector2& GetMove()	const
	{
		return m_move;
	}
	const Vector2& GetPos()	const
	{
		return m_pos;
	}
	const Vector2& GetSize()	const
	{
		return m_size;
	}
	const Vector2& GetPivot()	const
	{
		return m_pivot;
	}
	const Vector2& GetColliderSize()	const
	{
		return m_ColliderSize;
	}
	const Vector2& GetOffsetSize()	const
	{
		return m_OffsetSize;
	}
	float GetTimeScale()	const
	{
		return m_timeScale;
	}
	bool GetHaveShoes()	const
	{
		return m_HaveShoes;
	}
	void SetMove(float x, float y)
	{
		m_move.x = x;
		m_move.y = y;
	}
	void SetMove(const Vector2& size)
	{
		m_move = size;
	}
	virtual void SetPos(float x, float y)
	{
		m_pos.x = x;
		m_pos.y = y;
	}
	virtual void SetPos(const Vector2& pos)
	{
		m_pos = pos;
	}
	void SetSize(float x, float y)
	{
		m_size.x = x;
		m_size.y = y;
	}
	void SetSize(const Vector2& size)
	{
		m_size = size;
	}
	void SetPivot(float x, float y)
	{
		m_pivot.x = x;
		m_pivot.y = y;
	}
	void SetPivot(const Vector2& pivot)
	{
		m_pivot = pivot;
	}
	void SetTimeScale(float scale)
	{
		m_timeScale = scale;
	}
	void SetMoveSpeed(float moveSpeed)
	{
		m_moveSpeed = moveSpeed;
	}
	void SetHaveShoes(bool b)
	{
		m_HaveShoes = b;
	}
	void SetPhysicsSimulate(bool physics)
	{
		m_physicsSimulate = physics;
	}
	void SetGravityAccel(float accel)
	{
		m_gravityAccel = accel;
	}
	void SetJumpVelocity(float jumpVelocity)
	{
		m_jumpVelocity = jumpVelocity;
	}
	void Jump()
	{
		if (!m_jump)
		{
			m_jump = true;
			m_ground = false;
			m_fallTime = 0.f;
			m_fallStartY = m_pos.y;
		}
	}
	void SetSideWallCheck(bool check)
	{
		m_SideWallCheck = check;
	}
	void SetSlip(bool b)
	{
		m_IsSlip = b;
	}
	class CCollider* FindCollider(const std::string& name);
	void SetTexture(const std::string& name);
	void SetTexture(class CTexture* texture);
	void SetTexture(const std::string& name, const TCHAR* fileName,const std::string& pathName = TEXTURE_PATH);
	void SetTextureFullPath(const std::string& name, const TCHAR* fullPath);
	bool SetColorKey(unsigned char r, unsigned char g, unsigned char b,int index = 0);
	bool SetColorKeyAll(unsigned char r, unsigned char g, unsigned char b);
	void CreateAnimation();
	void AddAnimation(const std::string& sequenceName, bool loop = true,float playTime = 1.f, float playScale = 1.f,
		bool reverse = false);
	void SetPlayTime(const std::string& name, float playTime);
	void SetPlayScale(const std::string& name, float playScale);
	void SetPlayLoop(const std::string& name, bool loop);
	void SetPlayReverse(const std::string& name, bool reverse);
	void SetCurrentAnimation(const std::string& name);
	void ChangeAnimation(const std::string& name);
	bool CheckCurrentAnimation(const std::string& name);
	void MoveDir(const Vector2& dir);
	void Move(const Vector2& moveValue);
	void MoveAngle(const Vector2& angle);
	void Move(float angle);
	virtual void Start();
	virtual bool Init();
	virtual void Update(float deltaTime);
	virtual void PostUpdate(float deltaTime);
	virtual void Render(HDC hDC,float deltaTime);
	virtual float InflictDamage(float damage);
	virtual void Save(FILE* file);
	virtual void Load(FILE* file);
	void SaveFullPath(const char* fullPath);
	void LoadFullPath(const char* fullPath);
	void SaveFileName(const char* fileName, const std::string& pathName);
	void LoadFileName(const char* fileName, const std::string& pathName);
	void CheckFall();
	void CheckUp();
	void CheckMoveRight();
	void CheckMoveLeft();
	void Slippery();
	CWidgetComponent* FindWidgetComponent(const std::string& name)
	{
		auto	iter = m_widgetComponentList.begin();
		auto	iterEnd = m_widgetComponentList.end();
		for (; iter != iterEnd; ++iter)
		{
			if ((*iter)->GetName() == name)
			{
				return *iter;
			}
		}
		return nullptr;
	}
#ifdef UNICODE
	void SetTexture(const std::string& name, const std::vector<std::wstring>& vecFileName,
		const std::string& pathName = TEXTURE_PATH);
	void SetTextureFullPath(const std::string& name, const std::vector<std::wstring>& vecFullPath);
#else
	void SetTexture(const std::string& name, const std::vector<std::string>& vecFileName,
		const std::string& pathName = TEXTURE_PATH);
	void SetTextureFullPath(const std::string& name, const std::vector<std::string>& vecFullPath);
#endif // UNICODE
	template <typename T>
	void SetEndFunction(const std::string& name, T* obj, void(T::* func)())
	{
		if (m_animation)
		{
			m_animation->SetEndFunction<T>(name, obj, func);
		}
	}
	template <typename T>
	void SetCurrentAnimationEndFunction(T* obj, void(T::* func)())
	{
		if (m_animation)
		{
			m_animation->SetCurrentAnimationEndFunction<T>(obj, func);
		}
	}
	template <typename T>
	void AddNotify(const std::string& name, int frame, T* obj, void(T::* func)())
	{
		if (m_animation)
		{
			m_animation->AddNotify<T>(name, frame, obj, func);
		}
	}
	template <typename T>
	T* AddCollider(const std::string& name)
	{
		T* collider = new T;
		collider->SetName(name);
		collider->m_owner = this;
		collider->m_scene = m_scene;
		if (!collider->Init())
		{
			SAFE_DELETE(collider);
			return nullptr;
		}
		m_colliderList.push_back(collider);
		return collider;
	}
	template <typename T>
	CWidgetComponent* CreateWidgetComponent(const std::string& name)
	{
		CWidgetComponent* widget = FindWidgetComponent(name);
		if (widget)
		{
			return widget;
		}
		widget = new CWidgetComponent;
		widget->m_owner = this;
		widget->m_scene = m_scene;
		widget->SetName(name);
		if (!widget->Init())
		{
			SAFE_DELETE(widget);
			return nullptr;
		}
		widget->CreateWidget<T>(name);
		m_widgetComponentList.push_back(widget);
		return widget;
	}
};