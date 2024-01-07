#pragma once
#include <comdef.h>

#ifdef _DEBUG

#define DXCHECK(x)                                          \
    {                                                       \
        HRESULT hr = x;                                     \
        if(FAILED(hr))                                      \
        {                                                   \
            _com_error e(hr);                               \
            PG_ERROR(String::ToString(e.ErrorMessage()));   \
            throw std::exception();                         \
        }                                                   \
    }

#else // ----

#define DXCHECK(x) x

#endif
