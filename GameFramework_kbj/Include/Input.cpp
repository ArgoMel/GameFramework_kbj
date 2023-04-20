#include "Input.h"
#include "Collision/CollisionManager.h"
#include "Resource/ResourceManager.h"
#include "GameObject/GameObject.h"

DEFINITION_SINGLE(CInput)
CInput::CInput() 
	: m_hWnd{}
	, m_mouseProfile{}
	, m_ctrl(false)
	, m_alt(false)
	, m_shift(false)
	, m_mouseLDown(false)
	, m_mouseLStay(false)
	, m_mouseLUp(false)
	, m_showCursor(false)
{
}

CInput::~CInput() 
{
	{
		auto	iter = m_mapkeystate.begin();
		auto	iterend = m_mapkeystate.end();
		for (; iter != iterend; ++iter)
		{
			SAFE_DELETE(iter->second);
		}
		m_mapkeystate.clear();
	}

	{
		auto	iter = m_mapBindKey.begin();
		auto	iterend = m_mapBindKey.end();
		for (; iter != iterend; ++iter)
		{
			for (int i = 0; i < (int)Input_Type::END; ++i)
			{
				size_t	size = iter->second->vecFunction[i].size();
				for (size_t j = 0; j < size; ++j)
				{
					SAFE_DELETE(iter->second->vecFunction[i][j]);
				}
			}
			SAFE_DELETE(iter->second);
		}
		m_mapBindKey.clear();
	}
}
void CInput::UpdateMouse(float deltaTime)
{
	POINT	ptMouse;
	GetCursorPos(&ptMouse);		// 스크린 좌표로 나온다.
	ScreenToClient(m_hWnd, &ptMouse);		// 스크린 좌표를 윈도우 좌표로 변경한다.
	m_mouseMove.x = (float)ptMouse.x - m_mousePos.x;
	m_mouseMove.y = (float)ptMouse.y - m_mousePos.y;
	m_mousePos.x = (float)ptMouse.x;
	m_mousePos.y = (float)ptMouse.y;

	RECT	rc = {};
	GetClientRect(m_hWnd, &rc);
	if (rc.left <= ptMouse.x && ptMouse.x <= rc.right &&rc.top <= ptMouse.y && ptMouse.y <= rc.bottom)
	{
		if (m_showCursor)
		{
			m_showCursor = false;
			ShowCursor(FALSE);
		}
	}
	else
	{
		if (!m_showCursor)
		{
			m_showCursor = true;
			ShowCursor(TRUE);
		}
	}
	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
	{
		if (!m_mouseLDown && !m_mouseLStay)
		{
			m_mouseLDown = true;
			m_mouseLStay = true;
		}
		else
		{
			m_mouseLDown = false;
		}
	}
	else if (m_mouseLStay)
	{
		m_mouseLDown = false;
		m_mouseLStay = false;
		m_mouseLUp = true;
	}
	else if (m_mouseLUp)
	{
		m_mouseLUp = false;
	}
	m_mouseObj->SetPos(m_mouseWorldPos.x, m_mouseWorldPos.y);
	m_mouseObj->Update(deltaTime);
}

void CInput::UpdateKeyState(float deltaTime)
{
	m_ctrl = false;
	m_alt = false;
	m_shift = false;
	if (GetAsyncKeyState(VK_CONTROL) & 0x8000)
	{
		m_ctrl = true;
	}
	if (GetAsyncKeyState(VK_MENU) & 0x8000)
	{
		m_alt = true;
	}
	if (GetAsyncKeyState(VK_SHIFT) & 0x8000)
	{
		m_shift = true;
	}
	auto	iter = m_mapkeystate.begin();
	auto	iterend = m_mapkeystate.end();
	for (; iter != iterend; ++iter)
	{
		bool	keystay = false;
		if (GetAsyncKeyState(iter->second->key) & 0x8000)
		{
			keystay = true;
		}
		if (keystay)
		{
			if (!iter->second->down && !iter->second->stay)
			{
				iter->second->down = true;
				iter->second->stay = true;
			}
			else
			{
				iter->second->down = false;
			}
		}
		else if (iter->second->stay)
		{
			iter->second->up = true;
			iter->second->stay = false;
			iter->second->down = false;
		}
		else if (iter->second->up)
		{
			iter->second->up = false;
		}
	}
}

void CInput::UpdateBindKey(float deltaTime)
{
	auto	iter = m_mapBindKey.begin();
	auto	iterend = m_mapBindKey.end();
	for (; iter != iterend; ++iter)
	{
		if (iter->second->key->down &&
			iter->second->ctrl == m_ctrl &&
			iter->second->alt == m_alt &&
			iter->second->shift == m_shift)
		{
			size_t	size = iter->second->vecFunction[(int)Input_Type::DOWN].size();
			for (size_t i = 0; i < size; ++i)
			{
				iter->second->vecFunction[(int)Input_Type::DOWN][i]->func();
			}
		}
		if (iter->second->key->stay &&
			iter->second->ctrl == m_ctrl &&
			iter->second->alt == m_alt &&
			iter->second->shift == m_shift)
		{
			size_t	size = iter->second->vecFunction[(int)Input_Type::STAY].size();
			for (size_t i = 0; i < size; ++i)
			{
				iter->second->vecFunction[(int)Input_Type::STAY][i]->func();
			}
		}
		if (iter->second->key->up &&
			iter->second->ctrl == m_ctrl &&
			iter->second->alt == m_alt &&
			iter->second->shift == m_shift)
		{
			size_t	size = iter->second->vecFunction[(int)Input_Type::UP].size();
			for (size_t i = 0; i < size; ++i)
			{
				iter->second->vecFunction[(int)Input_Type::UP][i]->func();
			}
		}
	}
}

void CInput::SetKeyCtrl(const std::string& name, bool ctrl)
{
	BindKey* key = FindBindKey(name);
	if (!key)
	{
		return;
	}
	key->ctrl = ctrl;
}

void CInput::SetKeyAlt(const std::string& name, bool alt)
{
	BindKey* key = FindBindKey(name);
	if (!key)
	{
		return;
	}
	key->alt= alt;
}

void CInput::SetKeyShift(const std::string& name, bool shift)
{
	BindKey* key = FindBindKey(name);
	if (!key)
	{
		return;
	}
	key->shift = shift;
}

KeyState* CInput::FindKeyState(unsigned char key)
{
	auto	iter = m_mapkeystate.find(key);
	if (iter == m_mapkeystate.end())
	{
		return nullptr;
	}
	return iter->second;
}

BindKey* CInput::FindBindKey(const std::string& name)
{
	auto	iter = m_mapBindKey.find(name);
	if (iter == m_mapBindKey.end())
	{
		return nullptr;
	}
	return iter->second;
}

void CInput::ComputeWorldMousePos(const Vector2& cameraPos)
{
	m_mouseWorldPos = m_mousePos + cameraPos;
}
//순서 중요
bool CInput::Init(HWND hWnd)
{
	m_hWnd = hWnd;
	AddBindKey("MoveUp", VK_UP);
	AddBindKey("MoveDown", VK_DOWN);
	AddBindKey("MoveLeft", VK_LEFT);
	AddBindKey("MoveRight", VK_RIGHT);
	AddBindKey("Bomb", VK_SPACE);
	AddBindKey("Skill1", 'Z');
	AddBindKey("Skill2", 'X');
	AddBindKey("Click", VK_LBUTTON);
	AddBindKey("OpenTileMapEditor", 'T');
	SetKeyCtrl("OpenTileMapEditor");
	AddBindKey("PositionReset", VK_F1);
	AddBindKey("CheatMode", VK_F2);
	AddBindKey("Pause", VK_ESCAPE);

	m_mouseProfile = CCollisionManager::GetInst()->FindProfile("Mouse");

	std::vector<std::wstring>	vecFileName;
	for (int i = 0; i <= 10; ++i)
	{
		TCHAR	fileName[MAX_PATH] = {};
		wsprintf(fileName, TEXT("Mouse/%d.bmp"), i);
		vecFileName.push_back(fileName);
	}
	CResourceManager::GetInst()->CreateAnimationSequence("MouseDefault","MouseDefault", vecFileName, TEXTURE_PATH);
	for (int i = 0; i < 11; ++i)
	{
		CResourceManager::GetInst()->AddAnimationFrame("MouseDefault", 0.f, 0.f,32.f, 31.f);
	}
	CResourceManager::GetInst()->SetColorKey("MouseDefault", 255, 0, 255);

	m_mouseObj = new CGameObject;
	m_mouseObj->SetName("Mouse");
	m_mouseObj->Init();
	m_mouseObj->SetSize(32.f, 31.f);
	m_mouseObj->CreateAnimation();
	m_mouseObj->AddAnimation("MouseDefault", true);
	ShowCursor(FALSE);
	return true;
}

void CInput::Update(float deltatime)
{
	UpdateMouse(deltatime);
	UpdateKeyState(deltatime);
	UpdateBindKey(deltatime);
}

void CInput::PostUpdate(float deltaTime)
{
	m_mouseObj->PostUpdate(deltaTime);
}

void CInput::Render(HDC hDC, float deltaTime)
{
	m_mouseObj->Render(hDC, deltaTime);
}

bool CInput::AddBindKey(const std::string& name, unsigned char key)
{
	if (FindBindKey(name))
	{
		return false;
	}
	BindKey* newkey = new BindKey;
	KeyState* state = FindKeyState(key);
	if (!state)
	{
		state = new KeyState;
		state->key = key;
		m_mapkeystate.insert(std::make_pair(key, state));
	}
	newkey->key = state;
	newkey->name = name;
	m_mapBindKey.insert(std::make_pair(name, newkey));
	return true;
}

void CInput::ClearCallback()
{
	auto	iter = m_mapBindKey.begin();
	auto	iterEnd = m_mapBindKey.end();
	for (; iter != iterEnd; ++iter)
	{
		for (int i = 0; i < (int)Input_Type::END; ++i)
		{
			size_t	size = iter->second->vecFunction[i].size();
			for (size_t j = 0; j < size; ++j)
			{
				SAFE_DELETE(iter->second->vecFunction[i][j]);
			}
			iter->second->vecFunction[i].clear();
		}
	}
}

void CInput::ClearCallback(CScene* scene)
{
	auto	iter = m_mapBindKey.begin();
	auto	iterEnd = m_mapBindKey.end();
	for (; iter != iterEnd; ++iter)
	{
		for (int i = 0; i < (int)Input_Type::END; ++i)
		{
			auto	iter1 = iter->second->vecFunction[i].begin();
			auto	iter1End = iter->second->vecFunction[i].end();
			for (; iter1 != iter1End;)
			{
				if ((*iter1)->scene == scene)
				{
					SAFE_DELETE((*iter1));
					iter1 = iter->second->vecFunction[i].erase(iter1);
					iter1End = iter->second->vecFunction[i].end();
					continue;
				}
				++iter1;
			}
		}
	}
}
