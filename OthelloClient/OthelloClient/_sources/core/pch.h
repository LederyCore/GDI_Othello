#pragma once

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#define VC_EXTRALEAN

#include <windows.h>
#include <windowsx.h>
#include <wincodec.h>

#pragma comment(lib, "windowscodecs.lib")  // WIC 라이브러리
#pragma comment(lib, "msimg32.lib")        // AlphaBlend 함수가 포함된 라이브러리

#include <vector>
#include <chrono>

#include "../utils/Vector2f.h"
#include "../utils/DebugConsole.h"