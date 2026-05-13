#pragma once
class GameObject;

class IScene abstract
{
public :
	virtual ~IScene() { }

	virtual void Input() = 0;
	virtual void FixedUpdate() = 0;
	virtual void Update() = 0;
	virtual void LateUpdate() = 0;
	virtual void Render() = 0;

	virtual const std::vector<GameObject*>& GetGameObjects() = 0;
};