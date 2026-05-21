#include "pch.h"
#include "Button.h"
#include "../core/Engine/GameObject.h"
#include "../core/Engine/GDISpriteRenderer.h"

OthelloComponent::Button::Button() : m_width(50), m_height(50) {}

void OthelloComponent::Button::Awake()
{
    auto* tr = GetOwner()->GetComponent<OthelloComponent::Transform>();
    auto* gs = GetOwner()->GetComponent<OthelloComponent::GDISpriteRenderer>();
    if (!tr) return;
    if (!gs) return;
    m_tr = tr;
    m_gs = gs;
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

    // 2. 이번 프레임의 타겟 상태(Target State) 계산
    ButtonState targetState = ButtonState::Normal;

    if (nowHovered)
    {
        // 마우스가 위에 있고 좌클릭 유지 중이면 Pressed, 아니면 Hovered
        if (InputSystem::GetMouseButton(MouseInput::LEFT))
            targetState = ButtonState::Pressed;
        else
            targetState = ButtonState::Hovered;
    }
    else
    {
        // 영역 밖인데 드래그 중인 경우
        if (InputSystem::GetMouseButton(MouseInput::LEFT) && m_currentState == ButtonState::Pressed)
        {
            targetState = ButtonState::Pressed; // 누른 채로 영역 밖으로 나갔다면 여전히 눌린 상태로 간주
        }
        else
        {
            targetState = ButtonState::Normal;
        }
    }

    if (m_currentState != targetState)
    {
        // Hover 진입
        if (targetState == ButtonState::Hovered && m_currentState == ButtonState::Normal)
        {
            LOG_DEBUG("[Button] OnEnter");
            if (m_onEnter) m_onEnter();
            m_gs->SetBrightness(m_hoveredBright);
        }
        // Hover 이탈
        else if (targetState == ButtonState::Normal && m_currentState == ButtonState::Hovered)
        {
            LOG_DEBUG("[Button] OnExit");
            if (m_onExit) m_onExit();
            m_gs->SetBrightness(m_originBright);
        }
        else if (targetState == ButtonState::Pressed)
        {
            m_gs->SetBrightness(m_clickedBright);
        }
        // 클릭 성공
        else if (m_currentState == ButtonState::Pressed && targetState == ButtonState::Hovered)
        {
            LOG_DEBUG("[Button] OnClick");
            if (m_onCLick) m_onCLick();
            m_gs->SetBrightness(m_hoveredBright);
        }
        // 클릭 취소
        else if (m_currentState == ButtonState::Pressed && targetState == ButtonState::Normal)
        {
            // 클릭 이벤트는 발생하지 않음 (드래그 취소)
            m_gs->SetBrightness(m_originBright);
        }

        // 현재 상태 갱신
        m_currentState = targetState;
    }
}

void OthelloComponent::Button::Render(HDC hdc)
{
    if (!m_tr) return;
    if (!m_gs) return;
    // 스프라이트 렌더러가 있을 경우 이미지의 명도를 조정


#ifdef _DEBUG
    // 디버그 모드인 경우 호버 상태에 따라 색상 변경 
    COLORREF color = m_currentState == ButtonState::Hovered ? RGB(255, 255, 0) : RGB(0, 255, 0);

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
#endif
}

bool OthelloComponent::Button::CheckInternal(const Vector2f& vec) const
{
    return vec.X > m_point4.LeftTop.X &&
        vec.X < m_point4.RightTop.X &&
        vec.Y > m_point4.LeftTop.Y &&
        vec.Y < m_point4.LeftBottom.Y;
}