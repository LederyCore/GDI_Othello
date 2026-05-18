#include "pch.h"
#include "Component.h"

void Component::SetActive(bool active)
{
    if (m_isActive == active) return;
    m_isActive = active;
    ToggleActive(m_isActive);
}

bool Component::GetActive() const
{
    return m_isActive;
}

GameObject* Component::GetOwner() const
{
    return m_owner;
}

void Component::ToggleActive(bool active)
{
    if (active)
    {
        OnEnable();
    }
    else
    {
        OnDisable();
    }
}