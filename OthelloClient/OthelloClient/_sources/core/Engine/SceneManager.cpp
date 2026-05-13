#include "pch.h"
#include "SceneManager.h"

SceneManager::~SceneManager()
{

}

void SceneManager::Initialize()
{

}

IScene* SceneManager::GetActiveScene() const
{
	return m_currentActiveScene;
}