#pragma once
class IScene;

class Renderer
{
public :
	virtual ~Renderer() = default;
	virtual void Initialize(void* hwnd) = 0;
	virtual void BeginFrame() = 0;
	virtual void RenderScene(IScene* scene) = 0;
	virtual void EndFrame() = 0;

protected :
	HWND m_hwnd = nullptr;
	int m_width = 0;
	int m_height = 0;
};