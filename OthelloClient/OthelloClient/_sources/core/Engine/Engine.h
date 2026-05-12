#pragma once
class WndBase;
class Renderer;

class Engine
{
public :
	Engine();
	virtual ~Engine();

	bool Initialize(int width, int height);
	void Run();
	void Shutdown();
private : 
	void Update();
	void FixedUpdate();
	void Render();

private :
	WndBase* m_window = nullptr;
	Renderer* m_renderer = nullptr;
};