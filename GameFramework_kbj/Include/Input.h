#pragma once
#include "GameInfo.h"
#include "SingletonMacro.h"

//나중에 소문자입력하면 대문자로 변환시켜주는거 구현할 예정
enum class Input_Type
{
	DOWN,
	STAY,
	UP,
	END
};

struct KeyState
{
	unsigned char	key;
	bool			down;	// 누르기 시작할때
	bool			stay;	// 누르고 있을때
	bool			up;		// 누르고 있던 키가 올라올때

	KeyState() 
		:key(0)
		,down(false)
		,stay(false)
		,up(false)
	{}
};

struct BindFunction
{
	void* obj;
	std::function<void()>	func;
	class CScene* scene;

	BindFunction() 
		: obj(nullptr)
		, scene(nullptr)
	{}
};

struct BindKey
{
	std::string	name;	// 이름
	KeyState*	key;	// 어떤 키를 사용하는지.
	bool		ctrl;
	bool		alt;
	bool		shift;
	std::vector<BindFunction*>	vecFunction[(int)Input_Type::END];

	BindKey() 
		:key(nullptr)
		,ctrl(false)
		,alt(false)
		,shift(false)
	{}
};

class CInput
{
	DECLARE_SINGLE(CInput)
private:
	CSharedPtr<class CGameObject> m_mouseObj;
	HWND	m_hWnd;
	Vector2	m_mousePos;			// 윈도우 창에서의 위치
	Vector2	m_mouseWorldPos;	// 월드공간에서의 마우스 위치
	Vector2	m_mouseMove;
	CollisionProfile* m_mouseProfile;
	std::unordered_map<unsigned char, KeyState*> m_mapkeystate;		//키의 상태들을 모아두는 변수
	std::unordered_map<std::string, BindKey*> m_mapBindKey;			//바인드키들을 모아두는 변수
	bool	m_ctrl;
	bool	m_alt;
	bool	m_shift;
	bool	m_mouseLDown;
	bool	m_mouseLStay;
	bool	m_mouseLUp;
	bool	m_showCursor;
	void UpdateMouse(float deltatime);
	void UpdateKeyState(float deltatime);
	void UpdateBindKey(float deltatime);
	void SetKeyCtrl(const std::string& name, bool ctrl = true);
	void SetKeyAlt(const std::string& name, bool alt = true);
	void SetKeyShift(const std::string& name, bool shift = true);
	KeyState* FindKeyState(unsigned char key);
	BindKey* FindBindKey(const std::string& name);
public:
	const Vector2& GetMousePos()	const
	{
		return m_mousePos;
	}
	const Vector2& GetMouseWorldPos()	const
	{
		return m_mouseWorldPos;
	}
	const Vector2& GetMouseMove()	const
	{
		return m_mouseMove;
	}
	CollisionProfile* GetMouseProfile()	const
	{
		return m_mouseProfile;
	}
	bool GetMouseLDown()	const
	{
		return m_mouseLDown;
	}
	bool GetMouseLPush()	const
	{
		return m_mouseLStay;
	}
	bool GetMouseLUp()	const
	{
		return m_mouseLUp;
	}
	void ComputeWorldMousePos(const Vector2& cameraPos);
	bool Init(HWND hWnd);
	void Update(float deltaTime);
	void PostUpdate(float deltaTime);
	void Render(HDC hDC, float deltaTime);
	bool AddBindKey(const std::string& name, unsigned char key);
	void ClearCallback();
	void ClearCallback(class CScene* scene);
	template <typename T>
	void AddBindFunction(const std::string& keyname,Input_Type type,T* object, void (T::* func)(), class CScene* scene)
	{
		BindKey* key = FindBindKey(keyname);
		if (!key)
		{
			return;
		}
		BindFunction* function = new BindFunction;
		function->obj = object;
		function->func = std::bind(func, object);
		key->vecFunction[(int)type].push_back(function);
	}
	template <typename T>
	bool DeleteBindFunction(const std::string& name, Input_Type type, T* obj)
	{
		BindKey* key = FindBindKey(name);
		if (!key)
		{
			return false;
		}
		auto	iter = key->vecFunction[(int)type].begin();
		auto	iterEnd = key->vecFunction[(int)type].end();
		for (; iter != iterEnd;)
		{
			if ((*iter)->obj == obj)
			{
				SAFE_DELETE((*iter));
				iter = key->vecFunction[(int)type].erase(iter);
				iterEnd = key->vecFunction[(int)type].end();
				continue;
			}
			++iter;
		}
		return true;
	}
};

