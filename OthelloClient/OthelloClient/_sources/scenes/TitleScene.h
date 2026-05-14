#pragma once
#include "../core/Engine/Scene.h"
class TitleScene : public Scene
{
public :
	TitleScene();
	virtual ~TitleScene();

	void FixedUpdate(float fixedTime) override;
	void Update(float deltaTime) override;
	void LateUpdate(float deltaTime) override;
	void Render() override;

	const std::vector<GameObject*>& GetGameObjects() override;
private :
	std::vector<GameObject*> m_rootObjects;
};