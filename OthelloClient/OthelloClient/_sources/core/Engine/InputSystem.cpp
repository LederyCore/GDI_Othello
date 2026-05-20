#include "pch.h"
#include "InputSystem.h"
#include "../Window/WndBase.h"

// 마우스 버퍼
MouseInputState InputSystem::m_mouseState = {};
MouseInputState InputSystem::m_prevMouseState = {};
MouseInputState InputSystem::m_pendingMouseState = {};

// 키보드 버퍼
KeyboardInputState InputSystem::m_keyState = {};
KeyboardInputState InputSystem::m_prevKeyState = {};
KeyboardInputState InputSystem::m_pendingKeyState = {};

void InputSystem::Initialize(WndBase* wnd)
{
    BindToWindow(wnd);
}

void InputSystem::BindToWindow(WndBase* wnd)
{
    wnd->SetOnMouseMove([this](int x, int y) { OnMouseMove(x, y);      });
    wnd->SetOnMouseDown([this](int btn, int x, int y) { OnMouseDown(btn, x, y); });
    wnd->SetOnMouseUp([this](int btn, int x, int y) { OnMouseUp(btn, x, y);   });
    wnd->SetOnKeyDown([this](int key) { OnKeyDown(key);         });
    wnd->SetOnKeyUp([this](int key) { OnKeyUp(key);           });
}

// 윈도우로부터 입력 수신
void InputSystem::OnMouseMove(int x, int y)
{
    m_pendingMouseState.Point = { (float)x, (float)y };
}

void InputSystem::OnMouseDown(int button, int x, int y)
{
    m_pendingMouseState.Point = { (float)x, (float)y };
    m_pendingMouseState.IsPressed = true;
    m_pendingMouseState.Btn = (button == 0) ? MouseInput::LEFT
        : (button == 1) ? MouseInput::RIGHT
        : MouseInput::NONE;
}

void InputSystem::OnMouseUp(int button, int x, int y)
{
    m_pendingMouseState.Point = { (float)x, (float)y };
    m_pendingMouseState.IsPressed = false;
    m_pendingMouseState.Btn = MouseInput::NONE;
}

void InputSystem::OnKeyDown(int keyCode)
{
    m_pendingKeyState.Keys[keyCode] = true;
}

void InputSystem::OnKeyUp(int keyCode)
{
    m_pendingKeyState.Keys[keyCode] = false;
}

void InputSystem::Flush()
{
    // 마우스
    m_prevMouseState = m_mouseState;
    m_mouseState = m_pendingMouseState;

    // 키보드
    m_prevKeyState = m_keyState;
    m_keyState = m_pendingKeyState;
}

// 마우스 접근자
Vector2f& InputSystem::GetMousePosition()
{
    return m_mouseState.Point;
}

bool InputSystem::GetMouseButton(MouseInput btn)
{
    return m_mouseState.IsPressed && m_mouseState.Btn == btn;
}

bool InputSystem::GetMouseButtonDown(MouseInput btn)
{
    return  m_mouseState.IsPressed && m_mouseState.Btn == btn
        && !m_prevMouseState.IsPressed;
}

bool InputSystem::GetMouseButtonUp(MouseInput btn)
{
    return !m_mouseState.IsPressed
        && m_prevMouseState.IsPressed && m_prevMouseState.Btn == btn;
}

// 키보드 접근자
bool InputSystem::GetKey(int keyCode)
{
    auto it = m_keyState.Keys.find(keyCode);
    return it != m_keyState.Keys.end() && it->second;
}

bool InputSystem::GetKeyDown(int keyCode)
{
    auto curr = m_keyState.Keys.find(keyCode);
    auto prev = m_prevKeyState.Keys.find(keyCode);

    bool currPressed = (curr != m_keyState.Keys.end()) && curr->second;
    bool prevPressed = (prev != m_prevKeyState.Keys.end()) && prev->second;

    return currPressed && !prevPressed;  // 이번 프레임에 처음 눌림
}

bool InputSystem::GetKeyUp(int keyCode)
{
    auto curr = m_keyState.Keys.find(keyCode);
    auto prev = m_prevKeyState.Keys.find(keyCode);

    bool currPressed = (curr != m_keyState.Keys.end()) && curr->second;
    bool prevPressed = (prev != m_prevKeyState.Keys.end()) && prev->second;

    return !currPressed && prevPressed;  // 이번 프레임에 뗌
}