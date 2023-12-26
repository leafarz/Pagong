#include "Tests/TestLogs.h"
#include "Pagong/Core/CoreMinimal.h"

using namespace Pagong;

bool TestLogs::Initialize()
{
    return true;
}

void TestLogs::Run()
{
    TestOutputs();
    TestSets();
}

void TestLogs::Shutdown()
{
}

void TestLogs::TestOutputs()
{
    PG_FATAL("Fatal");
    Log::Output(LogLevel::Fatal, "Output Fatal");
    Log::Format(LogLevel::Fatal, "Format %s", "Fatal");

    PG_ERROR("Error");
    Log::Output(LogLevel::Error, "Output Error");
    Log::Format(LogLevel::Error, "Format %s", "Error");

    PG_WARN("Warn");
    Log::Output(LogLevel::Warn, "Output Warn");
    Log::Format(LogLevel::Warn, "Format %s", "Warn");

    PG_INFO("Info");
    Log::Output(LogLevel::Info, "Output Info");
    Log::Format(LogLevel::Info, "Format %s", "Info");

    PG_DEBUG("Debug");
    Log::Output(LogLevel::Debug, "Output Debug");
    Log::Format(LogLevel::Debug, "Format %s", "Debug");

    PG_VERBOSE("Verbose");
    Log::Output(LogLevel::Verbose, "Output Verbose");
    Log::Format(LogLevel::Verbose, "Format %s", "Verbose");
}

void TestLogs::TestSets()
{
    Log::SetLogLevel(LogLevel::Fatal);
    PG_ASSERT(Log::GetCurrentLogLevel() & LogLevel::Error);

    Log::SetLogLevel(LogLevel::Error);
    PG_ASSERT(Log::GetCurrentLogLevel() & LogLevel::Error);

    Log::SetLogLevel(LogLevel::Warn);
    PG_ASSERT(Log::GetCurrentLogLevel() & LogLevel::Warn);

    Log::SetLogLevel(LogLevel::Info);
    PG_ASSERT(Log::GetCurrentLogLevel() & LogLevel::Info);

    Log::SetLogLevel(LogLevel::Debug);
    PG_ASSERT(Log::GetCurrentLogLevel() & LogLevel::Debug);
    
    Log::SetLogLevel(LogLevel::Verbose);
    PG_ASSERT(Log::GetCurrentLogLevel() & LogLevel::Verbose);
}
