#pragma once
#include "../core/Engine/Component.h"
#include "../utils/Vector2f.h"
#include "../core/Engine/InputSystem.h"

class GameObject;

namespace OthelloComponent
{
	class Transform : public Component
	{
    public:
        Transform();
        Transform(float x, float y);
        virtual ~Transform() override;

        // Position
        const Vector2f& GetPosition() const { return m_localPosition; }
        void            SetPosition(const Vector2f& pos) { m_localPosition = pos; }
        void            SetPosition(float x, float y) { m_localPosition = { x, y }; }
        void            Translate(const Vector2f& delta) { m_localPosition += delta; }

        // Scale 
        const Vector2f& GetScale() const { return m_scale; }
        void            SetScale(float s) { m_scale = { s, s }; }
        void            SetScale(float x, float y) { m_scale = { x, y }; }

        const Transform* GetParent() { return m_parent; }
        void             SetParent(Transform* parent);
    private:
        Transform* m_parent = nullptr;
        std::vector<Transform*> m_children;
        Vector2f m_localPosition;
        Vector2f m_scale = Vector2f::one;
	};
}