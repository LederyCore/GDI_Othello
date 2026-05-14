#pragma once

class GameObject;

class Scene abstract
{
public :
	virtual ~Scene() { }

	virtual void FixedUpdate(float fixedTime) = 0;
	virtual void Update(float deltaTime) = 0;
	virtual void LateUpdate(float deltaTime) = 0;
	virtual void Render() = 0;

	virtual const std::vector<GameObject*>& GetGameObjects() = 0;

	bool AddGameObject(GameObject*);

private :

};