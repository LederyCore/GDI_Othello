#pragma once

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

class WndBase abstract
{
public:
	WndBase() = default;
	virtual ~WndBase() = default;

	bool Create(const wchar_t* className, const wchar_t* windowName, int width, int height);
	void Destroy();

	void* GetHandle() const { return m_hWnd; }

	int GetWidth() const { return m_width; }
	int GetHeight() const { return m_height; }

protected:
	friend LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lParam);

	virtual void OnResize(int width, int height);
	virtual void OnClose() abstract;

	HWND m_hWnd = HWND();
	int m_width = 0;
	int m_height = 0;

	WndBase(const WndBase&) = delete;
	WndBase& operator=(const WndBase&) = delete;
	WndBase(WndBase&&) = delete;
	WndBase& operator=(WndBase&&) = delete;
};