#include "pch.h"
#include "GDIRenderer.h"
#include "../core/Engine/Scene.h"

GDIRenderer::~GDIRenderer()
{
	SelectObject(m_memDC, m_oldBitmap);
	DeleteObject(m_memBitmap);
	DeleteDC(m_memDC);
	ReleaseDC(m_hwnd, m_hdc);
}

void GDIRenderer::Initialize(void* hwnd)
{
	m_hwnd = static_cast<HWND>(hwnd);

	RECT rect;
	GetClientRect(m_hwnd, &rect);
	m_width = rect.right - rect.left;
	m_height = rect.bottom - rect.top;

	// 더블 버퍼링 관련 멤버 초기화
	m_hdc = GetDC(m_hwnd);
	m_memDC = CreateCompatibleDC(m_hdc);
	m_memBitmap = CreateCompatibleBitmap(m_hdc, m_width, m_height);
	m_oldBitmap = (HBITMAP)SelectObject(m_memDC, m_memBitmap);
}

void GDIRenderer::BeginFrame()
{
	// 백버퍼 클리어 (검정)
	RECT rect = { 0, 0, m_width, m_height };
	HBRUSH brush = CreateSolidBrush(RGB(0, 0, 0));
	FillRect(m_memDC, &rect, brush);
	DeleteObject(brush);
}

void GDIRenderer::RenderScene(Scene* scene)
{
	// 메모리 DC에 렌더링하도록 전달
	scene->Render(m_memDC);

	// --- 테스트 코드 ---

	// 1. 흰색 사각형
	//HBRUSH whiteBrush = CreateSolidBrush(RGB(255, 255, 255));
	//RECT rect = { 100, 100, 300, 300 };
	//FillRect(m_memDC, &rect, whiteBrush);
	//DeleteObject(whiteBrush);

	//// 2. 빨간 원
	//HBRUSH redBrush = CreateSolidBrush(RGB(255, 0, 0));
	//HPEN   noPen = (HPEN)GetStockObject(NULL_PEN);
	//SelectObject(m_memDC, redBrush);
	//SelectObject(m_memDC, noPen);
	//Ellipse(m_memDC, 350, 100, 550, 300);
	//DeleteObject(redBrush);

	//// 3. 텍스트
	//SetTextColor(m_memDC, RGB(0, 255, 0));
	//SetBkMode(m_memDC, TRANSPARENT);
	//TextOut(m_memDC, 100, 350, L"GDI Renderer OK", 15);

	// --- 테스트 코드 끝 ---
}


void GDIRenderer::RenderFPS(float fps)
{
	SetTextColor(m_memDC, RGB(0, 255, 0));
	SetBkMode(m_memDC, TRANSPARENT);

	wchar_t buffer[64];
	swprintf_s(buffer, L"FPS : %.0f", fps);

	TextOut(m_memDC, 5, 5, buffer, wcslen(buffer));
}

void GDIRenderer::EndFrame()
{
	// 백버퍼 데이터를 프론트 버퍼로 '복사'
	BitBlt(m_hdc, 0, 0, m_width, m_height, m_memDC, 0, 0, SRCCOPY);
}