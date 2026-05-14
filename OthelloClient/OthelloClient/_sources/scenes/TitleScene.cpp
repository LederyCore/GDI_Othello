#include "pch.h"
#include "TitleScene.h"
#include "../core/Engine/GameObject.h"

TitleScene::TitleScene()
{

}

TitleScene::~TitleScene()
{

}


void TitleScene::FixedUpdate(float fixedTime)
{
	for (const auto& go : m_rootObjects)
	{
		go->FixedUpdate(fixedTime);
	}
}

void TitleScene::Update(float deltaTime)
{
	for (const auto& go : m_rootObjects)
	{
		go->Update(deltaTime);
	}
}

void TitleScene::LateUpdate(float deltaTime)
{
	for (const auto& go : m_rootObjects)
	{
		go->LateUpdate(deltaTime);
	}
}

void TitleScene::Render()
{
	for (const auto& go : m_rootObjects)
	{
		go->Render();
	}
}

const std::vector<GameObject*>& TitleScene::GetGameObjects()
{
	return m_rootObjects;
}

