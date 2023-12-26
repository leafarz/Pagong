#pragma once
#include "Test.h"
#include "Pagong/Core/CoreMinimal.h"

using namespace Pagong;

class TestWindow : public Test
{
public:
	bool Initialize() override;
	void Run() override;
	void Shutdown() override;

private:
	const Math::uivec2 m_Size = { 400, 400 };
	const Math::ivec2 m_Pos = { 150, 150 };
	TUnique<Window> m_Window;
};
