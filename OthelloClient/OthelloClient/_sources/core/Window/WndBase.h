#pragma once
#include <functional>

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

class WndBase abstract
{
public:
	WndBase() = default;
	virtual ~WndBase() = default;

	using MouseMoveCallback		=	std::function<void(int x, int y)>;
	using MouseButtonCallback	=	std::function<void(int button, int x, int y)>;
	using KeyCallback			=	std::function<void(int keyCode)>;
	using ResizeCallback		=	std::function<void(int width, int height)>;

	void SetOnMouseMove(MouseMoveCallback   cb) { m_onMouseMove = std::move(cb); }
	void SetOnMouseDown(MouseButtonCallback cb) { m_onMouseDown = std::move(cb); }
	void SetOnMouseUp(MouseButtonCallback cb)	{ m_onMouseUp = std::move(cb); }
	void SetOnKeyDown(KeyCallback         cb)	{ m_onKeyDown = std::move(cb); } 
	void SetOnKeyUp(KeyCallback         cb)		{ m_onKeyUp = std::move(cb); } 
	void SetOnResize(ResizeCallback      cb)	{ m_onResize = std::move(cb); } 

	bool			Create(const wchar_t* className, const wchar_t* windowName, int width, int height);
	void			Destroy();
	void*			GetHandle() const { return m_hWnd; }
	int				GetWidth() const { return m_width; }
	int				GetHeight() const { return m_height; }
	virtual void	OnClose() abstract;

protected:
	friend LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lParam);
	virtual void OnResize(int width, int height);
	virtual void ProcessInput() abstract;

	WndBase(const WndBase&) = delete;
	WndBase& operator=(const WndBase&) = delete;
	WndBase(WndBase&&) = delete;
	WndBase& operator=(WndBase&&) = delete;

protected :
	HWND m_hWnd = HWND();
	int m_width = 0;
	int m_height = 0;

private :
	MouseMoveCallback	m_onMouseMove;
	MouseButtonCallback m_onMouseDown;
	MouseButtonCallback m_onMouseUp;
	KeyCallback			m_onKeyDown;
	KeyCallback			m_onKeyUp;
	ResizeCallback		m_onResize;
};