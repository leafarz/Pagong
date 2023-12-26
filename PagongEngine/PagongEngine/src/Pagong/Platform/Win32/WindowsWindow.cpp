#include "pch.h"
#include "Pagong/Platform/Win32/WindowsWindow.h"

namespace Pagong::Win32
{
    LRESULT CALLBACK WindowsWindow::HandleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
    {
        /* Setup will call member WndProc function instead of static.
         * This part of the code will only be called for initialization.
         * HandleMsgThunk will be the "WndProc" function.
         * This links the windows api side to our WindowsWindow instance
         */
        if (msg == WM_NCCREATE)
        {
            const CREATESTRUCTW* const pCreate = reinterpret_cast<CREATESTRUCTW*>(lParam);
            WindowsWindow* const pWnd = static_cast<WindowsWindow*>(pCreate->lpCreateParams);
            SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWnd));
            SetWindowLongPtr(hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&WindowsWindow::HandleMsgThunk));
            return pWnd->WndProc(hWnd, msg, wParam, lParam);
        }
        return DefWindowProc(hWnd, msg, wParam, lParam);
    }

    LRESULT CALLBACK WindowsWindow::HandleMsgThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
    {
        // This will call the WndProc function of the WindowsWindow instance that is set from HandleMsgSetup
        WindowsWindow* const pWnd = reinterpret_cast<WindowsWindow*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
        return pWnd->WndProc(hWnd, msg, wParam, lParam);
    }

    LRESULT WindowsWindow::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
    {
        switch (msg)
        {
        case WM_KEYDOWN:
            // escape
            if (wParam == 27)
            {
                PostQuitMessage(0);
            }
            return 0;

        case WM_KEYUP:
            return 0;

        case WM_MOVE:
        {
            SetPos({
                (int32)(short)LOWORD(lParam),
                (int32)(short)HIWORD(lParam)
            });
            return 0;
        }

        case WM_SIZE:
        {
            SetSize({
                (uint32)(LOWORD(lParam)),
                (uint32)(HIWORD(lParam))
            });
            return 0;
        }

        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
        }

        return DefWindowProc(hWnd, msg, wParam, lParam);
    }

    WindowsWindow::WindowsWindow(const WindowInitInfo& windowInitInfo)
    {
        m_Class = InitializeWindow(windowInitInfo);

        uint8 res = RegisterClassEx(&m_Class);
        PG_ASSERT((uint32)res, GetLastErrorString().c_str());

        m_Handle = CreateWindow(windowInitInfo, m_Class);
        PG_ASSERT((uint32)m_Handle, GetLastErrorString().c_str());

        ShowWindow(m_Handle, SW_SHOW);
        UpdateWindow(m_Handle);
    }

    WindowsWindow::~WindowsWindow()
    {
        DestroyWindow(m_Handle);
    }

    bool WindowsWindow::ProcessMessage()
    {
        MSG msg = {};
        while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT)
            {
                return false;
            }

            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        return true;
    }

    void WindowsWindow::Close()
    {
        CloseWindow(m_Handle);
    }

    const Math::uivec2 WindowsWindow::GetSize() const
    {
        return m_Info.Size;
    }

    void WindowsWindow::SetSize(const Math::uivec2& size)
    {
        m_Info.Size = size;
    }

    const Math::ivec2 WindowsWindow::GetPos() const
    {
        return m_Info.Pos;
    }

    void WindowsWindow::SetPos(const Math::ivec2& pos)
    {
        m_Info.Pos = pos;
    }

    string WindowsWindow::GetLastErrorString()
    {
        DWORD errorId = GetLastError();
        if (errorId == 0)
        {
            return "Unknown error";
        }

        LPSTR buf = nullptr;

        uint32 size = FormatMessageA(
            FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
            NULL, errorId, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&buf, 0, NULL);

        string message(buf, size);
        LocalFree(buf);
        return message;
    }

    WNDCLASSEX WindowsWindow::InitializeWindow(const WindowInitInfo& windowInitInfo)
    {
        m_Info.ClassName = String::ToWString(windowInitInfo.ClassName);
        m_Info.Title = String::ToWString(windowInitInfo.Title);
        m_Info.Size = windowInitInfo.Size;

        POINT pos{ 0, 0 };
        GetCursorPos(&pos);
        HMONITOR monitor = MonitorFromPoint(pos, MONITOR_DEFAULTTOPRIMARY);
        MONITORINFO monitorInfo;
        monitorInfo.cbSize = sizeof(monitorInfo);
        GetMonitorInfoW(monitor, &monitorInfo);
        int32 x = monitorInfo.rcWork.left + windowInitInfo.Pos.x;
        int32 y = monitorInfo.rcWork.top + windowInitInfo.Pos.y;
        m_Info.Pos = { x , y };


        WNDCLASSEX window;
        window.cbSize = sizeof(window);
        window.style = CS_DBLCLKS;
        window.lpfnWndProc = HandleMsgSetup;
        window.cbClsExtra = 0;
        window.cbWndExtra = 0;
        window.hInstance = GetModuleHandle(NULL);
        window.hIcon = LoadIcon(0, IDI_APPLICATION);
        window.hCursor = LoadCursor(nullptr, IDC_ARROW);
        window.hbrBackground = (HBRUSH)GetStockObject(NULL_BRUSH);
        window.lpszClassName = m_Info.ClassName.c_str();
        window.lpszMenuName = nullptr;
        window.hIconSm = LoadIcon(0, IDI_APPLICATION);
        return window;
    }

    HWND WindowsWindow::CreateWindow(const WindowInitInfo& windowInitInfo, const WNDCLASSEX& windowClass)
    {
        HWND hWnd = CreateWindowEx(
            WS_EX_OVERLAPPEDWINDOW | WS_EX_APPWINDOW,
            m_Info.ClassName.c_str(),
            m_Info.Title.c_str(),
            WS_OVERLAPPEDWINDOW | WS_VISIBLE,
            m_Info.Pos.x, m_Info.Pos.y,
            windowInitInfo.Size.x,
            windowInitInfo.Size.y,
            nullptr,
            nullptr,
            m_Class.hInstance,
            this
        );
        return hWnd;
    }
}
