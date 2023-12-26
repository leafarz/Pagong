#pragma once
#include "Pagong/Core/Container/String.h"
#include "Pagong/Core/Logging/Log.h"
#include "Pagong/Core/Logging/LogInfo.h"
#include <type_traits>

#define PG_LOG(msg, logLevel, ...)													\
	{																				\
		Pagong::string format = Pagong::String::Printf(msg, __VA_ARGS__);			\
		Pagong::LogInfo info{format, __FILE__, __FUNCTION__, __LINE__, logLevel };	\
		Pagong::Log::Output(info);													\
	}

#if _DEBUG

#define PG_WARN(msg, ...) PG_LOG(msg, Pagong::LogLevel::Warn, __VA_ARGS__)
#define PG_INFO(msg, ...) PG_LOG(msg, Pagong::LogLevel::Info, __VA_ARGS__)
#define PG_DEBUG(msg, ...) PG_LOG(msg, Pagong::LogLevel::Debug, __VA_ARGS__)
#define PG_VERBOSE(msg, ...) PG_LOG(msg, Pagong::LogLevel::Verbose, __VA_ARGS__)

#else

#define PG_WARN(msg, ...)
#define PG_INFO(msg, ...)
#define PG_DEBUG(msg, ...)
#define PG_VERBOSE(msg, ...)

#endif

#define PG_FATAL(msg, ...) PG_LOG(msg, Pagong::LogLevel::Fatal, __VA_ARGS__)
#define PG_ERROR(msg, ...) PG_LOG(msg, Pagong::LogLevel::Error, __VA_ARGS__)
