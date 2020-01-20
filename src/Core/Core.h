#pragma once
#include "Utils/Performance.h"

#if FB_DEBUG
	#define FB_ASSERT(x, ...) { if(!(x)) { FB_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define FB_CORE_ASSERT(x, ...) { if(!(x)) { FB_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#elif FB_RELEASE
	#define FB_ASSERT(x, ...) { if(!(x)) { FB_ERROR("Assertion Failed: {0}", __VA_ARGS__); } }
	#define FB_CORE_ASSERT(x, ...) { if(!(x)) { FB_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); } }
#else
	#define FB_ASSERT(x, ...) {x;}
	#define FB_CORE_ASSERT(x, ...) {x;}
#endif

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