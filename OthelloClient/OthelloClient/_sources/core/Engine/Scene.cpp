#include "pch.h"
#include "Scene.h"
#include "../core/Engine/GameObject.h"

Scene::~Scene()
{
	for (auto* obj : m_rootObjects)
		delete obj;

	m_rootObjects.clear();
}

void Scene::FixedUpdate(float fixedTime)
{
	for (const auto& go : m_rootObjects)
	{
		go->FixedUpdate(fixedTime);
	}
}

void Scene::Update(float deltaTime)
{
	for (const auto& go : m_rootObjects)
	{
		go->Update(deltaTime);
	}
}

void Scene::LateUpdate(float deltaTime)
{
	for (const auto& go : m_rootObjects)
	{
		go->LateUpdate(deltaTime);
	}
}

void Scene::Render()
{
	for (const auto& go : m_rootObjects)
	{
		go->Render();
	}
}

bool Scene::AddGameObject(GameObject*)
{



	return false;
}