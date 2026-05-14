#pragma once
#include <cmath>

struct Vector2f
{
	Vector2f() { X = 0;	Y = 0; }
	Vector2f(float x, float y) : X(x), Y(y) {}

	float X;
	float Y;


	Vector2f operator+(const Vector2f& other) const
	{
		return Vector2f(X + other.X, Y + other.Y);
	}

	Vector2f operator-(const Vector2f& other) const
	{
		return Vector2f(X - other.X, Y - other.Y);
	}

	Vector2f operator*(const float scalar) const
	{
		return Vector2f(X * scalar, Y * scalar);
	}

	bool operator==(const Vector2f& other) const
	{
		constexpr float EPSILON = 0.0001f;
		return (fabsf(X - other.X) < EPSILON &&
			fabsf(Y - other.Y) < EPSILON);
	}

	Vector2f operator+=(const Vector2f& other) const
	{
		return Vector2f(X + other.X, Y + other.Y);
	}

	Vector2f operator-=(const Vector2f& other) const
	{
		return Vector2f(X - other.X, Y - other.Y);
	}

	Vector2f operator*=(const float sclar) const
	{
		return Vector2f(X * sclar, Y * sclar);
	}

	float Dot(const Vector2f& other) const
	{
		return X * other.X + Y * other.Y;
	}

	float Cross(const Vector2f& other) const
	{
		return X * other.Y - Y * other.X;
	}

	float Magnitude() const
	{
		return sqrtf(X * X + Y * Y);
	}

	Vector2f Normalize() const
	{
		float mag = Magnitude();
		if (mag == 0.0f) return Vector2f(0, 0);
		return Vector2f(X / mag, Y / mag);
	}

	float Distance(const Vector2f& other) const
	{
		return (*this - other).Magnitude();
	}
};