#pragma once
class IScene;

class Renderer
{
public :
	Renderer(void* hwnd) : m_hwnd(static_cast<HWND>(hwnd)) { }
	virtual ~Renderer() = default;
	virtual void BeginFrame() = 0;
	virtual void RenderScene(IScene* scene) = 0;
	virtual void EndFrame() = 0;

protected :
	HWND m_hwnd;
	int m_width = 0;
	int m_height = 0;
};