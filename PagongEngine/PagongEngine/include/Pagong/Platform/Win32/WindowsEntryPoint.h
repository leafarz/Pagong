#pragma once
#include <Windows.h>
#include "Pagong/Core/Application.h"

extern Pagong::Application* CreateApplication();

int CALLBACK WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ INT nShowCmd)
{
    auto application = CreateApplication();
    application->Initialize();
    application->OnInit();
    application->Run();
    application->Shutdown();
    return 0;
}
