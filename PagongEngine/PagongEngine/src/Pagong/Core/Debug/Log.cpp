#include "pch.h"
#include "Pagong/Core/Logging/Log.h"

namespace Pagong
{
	LogLevel Log::s_LogLevel = LogLevel::Debug;

	void Log::SetLogLevel(LogLevel logLevel)
	{
		s_LogLevel = std::max(LogLevel::Error, logLevel);
	}

	LogLevel Log::GetCurrentLogLevel()
	{
		return s_LogLevel;
	}

	bool Log::CanLog(LogLevel logLevel)
	{
		return logLevel <= s_LogLevel;
	}

	void Log::Output(LogLevel logLevel, const string& msg)
	{
		if (!CanLog(logLevel))
		{
			return;
		}
		OutputImpl(logLevel, msg);
	}

	void Log::Output(const LogInfo& logInfo)
	{
		if (!CanLog(logInfo.LogLevel))
		{
			return;
		}

		OutputImpl(logInfo);
	}

	void Log::OutputImpl(LogLevel logLevel, const string& msg)
	{
		char buf[MAX_BUFFER_SIZE];
		sprintf_s(buf, "[%s] %s\n", ToString(logLevel).c_str(), msg.c_str());
		PrintImpl(buf);
	}

	void Log::OutputImpl(const LogInfo& logInfo)
	{
		char buf[MAX_BUFFER_SIZE];
		sprintf_s(buf, "[%s] %s\n: [%s() - %s:%d]\n",
			ToString(logInfo.LogLevel).c_str(),
			logInfo.Msg.c_str(),
			logInfo.Function.c_str(),
			logInfo.Filepath.c_str(),
			logInfo.Line
		);
		PrintImpl(buf);
	}
}
