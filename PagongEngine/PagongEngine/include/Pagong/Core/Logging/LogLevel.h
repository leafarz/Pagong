#pragma once
#include "Pagong/Core/CoreTypes.h"

namespace Pagong
{
	enum LogLevel : uint8
	{
		Fatal	= 1,
		Error	= 2,
		Warn	= 4,
		Info	= 8,
		Debug	= 16,
		Verbose = 32
	};

	string PAGONG_API ToString(LogLevel logLevel);
}
