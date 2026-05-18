#include "pch.h"
#include "Transform.h"

OthelloComponent::Transform::Transform()
    : m_localPosition(Vector2f::zero)
    , m_scale(Vector2f::one)
{
}

OthelloComponent::Transform::Transform(float x, float y)
    : m_localPosition(x, y)
    , m_scale(Vector2f::one)
{
}