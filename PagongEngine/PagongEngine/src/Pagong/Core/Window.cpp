#include "pch.h"
#include "Pagong/Core/Window.h"

#ifdef _WIN64
    #include "Pagong/Platform/Win32/WindowsWindow.h"
#endif

namespace Pagong
{
    TUnique<Window> Pagong::Window::Create(const WindowInitInfo& windowProps)
    {
#ifdef _WIN64
        return MakeUnique<Win32::WindowsWindow>(windowProps);
#endif
    }
}
