#pragma once
#include "../core/Engine/Scene.h"
class TitleScene : public Scene
{
public :
	TitleScene();
	virtual ~TitleScene();

	void Enter() override;
};