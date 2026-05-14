#pragma once
class Component;

// GameObject.h
class GameObject abstract
{
public:
    GameObject();
    virtual ~GameObject();
    void FixedUpdate(float fixedTime);
    void Update(float deltaTime);
    void LateUpdate(float deltaTime);
    void Render();

    void SetActive(bool active);  // Enable/Disable 제어
    void AddComponent(Component* component);
private:
    std::vector<Component*> m_components;
    bool m_isActive = true;
    bool m_isStarted = false;  // Start 호출 여부
};