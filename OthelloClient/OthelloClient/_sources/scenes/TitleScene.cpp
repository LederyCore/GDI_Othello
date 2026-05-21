#include "pch.h"
#include "TitleScene.h"
#include "../utils/DebugConsole.h"
#include "../game/GameManager.h"
#include "../game/TitleUI.h"


TitleScene::TitleScene()
{
	LOG_INFO("타이틀 씬 초기화");
}

TitleScene::~TitleScene()
{

}

void TitleScene::Enter()
{
	using namespace OthelloGameObject;
	AddGameObject(new TitleUI());
	AddGameObject(new GameManager());
}