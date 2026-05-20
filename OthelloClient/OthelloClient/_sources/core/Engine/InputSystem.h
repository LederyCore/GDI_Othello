#pragma once
#include "../utils/Vector2f.h"
#include <unordered_map>
class WndBase;

enum class MouseInput
{
    NONE, LEFT, RIGHT
};

struct MouseInputState
{
    MouseInput Btn = MouseInput::NONE;
    bool       IsPressed = false;
    Vector2f   Point;
};

struct KeyboardInputState
{
    std::unordered_map<int, bool> Keys; // keyCode → 눌림 여부
};

class InputSystem
{
public:
    InputSystem() = default;
    ~InputSystem() = default;

    void Initialize(WndBase* wnd);
    void Flush();

    void OnMouseMove(int x, int y);
    void OnMouseDown(int button, int x, int y);
    void OnMouseUp(int button, int x, int y);
    void OnKeyDown(int keyCode);
    void OnKeyUp(int keyCode);

    // 마우스
    static Vector2f& GetMousePosition();
    static bool      GetMouseButton(MouseInput btn);
    static bool      GetMouseButtonDown(MouseInput btn);
    static bool      GetMouseButtonUp(MouseInput btn);

    // 키보드
    static bool      GetKey(int keyCode); // 누르고 있는 중
    static bool      GetKeyDown(int keyCode); // 이번 프레임에 누른 순간
    static bool      GetKeyUp(int keyCode); // 이번 프레임에 뗀 순간
private:
    void BindToWindow(WndBase* wnd);

    // 마우스 버퍼
    static MouseInputState m_mouseState;
    static MouseInputState m_prevMouseState;
    static MouseInputState m_pendingMouseState;

    // 키보드 버퍼
    static KeyboardInputState m_keyState;
    static KeyboardInputState m_prevKeyState;
    static KeyboardInputState m_pendingKeyState;
};