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


    private:
        bool LoadPNG(const wchar_t* filePath);
        bool LoadBMP(const wchar_t* filePath);

    private:
        HBITMAP m_hBitmap = nullptr;
        int     m_imgWidth = 0;
        int     m_imgHeight = 0;
    };
}