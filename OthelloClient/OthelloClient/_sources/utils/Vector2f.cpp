#include "pch.h"
#include "Vector2f.h"

// 정적 멤버 변수 초기화
const Vector2f Vector2f::right = Vector2f(1.0f, 0.0f);
const Vector2f Vector2f::left = Vector2f(-1.0f, 0.0f);
const Vector2f Vector2f::up = Vector2f(0.0f, 1.0f);
const Vector2f Vector2f::down = Vector2f(0.0f, -1.0f);
const Vector2f Vector2f::zero = Vector2f(0.0f, 0.0f);
const Vector2f Vector2f::one = Vector2f(1.0f, 1.0f);