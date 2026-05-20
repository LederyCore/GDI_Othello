#include "pch.h"
#include "Transform.h"

OthelloComponent::Transform::Transform()
{
    m_localPosition = Vector2f::zero;
}

OthelloComponent::Transform::Transform(float x, float y)
    : m_localPosition(x, y)
{

}

OthelloComponent::Transform::~Transform()
{
    for (auto* c : m_children)
    {
        if (c)
        {
            c->m_parent = nullptr;
            delete c;             
        }
    }
    m_parent = nullptr;
    m_children.clear();
}

void OthelloComponent::Transform::SetParent(Transform* parent)
{
    m_parent = parent;
}