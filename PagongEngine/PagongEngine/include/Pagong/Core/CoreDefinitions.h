#pragma once

#ifdef _WIN64

	#ifdef PAGONG_BUILD_DLL
		#define PAGONG_API __declspec(dllexport)
	#else
		#define PAGONG_API __declspec(dllimport)
	#endif

	#define _PG_EXPAND(x) x

#else // ----

	#error Platform not supported!

#endif

// -----------------------------------------------

#ifdef _MSC_VER
#define PG_DEBUGBREAK() __debugbreak()
#endif

#define MAX_BUFFER_SIZE 512
