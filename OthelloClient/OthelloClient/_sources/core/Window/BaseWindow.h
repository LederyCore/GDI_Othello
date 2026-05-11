#pragma once
class BaseWindow
{
public :
	BaseWindow(const wchar_t* name) : m_name(name) { }
	virtual ~BaseWindow() = default;
	static LRESULT CALLBACK StaticMsgRouter(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

protected :
	virtual LRESULT MsgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) = 0;

private :
	const wchar_t* m_name;
};