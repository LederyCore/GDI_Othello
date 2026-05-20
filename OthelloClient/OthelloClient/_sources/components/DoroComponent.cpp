#include "pch.h"
#include "DoroComponent.h"
#include "../components/Transform.h"
#include "../core/Engine/GameObject.h"
#include "../utils/DebugConsole.h"

OthelloComponent::DoroComponent::DoroComponent()
    : m_moveSpeed(100.0f)
    , m_moveDistance(100.0f)
    , m_currentDistance(0.0f)
    , m_movingRight(true)
    , m_startPosition(Vector2f::zero)
{
}

void OthelloComponent::DoroComponent::Start()
{
    LOG_INFO("도로롱 컴포넌트 시작!");
    
    auto* tr = GetOwner()->GetComponent<OthelloComponent::Transform>();
    if (tr)
    {
        m_startPosition = tr->GetPosition();
        LOG_INFO("도로롱 시작 위치: (%.1f, %.1f)", m_startPosition.X, m_startPosition.Y);
    }
}

void OthelloComponent::DoroComponent::FixedUpdate(float fixedTime)
{
    //auto* tr = GetOwner()->GetComponent<OthelloComponent::Transform>();
    //if (!tr) return;

    //// 이동 거리 계산 (고정 타임스텝으로 일정한 속도 보장)
    //float moveAmount = m_moveSpeed * fixedTime;

    //if (m_movingRight)
    //{
    //    m_currentDistance += moveAmount;
    //    
    //    if (m_currentDistance >= m_moveDistance)
    //    {
    //        // 오른쪽 끝에 도달, 왼쪽으로 전환
    //        m_currentDistance = m_moveDistance;
    //        m_movingRight = false;
    //    }
    //}
    //else
    //{
    //    m_currentDistance -= moveAmount;
    //    
    //    if (m_currentDistance <= 0.0f)
    //    {
    //        // 왼쪽 끝에 도달, 오른쪽으로 전환
    //        m_currentDistance = 0.0f;
    //        m_movingRight = true;
    //    }
    //}

    //// 위치 업데이트
    //Vector2f newPos = m_startPosition;
    //newPos.X += m_currentDistance;
    //tr->SetPosition(newPos);
}

void OthelloComponent::DoroComponent::Update(float deltaTime)
{
    auto* tr = GetOwner()->GetComponent<OthelloComponent::Transform>();
    if (!tr) return;

    float speed = m_moveSpeed * (deltaTime / 1000.f);

    if (InputSystem::GetKey(VK_LEFT))  tr->Translate({ -speed, 0 });
    if (InputSystem::GetKey(VK_RIGHT)) tr->Translate({ speed, 0 });
    if (InputSystem::GetKey(VK_UP))    tr->Translate({ 0, -speed });
    if (InputSystem::GetKey(VK_DOWN))  tr->Translate({ 0,  speed });

    if (InputSystem::GetKeyDown(VK_SPACE))
        LOG_GAME("스페이스 눌림!");

    if (InputSystem::GetKeyDown(VK_ESCAPE))
        LOG_GAME("ESC!");

    if (InputSystem::GetKeyDown(VK_SHIFT))
    {
        m_moveSpeed *= 3.0f;
        LOG_GAME("도로도로 달린다!");
    }

    if (InputSystem::GetKeyUp(VK_SHIFT))
        m_moveSpeed = 100.0f;
}