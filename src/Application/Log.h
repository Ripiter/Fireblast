#pragma once
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace Fireblast {
	class Log
	{
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	public:
		static void Init();
	public:
		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	};
}

// MACROS
#define FB_CORE_INFO(...)		::Fireblast::Log::GetCoreLogger()->info(__VA_ARGS__)
#define FB_CORE_TRACE(...)		::Fireblast::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define FB_CORE_WARN(...)		::Fireblast::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define FB_CORE_ERROR(...)		::Fireblast::Log::GetCoreLogger()->error(__VA_ARGS__)
#define FB_CORE_CRITICAL(...)	::Fireblast::Log::GetCoreLogger()->critical(__VA_ARGS__)

#define FB_INFO(...)			::Fireblast::Log::GetClientLogger()->info(__VA_ARGS__)
#define FB_TRACE(...)			::Fireblast::Log::GetClientLogger()->trace(__VA_ARGS__)
#define FB_WARN(...)			::Fireblast::Log::GetClientLogger()->warn(__VA_ARGS__)
#define FB_ERROR(...)			Fireblast::Log::GetClientLogger()->error(__VA_ARGS__)
#define FB_CRITICAL(...)		::Fireblast::Log::GetClientLogger()->critical(__VA_ARGS__)