#include "pch.h"

#ifdef _WIN64
namespace Pagong
{
	void PrintImpl(const char* msg)
	{
		OutputDebugStringA(msg);
	}
}
#endif
