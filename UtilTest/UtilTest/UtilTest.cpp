#include <iostream>
#include "Vector2f.h"


int main()
{
	Vector2f v1{ 1, 2 };
	Vector2f v2{ 3, 4 };

	std::cout << v1.Cross(v2) << std::endl;
	std::cout << v1.X << " " << v1.Y << std::endl;

	Vector2f v3 = v1 *= 3;

	std::cout << v1.X << " " << v1.Y << std::endl;
}