#include "pch.h"
#include "Button.h"
#include "../core/Engine/GameObject.h"

OthelloComponent::Button::Button() : m_width(50), m_height(50) {}

void OthelloComponent::Button::Awake()
{
    auto* tr = GetOwner()->GetComponent<OthelloComponent::Transform>();
    if (!tr) return;
    m_tr = tr;
}

void OthelloComponent::Button::Update(float deltaTime)
{
    if (!m_tr) return;

    m_pos = m_tr->GetPosition();
    m_width = m_tr->GetScale().X;
    m_height = m_tr->GetScale().Y;

    m_point4 = 
    {
        { m_pos.X,           m_pos.Y            }, // LeftTop
        { m_pos.X,           m_pos.Y + m_height }, // LeftBottom
        { m_pos.X + m_width, m_pos.Y            }, // RightTop
        { m_pos.X + m_width, m_pos.Y + m_height }  // RightBottom
    };

    const Vector2f mousePos = InputSystem::GetMousePosition();
    bool nowHovered = CheckInternal(mousePos);

    if (nowHovered && !m_isHovered) 
    {
        LOG_DEBUG("[Button] OnEnter");
        if (m_onEnter) m_onEnter();
    }

    if (!nowHovered && m_isHovered) 
    {
        LOG_DEBUG("[Button] OnExit");
        if (m_onExit) m_onExit();
    }

    if (nowHovered && InputSystem::GetMouseButtonDown(MouseInput::LEFT)) 
    {
        LOG_DEBUG("[Button] OnClick");
        if (m_onCLick) m_onCLick();
        m_isClicked = true;
    }
    else 
    {
        m_isClicked = false;
    }

    m_isHovered = nowHovered; // 상태 갱신
}

void OthelloComponent::Button::Render(HDC hdc)
{
    if (!m_tr) return;

    // 호버 상태에 따라 색상 변경
    COLORREF color = m_isHovered ? RGB(255, 255, 0) : RGB(0, 255, 0);

    HPEN   hPen = CreatePen(PS_SOLID, 2, color);
    HPEN   hOldPen = (HPEN)SelectObject(hdc, hPen);
    HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc, GetStockObject(NULL_BRUSH));

    Rectangle(hdc,
        (int)m_pos.X,
        (int)m_pos.Y,
        (int)(m_pos.X + m_width),
        (int)(m_pos.Y + m_height)
    );

    SelectObject(hdc, hOldPen);
    SelectObject(hdc, hOldBrush);
    DeleteObject(hPen);
}

bool OthelloComponent::Button::CheckInternal(const Vector2f& vec) const
{
    return vec.X > m_point4.LeftTop.X &&
        vec.X < m_point4.RightTop.X &&
        vec.Y > m_point4.LeftTop.Y &&
        vec.Y < m_point4.LeftBottom.Y;
}