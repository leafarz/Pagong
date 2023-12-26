#pragma once

#ifdef PG_ENABLE_ASSERTS

#define _PG_ASSERT_IMPL(check)				\
	{										\
		if (!(check))						\
		{									\
			PG_ERROR("Assertion failed");	\
			PG_DEBUGBREAK();				\
		}									\
	}

#define _PG_ASSERT_WITH_MSG_IMPL(check, msg, ...)						\
	{																	\
		if (!(check))													\
		{																\
			string errMsg = String::Printf("Assertion failed: %s", msg);\
			PG_ERROR(errMsg, __VA_ARGS__);								\
			PG_DEBUGBREAK();											\
		}																\
	}

#define _PG_ASSERT_GET_MACRO_NAME(check, msg, macro, ...) macro
#define _PG_ASSERT_GET_MACRO(...) _PG_EXPAND(_PG_ASSERT_GET_MACRO_NAME(__VA_ARGS__, _PG_ASSERT_WITH_MSG_IMPL, _PG_ASSERT_IMPL))


#define PG_ASSERT(...) _PG_EXPAND(_PG_ASSERT_GET_MACRO(__VA_ARGS__)(__VA_ARGS__))

#ifdef _DEBUG
#define PG_ASSERT_DEBUG(...) _PG_EXPAND(_PG_ASSERT_GET_MACRO(__VA_ARGS__)(__VA_ARGS__))
#else // ----
#define PG_ASSERT_DEBUG(...)
#endif

#else // ----

#define PG_ASSERT(...)
#define PG_ASSERT_DEBUG(...)

#endif
