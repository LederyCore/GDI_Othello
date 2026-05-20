#include "pch.h"
#include "GDISpriteRenderer.h"
#include "../Engine/GameObject.h"
#include "../components/Transform.h"
#include "../utils/DebugConsole.h"
#include "../utils/Vector2f.h"

#pragma comment(lib, "windowscodecs.lib")
#pragma comment(lib, "msimg32.lib")

OthelloComponent::GDISpriteRenderer::~GDISpriteRenderer()
{
    if (m_hBitmap)
    {
        DeleteObject(m_hBitmap);
        m_hBitmap = nullptr;
    }
}

void OthelloComponent::GDISpriteRenderer::Awake() {}
void OthelloComponent::GDISpriteRenderer::OnEnable() {}
void OthelloComponent::GDISpriteRenderer::Start() {}
void OthelloComponent::GDISpriteRenderer::OnDisable() {}

bool OthelloComponent::GDISpriteRenderer::LoadSprite(const wchar_t* filePath)
{
    const wchar_t* ext = wcsrchr(filePath, L'.');
    if (!ext)
    {
        LOG_ERROR("LoadSprite: no extension - %ls", filePath);
        return false;
    }

    bool ok = (_wcsicmp(ext, L".png") == 0) ? LoadPNG(filePath) : LoadBMP(filePath);

    if (ok)
    {
        LOG_INFO("LoadSprite OK : %ls (%dx%d)", filePath, m_imgWidth, m_imgHeight);
    }
    else
    {
        LOG_ERROR("LoadSprite FAILED : %ls", filePath);
    }

    return ok;
}

bool OthelloComponent::GDISpriteRenderer::LoadPNG(const wchar_t* filePath)
{
    if (m_hBitmap) { DeleteObject(m_hBitmap); m_hBitmap = nullptr; }

    IWICImagingFactory* pFactory = nullptr;
    IWICBitmapDecoder* pDecoder = nullptr;
    IWICBitmapFrameDecode* pFrame = nullptr;
    IWICFormatConverter* pConverter = nullptr;

    HRESULT hr = CoCreateInstance(
        CLSID_WICImagingFactory, nullptr,
        CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pFactory));
    if (FAILED(hr)) return false;

    hr = pFactory->CreateDecoderFromFilename(
        filePath, nullptr, GENERIC_READ,
        WICDecodeMetadataCacheOnLoad, &pDecoder);
    if (FAILED(hr)) goto CLEANUP;

    hr = pDecoder->GetFrame(0, &pFrame);
    if (FAILED(hr)) goto CLEANUP;

    hr = pFactory->CreateFormatConverter(&pConverter);
    if (FAILED(hr)) goto CLEANUP;

    hr = pConverter->Initialize(
        pFrame,
        GUID_WICPixelFormat32bppPBGRA,
        WICBitmapDitherTypeNone,
        nullptr, 0.0f,
        WICBitmapPaletteTypeCustom);
    if (FAILED(hr)) goto CLEANUP;

    {
        UINT w = 0, h = 0;
        pFrame->GetSize(&w, &h);
        m_imgWidth = (int)w;
        m_imgHeight = (int)h;

        BITMAPINFO bmi = {};
        bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
        bmi.bmiHeader.biWidth = m_imgWidth;
        bmi.bmiHeader.biHeight = -m_imgHeight;
        bmi.bmiHeader.biPlanes = 1;
        bmi.bmiHeader.biBitCount = 32;
        bmi.bmiHeader.biCompression = BI_RGB;

        void* pvBits = nullptr;
        HDC   hdc = GetDC(nullptr);
        m_hBitmap = CreateDIBSection(hdc, &bmi, DIB_RGB_COLORS, &pvBits, nullptr, 0);
        ReleaseDC(nullptr, hdc);

        if (!m_hBitmap) { hr = E_FAIL; goto CLEANUP; }

        hr = pConverter->CopyPixels(
            nullptr,
            m_imgWidth * 4,
            m_imgWidth * m_imgHeight * 4,
            (BYTE*)pvBits);
    }

CLEANUP:
    if (pConverter) pConverter->Release();
    if (pFrame)     pFrame->Release();
    if (pDecoder)   pDecoder->Release();
    if (pFactory)   pFactory->Release();

    if (FAILED(hr) && m_hBitmap)
    {
        DeleteObject(m_hBitmap);
        m_hBitmap = nullptr;
    }

    return SUCCEEDED(hr);
}

bool OthelloComponent::GDISpriteRenderer::LoadBMP(const wchar_t* filePath)
{
    if (m_hBitmap) { DeleteObject(m_hBitmap); m_hBitmap = nullptr; }

    m_hBitmap = (HBITMAP)LoadImage(
        nullptr, filePath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

    if (!m_hBitmap) return false;

    BITMAP bm;
    GetObject(m_hBitmap, sizeof(BITMAP), &bm);
    m_imgWidth = bm.bmWidth;
    m_imgHeight = bm.bmHeight;
    return true;
}

void OthelloComponent::GDISpriteRenderer::Render(HDC hdc)
{
    auto* tr = GetOwner()->GetComponent<OthelloComponent::Transform>();
    if (!tr) return;

    const Vector2f& pos = tr->GetPosition();
    const Vector2f& scale = tr->GetScale();

    // 정상 모드: 스프라이트 렌더링
    if (!m_hBitmap) return;

    HDC     memDC = CreateCompatibleDC(hdc);
    HBITMAP oldBitmap = (HBITMAP)SelectObject(memDC, m_hBitmap);

    BITMAP bm;
    GetObject(m_hBitmap, sizeof(BITMAP), &bm);

    if (bm.bmBitsPixel == 32)
    {
        BLENDFUNCTION bf = {};
        bf.BlendOp = AC_SRC_OVER;
        bf.BlendFlags = 0;
        bf.SourceConstantAlpha = 255;
        bf.AlphaFormat = AC_SRC_ALPHA;

        AlphaBlend(
            hdc,
            (int)pos.X, (int)pos.Y,
            (int)scale.X, (int)scale.Y,
            memDC,
            0, 0, m_imgWidth, m_imgHeight,
            bf);
    }
    else
    {
        StretchBlt(
            hdc,
            (int)pos.X, (int)pos.Y,
            (int)scale.X, (int)scale.Y,
            memDC,
            0, 0, m_imgWidth, m_imgHeight,
            SRCCOPY);
    }

    SelectObject(memDC, oldBitmap);
    DeleteDC(memDC);
}