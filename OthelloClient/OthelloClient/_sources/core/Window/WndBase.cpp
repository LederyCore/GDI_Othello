#include "pch.h"
#include "WndBase.h"

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_MOUSEMOVE:
	{
		WndBase* pWnd = (WndBase*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
		if (pWnd && pWnd->m_onMouseMove) pWnd->m_onMouseMove(LOWORD(lParam), HIWORD(lParam));
		break;
	}
	case WM_LBUTTONDOWN:
	{
		WndBase* pWnd = (WndBase*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
		if (pWnd && pWnd->m_onMouseDown) pWnd->m_onMouseDown(0, LOWORD(lParam), HIWORD(lParam));
		break;
	}
	case WM_LBUTTONUP:
	{
		WndBase* pWnd = (WndBase*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
		if (pWnd && pWnd->m_onMouseUp) pWnd->m_onMouseUp(0, LOWORD(lParam), HIWORD(lParam));
		break;
	}
	case WM_RBUTTONDOWN:
	{
		WndBase* pWnd = (WndBase*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
		if (pWnd && pWnd->m_onMouseDown) pWnd->m_onMouseDown(1, LOWORD(lParam), HIWORD(lParam));
		break;
	}
	case WM_RBUTTONUP:
	{
		WndBase* pWnd = (WndBase*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
		if (pWnd && pWnd->m_onMouseUp) pWnd->m_onMouseUp(1, LOWORD(lParam), HIWORD(lParam));
		break;
	}
	case WM_KEYDOWN:
	{
		WndBase* pWnd = (WndBase*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
		if (pWnd && pWnd->m_onKeyDown) pWnd->m_onKeyDown((int)wParam);
		break;
	}
	case WM_KEYUP:
	{
		WndBase* pWnd = (WndBase*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
		if (pWnd && pWnd->m_onKeyUp) pWnd->m_onKeyUp((int)wParam);
		break;
	}
	case WM_SIZE:
	{
		WndBase* pWnd = (WndBase*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
		if (pWnd && pWnd->m_onResize) pWnd->m_onResize(LOWORD(lParam), HIWORD(lParam));
		break;
	}
	case WM_CLOSE:
	{
		WndBase* pWnd = (WndBase*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
		if (pWnd) pWnd->OnClose();
		PostQuitMessage(0);
		break;
	}
	case WM_SETCURSOR:
		SetCursor(LoadCursor(nullptr, IDC_ARROW));
		break;
	default:
		return::DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return NULL;
}

bool WndBase::Create(const wchar_t* className, const wchar_t* windowName, int width, int height)
{
	WNDCLASSEX wc = {};
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wc.lpszClassName = className;
	wc.lpfnWndProc = WndProc;

	ATOM classId = 0;
	if (!GetClassInfoEx(HINSTANCE(), className, &wc))
	{
		classId = RegisterClassEx(&wc);

		if (0 == classId) return false;
	}

	m_width = width;
	m_height = height;

	RECT rc = { 0, 0, width, height };
	AdjustWindowRect(&rc,
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX, FALSE);

	// 실제 윈도우 크기
	int realW = rc.right - rc.left;
	int realH = rc.bottom - rc.top;

	// 중앙 좌표 계산
	int x = (GetSystemMetrics(SM_CXSCREEN) - realW) / 2;
	int y = (GetSystemMetrics(SM_CYSCREEN) - realH) / 2;

	m_hWnd = CreateWindowEx(NULL, MAKEINTATOM(classId), L"", WS_OVERLAPPEDWINDOW,
		x, y,          // ← CW_USEDEFAULT 대신
		realW, realH,
		HWND(), HMENU(), HINSTANCE(), NULL);

	if (NULL == m_hWnd) return false;
	::SetWindowText((HWND)m_hWnd, windowName);

	SetWindowLongPtr((HWND)m_hWnd, GWLP_USERDATA, (LONG_PTR)this);

	ShowWindow((HWND)m_hWnd, SW_SHOW);
	UpdateWindow((HWND)m_hWnd);

	return true;
}

void WndBase::Destroy()
{
	if (NULL != m_hWnd)
	{
		DestroyWindow((HWND)m_hWnd);
		m_hWnd = NULL;
	}
}

void WndBase::OnResize(int width, int height)
{
	m_width = width;
	m_height = height;
}