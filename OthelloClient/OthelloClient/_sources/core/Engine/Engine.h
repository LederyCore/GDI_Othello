#pragma once
class WndBase;
class Renderer;
class SceneManager;

class Engine
{
public :
	Engine();
	virtual ~Engine();

	bool Initialize(int width, int height);
	void Run();
	void Shutdown();
private : 
	void Input();
	void FixedUpdate();
	void Update();
	void LateUpdate();
	void Render();

private :
	WndBase* m_window				= nullptr;
	Renderer* m_renderer			= nullptr;
	SceneManager* m_sceneManager	= nullptr;
};