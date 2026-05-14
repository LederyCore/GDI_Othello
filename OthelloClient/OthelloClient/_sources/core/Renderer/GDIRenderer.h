#pragma once
#include "Renderer.h"

class GDIRenderer : public Renderer
{
public :
	GDIRenderer() = default;
	~GDIRenderer() override;

	void Initialize(void* hwnd) override;
	void BeginFrame() override;
	void RenderScene(Scene* scene) override;
	void RenderFPS(float fps) override;
	void EndFrame() override;
private :
	HDC m_hdc = nullptr;
	HDC m_memDC = nullptr;
	HBITMAP m_memBitmap = nullptr;
	HBITMAP m_oldBitmap = nullptr;
};