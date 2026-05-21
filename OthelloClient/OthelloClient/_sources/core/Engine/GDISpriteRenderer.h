#pragma once
#include "../Engine/Component.h"
#include <wincodec.h>

namespace OthelloComponent
{
    class GDISpriteRenderer : public Component
    {
    public:
        GDISpriteRenderer() = default;
        virtual ~GDISpriteRenderer() override;

        void Awake()         override;
        void OnEnable()      override;
        void Start()         override;
        void Render(HDC hdc) override;
        void OnDisable()     override;

        bool LoadSprite(const wchar_t* filePath);

        int GetWidth()  const { return m_imgWidth; }
        int GetHeight() const { return m_imgHeight; }

        void SetAlpha(int targetAlpha);
        void SetBrightness(float brightness); // 0.0 ~ 1.0
    private:
        bool LoadPNG(const wchar_t* filePath);
        bool LoadBMP(const wchar_t* filePath);
        void ApplyBrightness(); // 내부 적용 함수

    private:
        HBITMAP m_hBitmap = nullptr;
        int     m_imgWidth = 0;
        int     m_imgHeight = 0;
        int     m_targetAlpha = 255;

        std::vector<BYTE> m_originalPixels; // 원본 픽셀 백업
        float m_brightness = 1.0f;          // 1.0 = 원본, 0.0 = 검정
    };
}