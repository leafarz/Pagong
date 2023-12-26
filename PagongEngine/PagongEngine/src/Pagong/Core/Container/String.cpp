#include "pch.h"
#include "Pagong/Core/Container/String.h"

namespace Pagong::String
{
    string ToString(const wstring& ws)
    {
        return std::string(ws.begin(), ws.end());
    }

    wstring ToWString(const string& s)
    {
        return wstring(s.begin(), s.end());
    }

    string Printf(const string& msg, ...)
    {
        char buf[MAX_BUFFER_SIZE];
        memset(&buf, 0, sizeof(buf));

        int32 result = -1;
        const char* msgPtr = msg.c_str();
        GET_VA_ARGS(buf, MAX_BUFFER_SIZE, msgPtr, msg.c_str(), result);
        return result < sizeof(buf) ? buf : msg;
    }
}
