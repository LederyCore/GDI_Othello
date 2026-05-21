#include "pch.h"
#include "TitleUI.h"
#include "../components/Transform.h"
#include "../core/Engine/Scene.h"
#include "../core/Engine/SceneManager.h"
#include "../core/Engine/GDISpriteRenderer.h"

OthelloGameObject::TitleUI::TitleUI()
{
	using namespace OthelloComponent;
	LOG_INFO("UI 초기화 완료");

	AddComponent<GDISpriteRenderer>()->LoadSprite(L"_resources/sprite/OdoroTitle.png");

	Transform* tr = GetComponent<Transform>();
	tr->SetPosition(0, 0);
	tr->SetScale(1080, 720);
}