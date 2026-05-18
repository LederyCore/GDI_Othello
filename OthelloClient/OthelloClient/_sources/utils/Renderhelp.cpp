#include "pch.h"
#include "RenderHelp.h"

#pragma comment(lib, "windowscodecs.lib")
#pragma comment(lib, "msimg32.lib")

namespace renderHelp
{
    struct WICInitializer
    {
        WICInitializer() = default;

        ~WICInitializer()
        {
            if (m_pFactory) { m_pFactory->Release(); m_pFactory = nullptr; }
            CoUninitialize();
        }

        bool Initialize()
        {
            HRESULT hr = CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED);
            if (FAILED(hr) && hr != RPC_E_CHANGED_MODE) return false;

            m_LastError = CoCreateInstance(
                CLSID_WICImagingFactory, nullptr,
                CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&m_pFactory));

            if (FAILED(m_LastError)) { m_pFactory = nullptr; return false; }

            return true;
        }

        bool LoadImageFromFile(LPCWSTR filename, HBITMAP& hBitmap)
        {
            hBitmap = nullptr;
            if (!m_pFactory) { m_LastError = E_FAIL; return false; }

            IWICBitmapDecoder* pDecoder = nullptr;
            IWICBitmapFrameDecode* pFrame = nullptr;
            IWICFormatConverter* pConverter = nullptr;

            auto Cleanup = [&]()
                {
                    if (pConverter) pConverter->Release();
                    if (pFrame)     pFrame->Release();
                    if (pDecoder)   pDecoder->Release();
                };

            m_LastError = m_pFactory->CreateDecoderFromFilename(
                filename, nullptr, GENERIC_READ,
                WICDecodeMetadataCacheOnLoad, &pDecoder);
            if (FAILED(m_LastError)) { Cleanup(); return false; }

            m_LastError = pDecoder->GetFrame(0, &pFrame);
            if (FAILED(m_LastError)) { Cleanup(); return false; }

            m_LastError = m_pFactory->CreateFormatConverter(&pConverter);
            if (FAILED(m_LastError)) { Cleanup(); return false; }

            m_LastError = pConverter->Initialize(
                pFrame, GUID_WICPixelFormat32bppPBGRA,
                WICBitmapDitherTypeNone, nullptr, 0.0f,
                WICBitmapPaletteTypeCustom);
            if (FAILED(m_LastError)) { Cleanup(); return false; }

            UINT width = 0, height = 0;
            pFrame->GetSize(&width, &height);

            BITMAPINFO bmi = {};
            bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
            bmi.bmiHeader.biWidth = (LONG)width;
            bmi.bmiHeader.biHeight = -(LONG)height;  // top-down
            bmi.bmiHeader.biPlanes = 1;
            bmi.bmiHeader.biBitCount = 32;
            bmi.bmiHeader.biCompression = BI_RGB;

            void* pvBits = nullptr;
            HDC   hdc = GetDC(nullptr);
            hBitmap = CreateDIBSection(hdc, &bmi, DIB_RGB_COLORS, &pvBits, nullptr, 0);
            ReleaseDC(nullptr, hdc);

            if (!hBitmap) { Cleanup(); return false; }

            m_LastError = pConverter->CopyPixels(
                nullptr, width * 4, width * height * 4, (BYTE*)pvBits);

            Cleanup();
            return SUCCEEDED(m_LastError);
        }

        WICInitializer(const WICInitializer&) = delete;
        WICInitializer& operator=(const WICInitializer&) = delete;

        HRESULT             m_LastError = S_OK;
        IWICImagingFactory* m_pFactory = nullptr;

    } GWICInitializer;  // 전역 인스턴스

    // --------------------------------------------------

    bool Initialize()
    {
        return GWICInitializer.Initialize();
    }

    BitmapInfo* CreateBitmapInfo(LPCWSTR filename)
    {
        HBITMAP hBitmap = nullptr;

        if (!GWICInitializer.LoadImageFromFile(filename, hBitmap))
        {
            LOG_ERROR("CreateBitmapInfo FAILED : %ls", filename);
            return nullptr;
        }

        return new BitmapInfo(hBitmap);
    }
}