#pragma once
class Component;

class GameObject
{
public :
	GameObject();
	virtual ~GameObject();

	void Input();
	void FixedUpdate();
	void Update();
	void LateUpdate();
	void Render();
private :
	//std::vector<Component*> m_components;
};