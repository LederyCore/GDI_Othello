// =============================================================================
// FILE:         BasedWindow.cpp
// DESCRIPTION:  이 게임에 사용될 모든 윈도우의 공통 역할을 정의한 추상 클래스
// =============================================================================
//
// [책임 구현 / Responsibility Implementation]
//
//   <아는 것 / Knowing>
//     - 
//
//   <하는 것 / Doing>
//     - StaticMsgRouter : WM_NCCREATE 시 객체 포인터를 윈도우에 등록하고, 이후 메시지를 해당 객체의 MsgProc으로 전달한다.
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
#include "BaseWindow.h"


LRESULT BaseWindow::StaticMsgRouter(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    BaseWindow* pThis = nullptr;
    // WM_NCCREATE는 윈도우가 생성될 때 가장 먼저 오는 메시지.
    // 이때 객체 주소를 윈도우에 등록한다.
    if (uMsg == WM_NCCREATE)
    {
        // WM_NCCREATE일 때 lParam엔 CREATESTRUCT 구조체 포인터가 들어있음.
        // 이걸 꺼내는 것. CREATESTRUCT엔 CreateWindowEx() 호출 시 넘긴 정보가 담겨있다.
        // Windows API가 포인터를 LONG_PTR(정수) 또는 void*로 보관하기 때문에, 
        // reinterpret_cast를 사용하여 프로그래머가 사용하기 쉬운 포인터 형태로 바꿈
        LPCREATESTRUCTW pCreate = reinterpret_cast<LPCREATESTRUCTW>(lParam);
        // CREATESTRUCT.lpCreateParams는 CreateWindowEx()의 마지막 인자로 넘긴 값.
        pThis = reinterpret_cast<BaseWindow*>(pCreate->lpCreateParams);
        // 윈도우에 객체 주소 저장
        SetWindowLongPtrW(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pThis));
    }
    else
    {
        // 저장된 주소 불러오기
        pThis = reinterpret_cast<BaseWindow*>(GetWindowLongPtrW(hWnd, GWLP_USERDATA));
    }

    if (pThis)
    {
        return pThis->MsgProc(hWnd, uMsg, wParam, lParam);
    }
    return DefWindowProcW(hWnd, uMsg, wParam, lParam);
}