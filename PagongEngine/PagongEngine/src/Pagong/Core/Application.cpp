#include "pch.h"
#include "Pagong/Core/Application.h"

namespace Pagong
{
	Application::Application()
	{
	}

	Application::~Application()
	{
	}

	Window& Application::GetMainWindow()
	{
		return *m_Window;
	}

	void Application::Initialize()
	{
		ProjectSettings& projectSettings = ProjectSettings::Get();
		Configure(projectSettings);

		m_Window = Window::Create(WindowInitInfo{
			projectSettings.GetGameTitle(), projectSettings.GetGameTitle(),
			projectSettings.GetWindowSize(),
			projectSettings.GetWindowPos()
		});
	}

	void Application::Run()
	{
		//while (!quit)
		//{
		//    // Update the camera transform based on interactive
		//    // inputs or by following a predefined path.
		//    updateCamera();
		//    // Update positions, orientations and any other
		//    // relevant visual state of any dynamic elements
		//    // in the scene.
		//    updateSceneElements();
		//    // Render a still frame into an off-screen frame
		//    // buffer known as the "back buffer".
		//    renderScene();
		//    // Swap the back buffer with the front buffer, making
		//    // the most recently rendered image visible
		//    // on-screen. (Or, in windowed mode, copy (blit) the
		//    // back buffer's contents to the front buffer.
		//    swapBuffers();
		//}

		while (true)
		{
			if (!m_Window->ProcessMessage())
			{
				return;
			}

			OnUpdate(0.0f);
			Sleep(10);
		}
	}

	void Application::Shutdown()
	{
	}
}
