#include "pch.h"
#include "Pagong/Core/Logging/LogLevel.h"

namespace Pagong
{
	string ToString(LogLevel logLevel)
	{
		switch (logLevel)
		{
		case LogLevel::Fatal: return "Fatal";
		case LogLevel::Error: return "Error";
		case LogLevel::Warn: return "Warn";
		case LogLevel::Info: return "Info";
		case LogLevel::Debug: return "Debug";
		case LogLevel::Verbose: return "Verbose";
		default: return "Unknown";
		}
	}
}
