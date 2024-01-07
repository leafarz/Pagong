#pragma once
#include "Pagong/Core/CoreTypes.h"

namespace Pagong::String
{
#define MAX_BUFFER_SIZE 256

#define GET_VA_ARGS(buf, size, lastarg, format, result)                 \
    {                                                                   \
        va_list ap;                                                     \
        va_start(ap, lastarg);                                          \
        result = vsnprintf(buf, sizeof(buf), (const char*)format, ap);  \
        va_end(ap);                                                     \
    }

    string PAGONG_API ToString(const wstring& ws);
    wstring PAGONG_API ToWString(const string& s);
    wstring PAGONG_API ToWString(int32 value);
    string PAGONG_API Printf(const string& msg, ...);
}
