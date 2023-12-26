#pragma once
#include "Test.h"

class TestLogs : public Test
{
public:
	bool Initialize() override;
	void Run() override;
	void Shutdown() override;

private:
	void TestOutputs();
	void TestSets();
};
