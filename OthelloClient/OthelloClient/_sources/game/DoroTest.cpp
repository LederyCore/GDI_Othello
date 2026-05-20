#include "pch.h"
#include "DoroTest.h"
#include "../core/Engine/GDISpriteRenderer.h"
#include "../components/Transform.h"
#include "../components/DoroComponent.h"

OthelloGameObject::DoroTest::DoroTest()
{
	using namespace OthelloComponent;
	AddComponent<DoroComponent>();
	AddComponent<GDISpriteRenderer>()->LoadSprite(L"_resources/sprite/Doro.png");
	
	Transform* tr = GetComponent<Transform>();
	tr->SetPosition(500, 113);
	tr->SetScale(200, 113);
}