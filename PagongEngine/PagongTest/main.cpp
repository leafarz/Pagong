#include "Pagong/Core/CoreMinimal.h"
#include <Windows.h>
#include "Test.h"

#define TEST_LOGS 1
#define TEST_WINDOW 1

#if TEST_LOGS
#include "Tests/TestLogs.h"
#endif

#if TEST_WINDOW
#include "Tests/TestWindow.h"
#endif

using namespace Pagong;
void InitList(TArray<TUnique<Test>>& list);

int CALLBACK WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ INT nShowCmd)
{
	TArray<TUnique<Test>> tests;

	InitList(tests);

	for (const auto& test : tests)
	{
		if (test->Initialize())
		{
			test->Run();
		}
		test->Shutdown();
	}
	return 0;
}

void InitList(TArray<TUnique<Test>>& list)
{
#if TEST_LOGS
	list.push_back(MakeUnique<TestLogs>());
#endif

#if TEST_WINDOW
	list.push_back(MakeUnique<TestWindow>());
#endif
}
