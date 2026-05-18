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
    void Render(HDC hdc);

    void SetActive(bool active);  // Enable/Disable 제어

    template <typename T>
    T* AddComponent()
    {
        T* component = new T();
        component->SetOwner(this); 
        m_components.push_back(component);
        component->Awake();
        return component;
    }

    template <typename T>
    T* GetComponent() const
    {
        for (Component* component : m_components)
        {
            T* result = dynamic_cast<T*>(component);
            if (result)
            {
                return result;
            }
        }
        return nullptr;
    }

    template <typename T>
    void RemoveComponent()
    {
        auto it = std::find_if(m_components.begin(), m_components.end(),
            [](Component* component) {
                return dynamic_cast<T*>(component) != nullptr;
            });

        if (it != m_components.end())
        {
            delete* it;
            m_components.erase(it);
        }
    }
private:
    std::vector<Component*> m_components;
    bool m_isActive = true;
    bool m_isStarted = false;  // Start 호출 여부
};
