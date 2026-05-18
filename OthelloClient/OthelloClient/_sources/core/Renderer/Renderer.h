#pragma once
class Scene;

class Renderer abstract
{
public:
    virtual ~Renderer() = default;
    virtual void Initialize(void* hwnd) = 0;
    virtual void BeginFrame() = 0;
    virtual void RenderScene(Scene* scene) = 0;
    virtual void RenderFPS(float fps) = 0;
    virtual void EndFrame() = 0;

protected:
    HWND m_hwnd = nullptr;
    HDC m_hdc = nullptr;
    HDC m_memDC = nullptr;
    int m_width = 0;
    int m_height = 0;

    // 서브클래스가 메모리 DC에 렌더링하기 위해 제공
    HDC GetMemoryDC() const { return m_memDC; }
};