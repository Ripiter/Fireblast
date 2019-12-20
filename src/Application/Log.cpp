#include "fbpch.h"
#include "Log.h"

#include "spdlog/sinks/stdout_color_sinks.h"


namespace Fireblast {

	std::shared_ptr<spdlog::logger> Log::s_ClientLogger;
	std::shared_ptr<spdlog::logger> Log::s_CoreLogger;

	void Log::Init() 
	{
		spdlog::set_pattern("%^[%T] %n: %v%$");
		s_CoreLogger = spdlog::stdout_color_mt("CoreLogger");
		s_CoreLogger->set_level(spdlog::level::trace);

		s_ClientLogger = spdlog::stdout_color_mt("ClientLogger");
		s_ClientLogger->set_level(spdlog::level::trace);

		FB_CORE_INFO("Core Logger Initialised");
		FB_INFO("Client Logger Initialised");
	}
}	