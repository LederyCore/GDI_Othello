#pragma once
#include "Renderer.h"

class GDIRenderer : public Renderer
{
public :
	GDIRenderer(void* hwnd);
	~GDIRenderer();

	void BeginFrame() override;
	void RenderScene(IScene* scene) override;
	void EndFrame() override;

private :
	HDC m_hdc = nullptr;
	HDC m_memDC = nullptr;
	HBITMAP m_memBitmap = nullptr;
	HBITMAP m_oldBitmap = nullptr;
};