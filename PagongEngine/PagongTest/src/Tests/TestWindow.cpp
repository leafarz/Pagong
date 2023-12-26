#include "Tests/TestWindow.h"
#include <Windows.h>

bool TestWindow::Initialize()
{
	m_Window = Window::Create({"TestWindowClass", "Test Window", m_Size, m_Pos });
	const Math::uivec2& size = m_Window->GetSize();
	return true;
}

void TestWindow::Run()
{
	const Math::uivec2& size = m_Window->GetSize();
	PG_ASSERT(size.x == m_Size.x && size.y == m_Size.y);

	const Math::ivec2& pos = m_Window->GetPos();
	PG_ASSERT(pos.x == m_Pos.x && pos.y == m_Pos.y);
}

void TestWindow::Shutdown()
{
	Sleep(1000);
	m_Window->Close();
}
