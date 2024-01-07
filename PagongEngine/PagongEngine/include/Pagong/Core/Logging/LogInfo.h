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
		int32 Line;
		LogLevel LogLevel;
	};
}
