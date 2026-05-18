#pragma once
#include "../core/Engine/Component.h"

namespace OthelloComponent
{
    class DoroComponent : public Component
    {
    public:
        DoroComponent();
        virtual ~DoroComponent() override = default;

        void Start() override;
        void FixedUpdate(float fixedTime) override;

    private:
        // 움직임 관련
        float m_moveSpeed = 100.0f;  // 픽셀/초
        float m_moveDistance = 100.0f;  // 움직일 거리
        float m_currentDistance = 0.0f;  // 현재까지 움직인 거리
        bool m_movingRight = true;  // 오른쪽으로 이동 중?
        
        Vector2f m_startPosition;  // 시작 위치
    };
}