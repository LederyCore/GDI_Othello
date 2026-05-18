#pragma once

class GameObject;

class Scene abstract
{
public :
	virtual ~Scene();
	virtual void Enter() {}		// 씬 진입 시 오브젝트 등록
	virtual void Exit() {}		// 씬 종료 시 정리
	virtual void FixedUpdate(float fixedTime);
	virtual void Update(float deltaTime);
	virtual void LateUpdate(float deltaTime);
	virtual void Render(HDC hdc);

	bool AddGameObject(GameObject*);
private:
	std::vector<GameObject*> m_rootObjects;
};