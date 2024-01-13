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

const D3D_FEATURE_LEVEL MIN_FEATURE_LEVEL = D3D_FEATURE_LEVEL_12_2;
