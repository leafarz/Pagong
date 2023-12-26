#include "Pagong/Core/CoreMinimal.h"
#include "Pagong/Platform/EntryPoint.h"
using namespace Pagong;
class Sandbox : public Pagong::Application
{
public:
	Sandbox()
	{
	}

	~Sandbox()
	{
	}

	void Configure(Pagong::ProjectSettings& projectSettings) override
	{
		projectSettings.SetGameTitle("Sandstorm");
		projectSettings.SetWindowSize({ 1280, 720 });
		projectSettings.SetWindowPos({ 100, 100 });
	}

	void OnInit() override
	{
	}

	void OnUpdate(float dt) override
	{
	}
};

CREATEAPP(Sandbox)
