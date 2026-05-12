#include "pch.h"
#include "Engine/Engine.h"
#include <iostream>


int main()
{
	Engine engine;

	if (!engine.Initialize(1080, 720)) return -1;

	engine.Run();

	engine.Shutdown();

	return 0;
}