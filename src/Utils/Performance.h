#pragma once

#include "Application/Log.h"
#include <algorithm>
#include <chrono>
#include <fstream>
#include <iomanip>
#include <string>
#include <thread>
#include <sstream>


// TODO: Performance counter can only be at
// The lowest function at a time
// This means that the performance counter isn't as precise
// As it should be. This can be fixed by creating objects 
// With a lifetime of the function, and writing those
// Profiles when they die. 

namespace Fireblast { namespace Debug {

	struct PerformanceCounter
	{
		std::string Name;
		long long Start;
		long long Duration;
	};

	class PerformanceInstrument
	{
	private:
		char* m_FilePath;
		std::ofstream m_OutputStream;	
		PerformanceCounter* m_CurrentProfile;
	public:
		PerformanceInstrument()
			:  m_FilePath(nullptr), m_CurrentProfile(nullptr) {}
		virtual ~PerformanceInstrument() {}
	public:
		void StartSession(char* filepath) 
		{ 
			m_FilePath = filepath;

			m_OutputStream.open(filepath);
			if (m_OutputStream.is_open())
				WriteHeaderToOutput();
			else
				FB_CORE_ERROR("Performance Stream could not be opened");

		}

		void StartFunctionProfiling(const std::string& name)
		{
			AddPerformance(name);
		}

		void EndFunctionProfiling()
		{
			m_CurrentProfile->Duration = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now().time_since_epoch()).count() - m_CurrentProfile->Start;
			WriteProfileToOutput(*m_CurrentProfile);
		}

		void EndSession()
		{
			WriteFooterToOutput();
			m_OutputStream.close();

			delete m_CurrentProfile;
		}

	private:
		void AddPerformance(const std::string& name) 
		{
			PerformanceCounter* pc = new PerformanceCounter();
			pc->Name = name;
			pc->Start = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();
			pc->Duration = pc->Start;
			m_CurrentProfile = pc;
		}

		void WriteHeaderToOutput()
		{
			m_OutputStream << "{\"otherData\": {},\"traceEvents\":[";
			m_OutputStream.flush();
		}

		void WriteFooterToOutput()
		{
			m_OutputStream << "]}";
			m_OutputStream.flush();
		}

		void WriteProfileToOutput(const PerformanceCounter& profile)
		{
			std::stringstream json;

			std::string name = profile.Name;
			std::replace(name.begin(), name.end(), '"', '\'');

			json << std::setprecision(3) << std::fixed;
			json << "{";
			json << "\"cat\":\"function\",";
			json << "\"dur\":" << (profile.Duration) << ',';
			json << "\"name\":\"" << name << "\",";
			json << "\"ph\":\"X\",";
			json << "\"pid\":0,";
			json << "\"tid\":" << 1 << ",";
			json << "\"ts\":" << profile.Start;
			json << "},\n";

			m_OutputStream << json.str();
			m_OutputStream.flush();
		}

	public:
		static PerformanceInstrument& Get()
		{
			static PerformanceInstrument instance;
			return instance;
		}
	};

#if defined(__GNUC__) || (defined(__MWERKS__) && (__MWERKS__ >= 0x3000)) || (defined(__ICC) && (__ICC >= 600)) || defined(__ghs__)
	#define FB_GET_FUNCTION_NAME  __PRETTY_FUNCTION__
#elif defined(__DMC__) && (__DMC__ >= 0x810)
	#define FB_GET_FUNCTION_NAME __PRETTY_FUNCTION__
#elif defined(__FUNCSIG__)
	#define FB_GET_FUNCTION_NAME __FUNCSIG__
#elif (defined(__INTEL_COMPILER) && (__INTEL_COMPILER >= 600)) || (defined(__IBMCPP__) && (__IBMCPP__ >= 500))
	#define FB_GET_FUNCTION_NAME __FUNCTION__
#elif defined(__BORLANDC__) && (__BORLANDC__ >= 0x550)
	#define FB_GET_FUNCTION_NAME __FUNC__
#elif defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901)
	#define FB_GET_FUNCTION_NAME __func__
#elif defined(__cplusplus) && (__cplusplus >= 201103)
	#define FB_GET_FUNCTION_NAME __func__
#else
	#define FB_GET_FUNCTION_NAME "Unknow_Function_Name"
#endif

#if FB_DEBUG || FB_RELEASE
	#define FB_PERFORMANCE_FUNCTIONNAME ::Fireblast::Debug::PerformanceInstrument::Get().GetFunctionName()
	#define FB_PERFORMANCE_STARTSESSION(path) ::Fireblast::Debug::PerformanceInstrument::Get().StartSession(path);
	#define FB_PERFORMANCE_START_PROFILEFUNCTION() ::Fireblast::Debug::PerformanceInstrument::Get().StartFunctionProfiling(std::string(FB_GET_FUNCTION_NAME));
	#define FB_PERFORMANCE_END_PROFILEFUNCTION() ::Fireblast::Debug::PerformanceInstrument::Get().EndFunctionProfiling();
	#define FB_PERFORMANCE_ENDSESSION() ::Fireblast::Debug::PerformanceInstrument::Get().EndSession();
#else
	#define FB_PERFORMANCE_STARTSESSION(path)
	#define FB_PERFORMANCE_FUNCTIONNAME()
	#define FB_PERFORMANCE_PROFILEFUNCTION()
	#define FB_PERFORMANCE_ENDSESSION()
#endif

}}