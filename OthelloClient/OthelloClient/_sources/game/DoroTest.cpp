#include "pch.h"
#include "DoroTest.h"
#include "../core/Engine/GDISpriteRenderer.h"
#include "../components/Transform.h"
#include "../components/DoroComponent.h"
#include "../components/Button.h"

OthelloGameObject::DoroTest::DoroTest()
{
	using namespace OthelloComponent;
	AddComponent<DoroComponent>();
	AddComponent<GDISpriteRenderer>()->LoadSprite(L"_resources/sprite/Doro100_100.png");
	AddComponent<Button>();

	Transform* tr = GetComponent<Transform>();
	tr->SetPosition(500, 113);
	tr->SetScale(100, 100);
}