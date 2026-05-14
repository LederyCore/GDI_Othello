#pragma once

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
	virtual void Render() {}
	virtual void OnDisable() {}

	void SetActive(bool active);
	bool GetActive() const;
protected :


private :
	void ToggleActive(bool active);


private :
	bool m_isActive = true;
};