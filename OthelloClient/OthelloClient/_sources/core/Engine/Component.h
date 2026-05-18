#pragma once
class GameObject;

class Component abstract
{
public :
	virtual ~Component() = default;
	virtual void Awake() {}
	virtual void OnEnable() {}
	virtual void Start() {}
	virtual void FixedUpdate(float fixedTime) {}
	virtual void Update(float deltaTime) {}
	virtual void LateUpdate(float deltaTime) {}
	virtual void Render(HDC hdc) {}
	virtual void OnDisable() {}

	void SetActive(bool active);
	bool GetActive() const;

	void SetOwner(GameObject* owner) { m_owner = owner; }
	GameObject* GetOwner() const;
protected :


private :
	void ToggleActive(bool active);


private :
	GameObject* m_owner = nullptr;
	bool m_isActive = true;
};