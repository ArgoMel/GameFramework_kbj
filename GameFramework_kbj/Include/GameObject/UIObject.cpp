#include "UIObject.h"
#include "../Scene/Scene.h"
#include "../Widget/WidgetComponent.h"
#include "../Widget/Text.h"
#include "../Widget/ImageWidget.h"

CUIObject::CUIObject()
{
    SetTypeID<CUIObject>();
    m_OutputSize = Vector2(0.f, 42.f);
}

CUIObject::CUIObject(const CUIObject& obj)
{
}

CUIObject::~CUIObject()
{
}

bool CUIObject::Init()
{
    CGameObject::Init();
    SetPos(277.f, 664.f);
    SetPivot(0.5f, 0.5f);

    int size = (int)std::size(m_ItemIcon);
    char widgetName[64] = {};
    for (int i = 0; i < size; ++i)
    {
        sprintf_s(widgetName, "ItemIcon_%d", i+3);
        m_ItemIcon[i] = CreateWidgetComponent<CImageWidget>(widgetName);
        TCHAR	fileName[MAX_PATH] = {};
        wsprintf(fileName, TEXT("Item/item_%d.bmp"), i+3);
        m_ItemIcon[i]->GetWidget<CImageWidget>()->SetTexture(widgetName, fileName);
        m_ItemIcon[i]->GetWidget<CImageWidget>()->SetColorKey(255, 0, 255);
        m_ItemIcon[i]->GetWidget<CImageWidget>()->SetSize(38.f, 38.f);
        m_ItemIcon[i]->SetPos(907.f, -506.f + i * 60.f);
    }
    size = (int)std::size(m_ItemCount);
    for (int i = 0; i < size; ++i)
    {
        sprintf_s(widgetName, "ItemCount_%d", i);
        m_ItemCount[i] = CreateWidgetComponent<CText>(widgetName);
        m_ItemCount[i]->GetWidget<CText>()->SetText(TEXT("1"));
        m_ItemCount[i]->GetWidget<CText>()->SetTextColor(255, 255, 255);
        m_ItemCount[i]->GetWidget<CText>()->EnableShadow(true);
        m_ItemCount[i]->GetWidget<CText>()->SetTextShadowColor(0,0,0);
        m_ItemCount[i]->GetWidget<CText>()->SetShadowOffset(2.f, 2.f);
        m_ItemCount[i]->SetPos(854.f, -485.f + i * 60.f);
    }

    m_CTImage = CreateWidgetComponent<CImageWidget>("DartCT");
    m_CTImage->GetWidget<CImageWidget>()->SetTexture("DartCT", TEXT("Item/dart_cooltime.bmp"));
    m_CTImage->GetWidget<CImageWidget>()->SetSize(m_OutputSize);
    m_CTImage->SetPos(903.f, -388.f);
	return true;
}

void CUIObject::Update(float deltaTime)
{
    CGameObject::Update(deltaTime);
    if (0.f<m_OutputSize.x )
    {
        m_CTImage->GetWidget<CImageWidget>()->SetSize(m_OutputSize);
        m_OutputSize.x -= 20.f * deltaTime;
        if (m_OutputSize.x < 0.f)
        {
            m_OutputSize.x = 0.f;
        }
    }
}

void CUIObject::PostUpdate(float deltaTime)
{
    CGameObject::PostUpdate(deltaTime);
}

void CUIObject::Render(HDC hDC, float deltaTime)
{
    CGameObject::Render(hDC,deltaTime);
}

void CUIObject::SetCount(int index, int count)
{
    std::wstring s = std::to_wstring(count);
    m_ItemCount[index]->GetWidget<CText>()->SetText(s.c_str());
}

void CUIObject::StartCT()
{
    m_OutputSize.x = 42.f;
}
