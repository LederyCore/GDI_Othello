#include "pch.h"
#include "DebugConsole.h"

// Debug 빌드에서만 cpp 내용 컴파일
#ifdef _DEBUG

#include <cstdarg>
#include <cstdio>
#include <cassert>

namespace {
    constexpr WORD DC_COLOR_DEFAULT = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
    constexpr WORD DC_COLOR_INFO = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
    constexpr WORD DC_COLOR_WARNING = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
    constexpr WORD DC_COLOR_ERR = FOREGROUND_RED | FOREGROUND_INTENSITY;
    constexpr WORD DC_COLOR_DEBUG = FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY;
    constexpr WORD DC_COLOR_NETWORK = FOREGROUND_GREEN | FOREGROUND_INTENSITY;
    constexpr WORD DC_COLOR_GAME = FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY;

    constexpr WORD TYPE_COLORS[] = {
        DC_COLOR_INFO, DC_COLOR_WARNING, DC_COLOR_ERR,
        DC_COLOR_DEBUG, DC_COLOR_NETWORK, DC_COLOR_GAME,
    };

    constexpr int BUFFER_SIZE = 1024;
    constexpr int TYPE_COUNT = 6;
}

DebugConsole& DebugConsole::GetInstance()
{
    static DebugConsole instance;
    return instance;
}

DebugConsole::DebugConsole()
{
    m_hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
}

void DebugConsole::Info(const char* fmt, ...) { char buf[BUFFER_SIZE]; va_list a; va_start(a, fmt); vsnprintf(buf, sizeof(buf), fmt, a); va_end(a); LogInternal(LogType::INFO, buf); }
void DebugConsole::Warning(const char* fmt, ...) { char buf[BUFFER_SIZE]; va_list a; va_start(a, fmt); vsnprintf(buf, sizeof(buf), fmt, a); va_end(a); LogInternal(LogType::WARNING, buf); }
void DebugConsole::Error(const char* fmt, ...) { char buf[BUFFER_SIZE]; va_list a; va_start(a, fmt); vsnprintf(buf, sizeof(buf), fmt, a); va_end(a); LogInternal(LogType::ERR, buf); }
void DebugConsole::Debug(const char* fmt, ...) { char buf[BUFFER_SIZE]; va_list a; va_start(a, fmt); vsnprintf(buf, sizeof(buf), fmt, a); va_end(a); LogInternal(LogType::DEBUG, buf); }
void DebugConsole::Network(const char* fmt, ...) { char buf[BUFFER_SIZE]; va_list a; va_start(a, fmt); vsnprintf(buf, sizeof(buf), fmt, a); va_end(a); LogInternal(LogType::NETWORK, buf); }
void DebugConsole::Game(const char* fmt, ...) { char buf[BUFFER_SIZE]; va_list a; va_start(a, fmt); vsnprintf(buf, sizeof(buf), fmt, a); va_end(a); LogInternal(LogType::GAME, buf); }

void DebugConsole::Log(LogType type, const char* fmt, ...)
{
    char buf[BUFFER_SIZE];
    va_list a;
    va_start(a, fmt);
    vsnprintf(buf, sizeof(buf), fmt, a);
    va_end(a);
    LogInternal(type, buf);
}

void DebugConsole::SetEnabled(bool enabled) { m_enabled = enabled; }

void DebugConsole::SetFilter(LogType type, bool show)
{
    const int idx = static_cast<int>(type);
    assert(idx >= 0 && idx < TYPE_COUNT);
    m_filter[idx] = show;
}

void DebugConsole::LogInternal(LogType type, const char* message)
{
    const int idx = static_cast<int>(type);
    if (!m_enabled)     return;
    if (!m_filter[idx]) return;

    const std::string timeStr = GetTimeString();
    const char* label = GetTypeLabel(type);

    std::lock_guard<std::mutex> lock(m_mutex);
    ResetColor();
    printf("[%s] ", timeStr.c_str());
    SetColor(type);
    printf("[%-7s] ", label);
    ResetColor();
    printf("%s\n", message);
}

std::string DebugConsole::GetTimeString() const
{
    SYSTEMTIME st;
    GetLocalTime(&st);
    char buf[32];
    snprintf(buf, sizeof(buf), "%02d:%02d:%02d.%03d",
        st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);
    return buf;
}

const char* DebugConsole::GetTypeLabel(LogType type) const
{
    switch (type) {
    case LogType::INFO:    return "INFO";
    case LogType::WARNING: return "WARNING";
    case LogType::ERR:     return "ERROR";
    case LogType::DEBUG:   return "DEBUG";
    case LogType::NETWORK: return "NETWORK";
    case LogType::GAME:    return "GAME";
    default:               return "UNKNOWN";
    }
}

void DebugConsole::SetColor(LogType type) const
{
    if (m_hConsole == INVALID_HANDLE_VALUE) return;
    SetConsoleTextAttribute(m_hConsole, TYPE_COLORS[static_cast<int>(type)]);
}

void DebugConsole::ResetColor() const
{
    if (m_hConsole == INVALID_HANDLE_VALUE) return;
    SetConsoleTextAttribute(m_hConsole, DC_COLOR_DEFAULT);
}

#endif // _DEBUG