#pragma once
#include "../components/Transform.h"
#include "../utils/Vector2f.h"
#include <functional>


namespace OthelloComponent
{
    class Transform;

    class Button : public Component
    {
    public:
        Button();

        void Awake()  override;
        void Update(float deltaTime) override;
        void Render(HDC hdc)        override;

        // 상태 조회
        bool IsHovered() const { return m_isHovered; }
        bool IsClicked() const { return m_isClicked; }

        // 콜백 등록
        void SetOnEnter(std::function<void()> cb) { m_onEnter = cb; }
        void SetOnExit(std::function<void()> cb) { m_onExit = cb; }
        void SetOnClick(std::function<void()> cb) { m_onCLick = cb; }

    private:
        bool CheckInternal(const Vector2f& vec) const;

    private:
        struct Point4 {
            Vector2f LeftTop;
            Vector2f LeftBottom;
            Vector2f RightTop;
            Vector2f RightBottom;
        };

        Transform* m_tr = nullptr;
        Vector2f   m_pos;
        float      m_width = 50.f;
        float      m_height = 50.f;
        Point4     m_point4 = {};

        // 이전 프레임 상태
        bool m_isHovered = false;
        bool m_isClicked = false;

        // 콜백
        std::function<void()> m_onEnter;
        std::function<void()> m_onExit;
        std::function<void()> m_onCLick;
    };
}