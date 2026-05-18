#include "pch.h"
#include "GameManager.h"
#include "../utils/Vector2f.h"

OthelloGameObject::GameManager::GameManager()
{
	Vector2f v1{ 1, 2 };
	Vector2f v2{ 3, 4 };

	v1 += v2;
	v1 *= 3;
}