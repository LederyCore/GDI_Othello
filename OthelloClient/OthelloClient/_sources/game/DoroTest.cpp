#include "pch.h"
#include "DoroTest.h"
#include "../core/Engine/GDISpriteRenderer.h"
#include "../core/Engine/Transform.h"
#include "../components/DoroComponent.h"

OthelloGameObject::DoroTest::DoroTest()
{
	using namespace OthelloComponent;
	Transform* tr = GetComponent<Transform>();
	AddComponent<DoroComponent>();
	AddComponent<GDISpriteRenderer>()->LoadSprite(L"_resources/sprite/Doro.png");
	
	tr->SetPosition(200, 113);
	tr->SetScale(200, 113);
}