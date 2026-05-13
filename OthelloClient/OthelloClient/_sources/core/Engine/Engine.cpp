#include "pch.h"
#include "Engine.h"
#include "Window/OthelloWindow.h"
#include "Renderer/GDIRenderer.h"
#include "SceneManager.h"
#include "IScene.h"
#include <iostream>

Engine::Engine()
{
	m_window = new OthelloWindow();
	m_renderer = new GDIRenderer(m_window->GetHandle());
	m_sceneManager = new SceneManager();
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
	// InitSceneManager();

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
			Input();
			Update();
			LateUpdate();
			Render();
		}
	}
}

void Engine::Shutdown()
{
	// 소멸은 항상 생성 순서의 역순
	delete m_sceneManager;
	delete m_renderer;
	delete m_window;

	m_sceneManager = nullptr;
	m_renderer = nullptr;
	m_window = nullptr;
}

void Engine::Input()
{
	IScene* scene = m_sceneManager->GetActiveScene();

	//scene->Input();
}

void Engine::FixedUpdate()
{
	IScene* scene = m_sceneManager->GetActiveScene();

	//scene->FixedUpdate();
}

void Engine::Update()
{
	IScene* scene = m_sceneManager->GetActiveScene();

	//scene->Update();
}

void Engine::LateUpdate()
{
	IScene* scene = m_sceneManager->GetActiveScene();

	//scene->LateUpdate();
}

void Engine::Render()
{
	IScene* scene = m_sceneManager->GetActiveScene();

	m_renderer->BeginFrame();
	m_renderer->RenderScene(scene);
	m_renderer->EndFrame();
}