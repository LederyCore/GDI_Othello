#pragma once

class GameObject;

class Scene abstract
{
public :
	virtual ~Scene();

	virtual void FixedUpdate(float fixedTime);
	virtual void Update(float deltaTime);
	virtual void LateUpdate(float deltaTime);
	virtual void Render();

	bool AddGameObject(GameObject*);
private:
	std::vector<GameObject*> m_rootObjects;
};