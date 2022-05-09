#pragma once
#include <chrono>

class Instrumentor
{
	friend class Timer;

public:
	void beginSession(const std::string& sessioname, const std::string& filepath = "profile.json");
	void endSession();

	static Instrumentor& Get();

private:
	std::string m_CurrentSession;
	std::ofstream m_jsonFile;
	int m_ProfileCount;

private:
	Instrumentor() : m_ProfileCount(0) { }
	~Instrumentor() = default;

	void Write(const char* name, float duration, std::chrono::duration<double, std::micro> start, std::thread::id threadID);
};

class Timer
{
public:
	Timer(const char* functionName);
	~Timer();
	void Shutdown();

private:
	std::chrono::time_point<std::chrono::steady_clock> m_Time;
	const char* m_FunName;
	bool m_Stopped = false;
};

#if DEBUG == 1
#define START_SCOPE_PROFILE(name) Timer time##__LINE__(name)
#define BEGIN_SESSION(name, file) Instrumentor::Get().beginSession(name, file)
#define END_SESSION 			  Instrumentor::Get().endSession()

#elif RELEASE == 1
#define START_SCOPE_PROFILE(name)
#define BEGIN_SESSION(name, file)
#define END_SESSION
#endif