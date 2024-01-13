#include "pch.h"
#include "Pagong/Core/Application.h"
#include "Pagong/Core/MathTypes.h"
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

		m_GraphicsDebug = Graphics::GraphicsDebug::Create(projectSettings.GetGraphicsApi());
		m_GraphicsDebug->Initialize();

		m_Renderer = Graphics::Renderer::Create(projectSettings.GetGraphicsApi());
		m_Renderer->Initialize(m_Window->GetWidth(), m_Window->GetHeight(), m_Window->GetHandle());
	}

	void Application::Run()
	{
		while (true)
		{
			if (!m_Window->ProcessMessage())
			{
				return;
			}

			OnUpdate(0.0f);

			m_Renderer->OnRender();
			Sleep(1);
		}
	}

	void Application::Shutdown()
	{
		m_Renderer->Shutdown();
		m_GraphicsDebug->Shutdown();
	}
}
