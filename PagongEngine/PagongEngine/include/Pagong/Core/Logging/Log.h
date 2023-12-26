#pragma once
#include "Pagong/Platform/Platform.h"
#include "Pagong/Core/Logging/LogInfo.h"
#include "Pagong/Core/CoreTypes.h"

namespace Pagong
{
	class PAGONG_API Log
	{
	public:
		static void SetLogLevel(LogLevel logLevel);

		static LogLevel GetCurrentLogLevel();

		static bool CanLog(LogLevel logLevel);
		static void Output(LogLevel logLevel, const string& msg);
		static void Output(const LogInfo& logInfo);

		template<typename... Types>
		static void Format(LogLevel logLevel, const string& msg, Types... args)
		{
			if (!CanLog(logLevel))
			{
				return;
			}
			string str = String::Printf(msg, args...);
			OutputImpl(logLevel, str);
		}

	private:
		Log(void) = delete;
		~Log(void) = delete;

		static void OutputImpl(LogLevel logLevel, const string& msg);
		static void OutputImpl(const LogInfo& logInfo);

	private:
		static LogLevel s_LogLevel;
	};
}
