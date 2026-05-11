// =============================================================================
// FILE:         WindowFactory.cpp
// DESCRIPTION:  윈도우 창 생성을 담당하는 클래스
// =============================================================================
//
// [책임 구현 / Responsibility Implementation]
//
//   <아는 것 / Knowing>
//     - validate()     : 결제 수단과 한도를 기반으로 승인 가능 여부 계산
//     - getLimit()     : 현재 설정된 결제 한도 반환
//
//   <하는 것 / Doing>
//     - Create(int width, int height)       : 가로 세로를 입력 받아 윈도우를 생성하고 그 윈도우의 핸들 포인터를 반환
//     - createReceipt(): ReceiptFactory를 통해 영수증 객체 생성
//
//
// [Notes]
//   - 알아두면 좋은 특이사항, 제약 조건, 레거시 이유 등
//   - TODO: 향후 개선이 필요한 항목
//
// -----------------------------------------------------------------------------
// AUTHOR:       이은수 <wwe2705@naver.com>
// CREATED:      2026-05-11
// UPDATED:      2026-05-11
// =============================================================================

#include "pch.h"
#include "WindowFactory.h"
#include "OthelloWindow.h"

WindowFactory::WindowFactory()
{

}

HWND WindowFactory::Create(const wchar_t* name, int width, int height)
{
    // 윈도우 클래스 설정
    WNDCLASSEXW wc = SetWindowClass(name);

    // 클래스 등록
    RegisterClassExW(&wc);

    // 메시지를 실제로 처리할 윈도우 클래스 인스턴스 생성
    BaseWindow* bw = new OthelloWindow(name);

    // 메모리에 생성한 윈도우 인스턴스를 커널에 전달하여 윈도우 핸들 반환
    HWND hWnd = CreateWindowExW(
        0,
        wc.lpszClassName,
        name,
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, width, height,
        NULL, NULL, GetHInstance(),
        bw);

    // 성공시 바로 화면 렌더링
    if (hWnd)
    {
        ShowWindow(hWnd, SW_SHOW);
        UpdateWindow(hWnd);
    }

	return hWnd;
}

WNDCLASSEXW WindowFactory::SetWindowClass(const wchar_t* name)
{
    WNDCLASSEXW wc = { };
    wc.cbSize = sizeof(WNDCLASSEXW);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = BaseWindow::StaticMsgRouter;
    wc.hInstance = GetHInstance();
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.lpszClassName = name;

    return wc;
}