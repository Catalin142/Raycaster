#include "Core/RaycastPCH.h"

#include "Benchmark.h"

void Instrumentor::beginSession(const std::string& sessioname, const std::string& filepath)
{
	if (m_CurrentSession != sessioname)
	{
		m_jsonFile.open(filepath);
		m_CurrentSession = sessioname;
	}
	m_jsonFile << "{\"otherData\": {},\"traceEvents\":[{}\n";
	m_jsonFile.flush();
}

void Instrumentor::endSession()
{
	m_jsonFile << "]}\n";
	m_jsonFile.flush();
	m_jsonFile.close();
	m_ProfileCount = 0;
}

Instrumentor& Instrumentor::Get()
{
	static Instrumentor instance;
	return instance;
}

void Instrumentor::Write(const char* name, float duration, std::chrono::duration<double, std::micro> start, std::thread::id threadID)
{
	std::stringstream json;

	json << std::setprecision(3) << std::fixed;
	json << "\t,{\n";
	json << "\t\"cat\":\"function\",\n";
	json << "\t\"dur\":" << duration << ", \n";
	json << "\t\"name\":\"" << name << "\",\n";
	json << "\t\"ph\":\"X\",\n";
	json << "\t\"pid\":1,\n";
	json << "\t\"tid\":" << threadID << ",\n";
	json << "\t\"ts\":" << start.count() << "\n";
	json << "\t}";

	m_jsonFile << json.str();

	m_jsonFile.flush();
}


Timer::Timer(const char* functionName) : m_FunName(functionName)
{
	m_Time = std::chrono::steady_clock::now();
}

Timer::~Timer()
{
	if (!m_Stopped)
		Shutdown();
}

void Timer::Shutdown()
{
	auto end = std::chrono::steady_clock::now();
	auto elapsed = std::chrono::time_point_cast<std::chrono::microseconds>(end).time_since_epoch() -
		std::chrono::time_point_cast<std::chrono::microseconds>(m_Time).time_since_epoch();

	auto Start = std::chrono::duration<double, std::micro>{ m_Time.time_since_epoch() };

	Instrumentor::Get().Write(m_FunName, elapsed.count(), Start, std::this_thread::get_id());

	m_Stopped = true;
}