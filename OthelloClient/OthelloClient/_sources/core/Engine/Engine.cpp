#include "pch.h"
#include "Engine.h"
#include "Window/OthelloWindow.h"
#include "Renderer/GDIRenderer.h"
#include "SceneManager.h"
#include "Scene.h"
#include "../utils/GameTimer.h"
#include "../utils/DebugConsole.h"
#include "../utils/Renderhelp.h"
#include <iostream>

#define FIXED_TIMESTEP 0.0166f  // 16.6ms = 0.0166초 (60 FPS)

Engine::Engine()
{
	m_timer = new GameTimer();
	m_window = new OthelloWindow();
	m_renderer = new GDIRenderer();
	m_sceneManager = new SceneManager();
}

Engine::~Engine()
{
	delete m_sceneManager;
	m_sceneManager = nullptr;

	delete m_renderer;
	m_renderer = nullptr;  

	delete m_window;
	m_window = nullptr;   

	delete m_timer;
	m_timer = nullptr;
}

bool Engine::Initialize(int width, int height)
{
	CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED);
	m_timer->Reset();

	const wchar_t* className = L"OthelloEngine_0.1";
	const wchar_t* windowName = L"Othello";

	if (false == m_window->Create(className, windowName, width, height))
	{
		std::cerr << "Failed to Initialize" << std::endl;
		return false;
	}

	m_renderer		->Initialize(m_window->GetHandle());
	m_sceneManager	->Initialize();

	//renderHelp::Initialize();

	LOG_INFO("엔진 초기화 완료");
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
			m_timer->Tick();

			m_fDeltaTime = m_timer->DeltaTimeMS();
			m_fFrameCount += m_timer->DeltaTime();

			Input();

			while (m_fFrameCount >= FIXED_TIMESTEP)
			{
				FixedUpdate(FIXED_TIMESTEP);
				m_fFrameCount -= FIXED_TIMESTEP;
			}

			Update(m_fDeltaTime);
			LateUpdate(m_fDeltaTime);
			Render();
		}
	}
}

void Engine::Shutdown()
{
	CoUninitialize();

	// 소멸은 항상 생성 순서의 역순
	delete		m_sceneManager;
	delete		m_renderer;
	delete		m_window;
	delete		m_timer;

	m_sceneManager		= nullptr;
	m_renderer			= nullptr;
	m_window			= nullptr;
	m_timer				= nullptr;

}

void Engine::Input()
{
	Scene* scene = m_sceneManager->GetActiveScene();

	
}

void Engine::FixedUpdate(float fixedTime)
{
	Scene* scene = m_sceneManager->GetActiveScene();

	scene->FixedUpdate(fixedTime);
}

void Engine::Update(float deltaTime)
{
	Scene* scene = m_sceneManager->GetActiveScene();

	scene->Update(deltaTime);
}

void Engine::LateUpdate(float deltaTime)
{
	Scene* scene = m_sceneManager->GetActiveScene();

	scene->LateUpdate(deltaTime);
}

void Engine::Render()
{
	Scene* scene = m_sceneManager->GetActiveScene();

	m_renderer->BeginFrame();
	m_renderer->RenderScene(scene);

	float fps = 1.0f / m_timer->DeltaTime();
	m_renderer->RenderFPS(fps);

	m_renderer->EndFrame();
}