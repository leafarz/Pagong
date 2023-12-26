#pragma once
#include "Pagong/Core/CoreDefinitions.h"
#include "Pagong/Core/Aliases.h"

#define CREATEAPP(x) Pagong::Application* CreateApplication() { return new x; }

namespace Pagong
{
	class Window;

	class PAGONG_API Application
	{
	public:
		Application();
		~Application();

		virtual void OnInit() = 0;
		virtual void OnUpdate(float dt) = 0;

#pragma region Window
		Window& GetMainWindow();
#pragma endregion Window

		void Initialize();
		void Run();
		void Shutdown();

	protected:
		virtual void Configure(ProjectSettings& projectSettings) = 0;

	private:
		TUnique<Window> m_Window;
	};

	Application* CreateApplication();
}
