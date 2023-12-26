#pragma once
#include "Pagong/Core/Logging/LogLevel.h"
#include "Pagong/Core/CoreTypes.h"

namespace Pagong
{
	struct LogInfo
	{
		string Msg;
		string Filepath;
		string Function;
		uint32 Line;
		LogLevel LogLevel;
	};
}
