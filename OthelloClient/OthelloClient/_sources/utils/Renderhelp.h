#pragma once
#include <wincodec.h>

namespace renderHelp
{
    struct BitmapInfo
    {
        explicit BitmapInfo(HBITMAP hBitmap)
        {
            m_hBitmap = hBitmap;

            BITMAP bm;
            if (GetObject(hBitmap, sizeof(BITMAP), &bm))
            {
                m_width = bm.bmWidth;
                m_height = bm.bmHeight;
            }
        }

        ~BitmapInfo()
        {
            if (m_hBitmap)
            {
                DeleteObject(m_hBitmap);
                m_hBitmap = nullptr;
            }
        }

        BitmapInfo(const BitmapInfo&) = delete;
        BitmapInfo& operator=(const BitmapInfo&) = delete;

        HBITMAP m_hBitmap = nullptr;
        int     m_width = 0;
        int     m_height = 0;
    };

    // WIC 초기화 (Engine::Initialize 에서 1회 호출)
    bool Initialize();

    // PNG/BMP 로드 → BitmapInfo 반환 (실패 시 nullptr)
    BitmapInfo* CreateBitmapInfo(LPCWSTR filename);
}