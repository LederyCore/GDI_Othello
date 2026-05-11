#pragma once
#include "BaseWindow.h"

class OthelloWindow : public BaseWindow
{
public :
	OthelloWindow(const wchar_t* name) : BaseWindow(name) { }
	virtual ~OthelloWindow() override;

protected :
	LRESULT MsgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) override;
};