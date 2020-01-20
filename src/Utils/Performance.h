#pragma once
#include "Core/Core.h"
#include "Application/Log.h"
#include <algorithm>
#include <chrono>
#include <fstream>
#include <iomanip>
#include <string>
#include <thread>
#include <sstream>

namespace Fireblast { namespace Debug {

	struct Performance
	{
		std::string FunctionName;
		long long StartTime;
		long long Duration;
	};

	class PerformanceWriter
	{
	private:
		std::string m_Path;
		std::ofstream m_OutPutStream;

	public:
		PerformanceWriter() : m_Path(), m_OutPutStream() {};
		~PerformanceWriter() {};
	public:
		inline void OpenFile(char* path)
		{
			m_Path = path;

			m_OutPutStream.open(m_Path);
			if (m_OutPutStream.is_open())
				WriteHeader();
			else
				FB_CORE_ERROR("Performance file could not be opened {0}", m_Path);
		};

		inline void CloseFile()
		{
			WriteFooter();
			m_OutPutStream.close();
		}

		inline void WriteHeader() 
		{
			m_OutPutStream << "{\"otherData\": {},\"traceEvents\":[";
			m_OutPutStream.flush();
		};

		inline void WriteFooter() 
		{
			m_OutPutStream << "]}";
			m_OutPutStream.flush();
		};

		inline void WriteProfile(const Performance& performance) 
		{
			std::stringstream json;

			std::string name = performance.FunctionName;
			std::replace(name.begin(), name.end(), '"', '\'');

			json << std::setprecision(3) << std::fixed;
			json << "{";
			json << "\"cat\":\"function\",";
			json << "\"dur\":" << (performance.Duration) << ',';
			json << "\"name\":\"" << name << "\",";
			json << "\"ph\":\"X\",";
			json << "\"pid\":0,";
			json << "\"tid\":" << 1 << ",";
			json << "\"ts\":" << performance.StartTime;
			json << "},\n";

			m_OutPutStream << json.str();
			m_OutPutStream.flush();
		};

	public:
		static PerformanceWriter& Get()
		{
			static PerformanceWriter instance;
			return instance;
		}
	};

	class PerformanceProfile
	{
	private:
		Performance* m_Profile;
	public:
		PerformanceProfile(const std::string& functionName)
		{
			m_Profile					= new Performance();
			m_Profile->FunctionName		= functionName;
			m_Profile->StartTime		= std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();
			m_Profile->Duration			= m_Profile->StartTime;
		};
		~PerformanceProfile()
		{
			Stop();
			delete m_Profile;
		}

	private:
		void Stop()
		{
			m_Profile->Duration = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now().time_since_epoch()).count() - m_Profile->StartTime;
			PerformanceWriter::Get().WriteProfile(*m_Profile);
		}
	};

}}

#if FB_DEBUG || FB_RELEASE
	#define FB_PERFORMANCE_STARTSESSION(path)		::Fireblast::Debug::PerformanceWriter::Get().OpenFile(path);
	#define FB_PERFORMANCE_PROFILE()				::Fireblast::Debug::PerformanceProfile performanceProfile(std::string(FB_GET_FUNCTION_NAME));
	#define FB_PERFORMANCE_ENDSESSION()				::Fireblast::Debug::PerformanceWriter::Get().CloseFile();
#else
	#define FB_PERFORMANCE_STARTSESSION(path)
	#define FB_PERFORMANCE_PROFILE()
	#define FB_PERFORMANCE_ENDSESSION()
#endif