#include "pch.h"
#include "GameManager.h"
#include "../utils/Vector2f.h"
#include "../utils/DebugConsole.h"
#include "../core/Engine/SceneManager.h"
#include "../core/Engine/Scene.h"
#include "../game/DoroTest.h"

OthelloGameObject::GameManager::GameManager()
{
	LOG_INFO("게임 매니저 초기화 완료");

	Scene* scene = SceneManager::GetActiveScene();
	scene->AddGameObject(new DoroTest());
}