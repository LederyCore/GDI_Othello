#pragma once

class WndBase;
class Renderer;
class SceneManager;
class GameTimer;
class InputSystem;

class Engine
{
public:
	Engine();
	virtual ~Engine();

	bool Initialize(int width, int height);
	void Run();
	void Shutdown();
private:
	void Input();
	void FixedUpdate(float fixedTime);
	void Update(float deltaTime);
	void LateUpdate(float deltaTime);
	void Render();

private:
	GameTimer* m_timer = nullptr;
	WndBase* m_window = nullptr;
	InputSystem* m_inputSystem = nullptr;
	Renderer* m_renderer = nullptr;
	SceneManager* m_sceneManager = nullptr;

	float m_fDeltaTime = 0;
	float m_fFrameCount = 0;
};