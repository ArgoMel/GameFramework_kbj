#include "GameManager.h"
#include "resource.h"
#include "Timer.h"
#include "Scene/SceneManager.h"
#include "Input.h"
#include "Resource/ResourceManager.h"
#include "PathManager.h"
#include "Collision/CollisionManager.h"

DEFINITION_SINGLE(CGameManager)
bool CGameManager::m_Loop = true;

CGameManager::CGameManager()
    : m_hInst{}
    , m_hWnd{}
    , m_hDC(0)
    , m_hBackDC(0)
    , m_hBackBmp(0)
    , m_hBackPrevBmp(0)
    , m_frameLimitTime(1 / 60.f)
    , m_deltaTime(0.f)
    , m_timeScale(1.f)
    , m_EditMode(false)
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    //_CrtSetBreakAlloc(233);
    srand((unsigned int)time(0));
    m_RS.width = 1280;
    m_RS.height = 720;
    m_timer = new CTimer;
    m_brush[(int)EBrush_Type::Red] = CreateSolidBrush(RGB(255, 0, 0));
    m_brush[(int)EBrush_Type::Green] = CreateSolidBrush(RGB(0, 255, 0));
    m_brush[(int)EBrush_Type::Black] = CreateSolidBrush(RGB(0, 0, 0));
    m_brush[(int)EBrush_Type::Blue] = CreateSolidBrush(RGB(0, 0, 255));
    m_brush[(int)EBrush_Type::Yellow] = CreateSolidBrush(RGB(255, 255, 0));
    m_pen[(int)EBrush_Type::Red] = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
    m_pen[(int)EBrush_Type::Green] = CreatePen(PS_SOLID, 2, RGB(0, 255, 0));
    m_pen[(int)EBrush_Type::Black] = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
    m_pen[(int)EBrush_Type::Blue] = CreatePen(PS_SOLID, 2, RGB(0, 0, 255));
    m_pen[(int)EBrush_Type::Yellow] = CreatePen(PS_SOLID, 2, RGB(255, 255, 0));
}

CGameManager::~CGameManager()
{
    CSceneManager::DestroyInst();
    CPathManager::DestroyInst();
    CCollisionManager::DestroyInst();
    CInput::DestroyInst();
    CResourceManager::DestroyInst();
    SAFE_DELETE(m_timer);
    SelectObject(m_hBackDC, m_hBackPrevBmp);
    DeleteObject(m_hBackBmp);
    DeleteDC(m_hBackDC);
    for (int i = 0; i < (int)EBrush_Type::Max; ++i)
    {
        DeleteObject(m_brush[i]);
    }
    for (int i = 0; i < (int)EBrush_Type::Max; ++i)
    {
        DeleteObject(m_pen[i]);
    }
    ReleaseDC(m_hWnd, m_hDC);
}

float CGameManager::GetFPS() const
{
    return m_timer->GetFPS();
}

void CGameManager::Exit()
{
    DestroyWindow(m_hWnd);
}

bool CGameManager::Init(HINSTANCE hInst)
{
    m_hInst = hInst;
    Register();
    Create();
    if (!CPathManager::GetInst()->Init())
    {
        return false;
    }
    if (!CResourceManager::GetInst()->Init())
    {
        return false;
    }
    if (!CCollisionManager::GetInst()->Init())
    {
        return false;
    }
    if (!CInput::GetInst()->Init(m_hWnd))
    {
        return false;
    }
    if(!CSceneManager::GetInst()->Init())
    {
        return false;
    }
    m_timer->Init();
    m_hDC = GetDC(m_hWnd);
    m_hBackDC = CreateCompatibleDC(m_hDC);
    m_hBackBmp = CreateCompatibleBitmap(m_hDC, m_RS.width, m_RS.height);
    m_hBackPrevBmp = (HBITMAP)SelectObject(m_hBackDC, m_hBackBmp);
    return true;
}

int CGameManager::Run()
{
    MSG msg{};
    while (m_Loop)
    {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
            Logic();
        }
    }
    return (int)msg.wParam;
}

void CGameManager::Logic()
{
    m_timer->Update();
    m_deltaTime = m_timer->GetDeltaTime()*m_timeScale;
    Input(m_deltaTime);
    if(Update(m_deltaTime))
    {
        return;
    }
    if(PostUpdate(m_deltaTime))
    {
        return;
    }
    Collision(m_deltaTime);
    Render(m_deltaTime);
}

void CGameManager::Input(float deltaTime)
{
    CInput::GetInst()->Update(deltaTime);
}

bool CGameManager::Update(float deltaTime)
{
    CResourceManager::GetInst()->Update();
    return CSceneManager::GetInst()->Update(deltaTime);
}

bool CGameManager::PostUpdate(float deltaTime)
{
    CInput::GetInst()->PostUpdate(deltaTime);
    return CSceneManager::GetInst()->PostUpdate(deltaTime);
}

void CGameManager::Collision(float deltaTime)
{
}

void CGameManager::Render(float deltaTime)
{
    CSceneManager::GetInst()->Render(m_hBackDC, deltaTime);
    CInput::GetInst()->Render(m_hBackDC, deltaTime);
    BitBlt(m_hDC, 0, 0, m_RS.width, m_RS.height, m_hBackDC, 0, 0, SRCCOPY);
}

void CGameManager::Register()
{
    WNDCLASSEXW wcex;
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = m_hInst;
    wcex.hIcon = LoadIcon(m_hInst, MAKEINTRESOURCE(IDI_ICON1));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = nullptr;// MAKEINTRESOURCEW(IDC_MY220428);
    wcex.lpszClassName = TEXT("GameFramework");
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_ICON1));

    RegisterClassExW(&wcex);
}

bool CGameManager::Create()
{
    m_hWnd = CreateWindowW(TEXT("GameFramework"),
        TEXT("AssortRock41_KBJ"), WS_OVERLAPPEDWINDOW,
        100, 0, 0, 0, nullptr, nullptr, m_hInst, nullptr);
    if (!m_hWnd)
    {
        return false;
    }
    RECT    rc = { 0, 0, m_RS.width, m_RS.height };
    RECT    rtDesk;
    GetWindowRect(GetDesktopWindow(),&rtDesk);
    AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);
    int width= rc.right - rc.left;
    int height= rc.bottom - rc.top;
    MoveWindow(m_hWnd, (rtDesk.right- width)/2, (rtDesk.bottom - height)/2, width, height, TRUE);
    ShowWindow(m_hWnd, SW_SHOW);
    UpdateWindow(m_hWnd);
    return true;
}

LRESULT CGameManager::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_GETMINMAXINFO:
        ((MINMAXINFO*)lParam)->ptMaxTrackSize.x = 1280+16;
        ((MINMAXINFO*)lParam)->ptMaxTrackSize.y = 720+38;
        ((MINMAXINFO*)lParam)->ptMinTrackSize.x = 1280 + 16;
        ((MINMAXINFO*)lParam)->ptMinTrackSize.y = 720+38;
        return FALSE;
    case WM_DESTROY:
        m_Loop = false;
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}
