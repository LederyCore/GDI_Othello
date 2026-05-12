#include "pch.h"
#include "Engine.h"
#include "Window/OthelloWindow.h"
#include "Renderer/GDIRenderer.h"
#include <iostream>

Engine::Engine()
{
	m_window = new OthelloWindow();
	m_renderer = new GDIRenderer(m_window->GetHandle());
}

Engine::~Engine()
{
	delete m_renderer;
	m_renderer = nullptr;  

	delete m_window;
	m_window = nullptr;   
}

bool Engine::Initialize(int width, int height)
{
	const wchar_t* className = L"OthelloEngine_0.1";
	const wchar_t* windowName = L"Othello";

	if (false == m_window->Create(className, windowName, width, height))
	{
		std::cerr << "Failed to Initialize" << std::endl;
		return false;
	}

	// InitRenderer();

	return true;
}

void Engine::Run()
{
	MSG msg = { 0 };
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			Update();
			Render();
		}
	}
}

void Engine::Shutdown()
{

}

void Engine::Update()
{

}

void Engine::FixedUpdate()
{

}

void Engine::Render()
{
	m_renderer->BeginFrame();
	m_renderer->RenderScene();
	m_renderer->EndFrame();
}