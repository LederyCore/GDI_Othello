#include "pch.h"
#include "SceneManager.h"
#include "../scenes/TitleScene.h"

SceneManager* SceneManager::Instance = nullptr;

SceneManager::SceneManager()
{
	// 엔진 구조상 생성자는 무조건 한번만 호출된다는 가정
	Instance = this;
}

SceneManager::~SceneManager()
{
	// 엔진 구조상 소멸자는 무조건 한번만 호출된다는 가정
	Instance = nullptr;
}

void SceneManager::Initialize()
{
	m_currentActiveScene = new TitleScene();
	m_currentActiveScene->Enter();
}

SceneManager* SceneManager::GetInstance()
{
	return Instance;
}

Scene* SceneManager::GetActiveScene()
{
	if (Instance == nullptr) return nullptr;
	return Instance->m_currentActiveScene;
}