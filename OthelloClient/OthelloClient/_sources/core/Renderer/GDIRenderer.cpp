#include "pch.h"
#include "GDIRenderer.h"

GDIRenderer::GDIRenderer(void* hwnd) : Renderer(hwnd)
{
	RECT rect;
	GetClientRect(m_hwnd, &rect);
	m_width  = rect.right  - rect.left;
	m_height = rect.bottom - rect.top;

	// 더블 버퍼링 관련 멤버 초기화
	m_hdc		= GetDC(m_hwnd);
	m_memDC		= CreateCompatibleDC(m_hdc);
	m_memBitmap = CreateCompatibleBitmap(m_hdc, m_width, m_height);
	m_oldBitmap = (HBITMAP)SelectObject(m_memDC, m_memBitmap);
}

GDIRenderer::~GDIRenderer()
{
	SelectObject(m_memDC, m_oldBitmap);
	DeleteObject(m_memBitmap);
	DeleteDC(m_memDC);
	ReleaseDC(m_hwnd, m_hdc);
}

void GDIRenderer::BeginFrame()
{
	// 백버퍼 클리어 (검정)
	RECT rect = { 0, 0, m_width, m_height };
	HBRUSH brush = CreateSolidBrush(RGB(0, 0, 0));
	FillRect(m_memDC, &rect, brush);
	DeleteObject(brush);
}

void GDIRenderer::RenderScene(IScene* scene)
{

}

void GDIRenderer::EndFrame()
{
	BitBlt(m_hdc, 0, 0, m_width, m_height, m_memDC, 0, 0, SRCCOPY);
}