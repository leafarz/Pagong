#pragma once
#include <Windows.h>
#include "Pagong/Core/Application.h"

extern Pagong::Application* CreateApplication();

int CALLBACK WinMain(HINSTANCE, HINSTANCE, LPSTR, INT)
{
    auto application = CreateApplication();
    application->Initialize();
    application->OnInit();
    application->Run();
    application->Shutdown();
    return 0;
}
