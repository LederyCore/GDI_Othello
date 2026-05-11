#pragma once
class WindowFactory
{
public :
	WindowFactory();
	HWND Create(const wchar_t* name, int width, int height);

private :
	HINSTANCE GetHInstance() { return GetModuleHandle(NULL); }
	WNDCLASSEXW SetWindowClass(const wchar_t* name);
};