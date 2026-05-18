#pragma once
#include <string>
#include <mutex>

// ============================================================
//  LogType : 콘솔에 출력될 로그 유형
//  (Windows 헤더의 ERROR 매크로와 충돌 방지를 위해 ERR 사용)
// ============================================================
enum class LogType : uint8_t
{
	INFO    = 0,
	WARNING = 1,
	ERR     = 2,
	DEBUG   = 3,
	NETWORK = 4,
	GAME    = 5,
};

// ============================================================
//  DebugConsole
//  - 싱글톤 전역 디버그 콘솔 클래스
//  - [HH:MM:SS.mmm] [TYPE   ] 메시지 형식으로 출력
//  - LogType별 색상 구분 (Windows Console API)
// ============================================================
class DebugConsole
{
public:
	// 싱글톤 인스턴스
	static DebugConsole& GetInstance();

	// ── 타입별 단축 함수 ─────────────────────────────
	void Info   (const char* fmt, ...);
	void Warning(const char* fmt, ...);
	void Error  (const char* fmt, ...);
	void Debug  (const char* fmt, ...);
	void Network(const char* fmt, ...);
	void Game   (const char* fmt, ...);

	// ── 범용 로그 함수 ───────────────────────────────
	void Log(LogType type, const char* fmt, ...);

	// ── 설정 ─────────────────────────────────────────
	void SetEnabled(bool enabled);          // 전체 출력 on/off
	void SetFilter(LogType type, bool show);// 특정 타입 필터

private:
	DebugConsole();
	~DebugConsole() = default;
	DebugConsole(const DebugConsole&) = delete;
	DebugConsole& operator=(const DebugConsole&) = delete;

	void        LogInternal(LogType type, const char* message);
	std::string GetTimeString() const;
	const char* GetTypeLabel(LogType type) const;
	void        SetColor(LogType type) const;
	void        ResetColor() const;

private:
	bool      m_enabled             = true;
	bool      m_filter[6]           = { true, true, true, true, true, true };
	HANDLE    m_hConsole            = INVALID_HANDLE_VALUE;
	std::mutex m_mutex;
};

// ============================================================
//  전역 매크로 단축키
//  사용 예) LOG_INFO("FPS : %.1f", fps);
// ============================================================
#define LOG_INFO(...)    DebugConsole::GetInstance().Info   (__VA_ARGS__)
#define LOG_WARN(...)    DebugConsole::GetInstance().Warning(__VA_ARGS__)
#define LOG_ERROR(...)   DebugConsole::GetInstance().Error  (__VA_ARGS__)
#define LOG_DEBUG(...)   DebugConsole::GetInstance().Debug  (__VA_ARGS__)
#define LOG_NET(...)     DebugConsole::GetInstance().Network(__VA_ARGS__)
#define LOG_GAME(...)    DebugConsole::GetInstance().Game   (__VA_ARGS__)
