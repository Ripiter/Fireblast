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