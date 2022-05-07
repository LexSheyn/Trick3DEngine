#include "../PCH/t3dpch.h"
#include "FLogger.h"

namespace t3d
{
// Constructors and Destructor:

	FLogger::FLogger()
		:
		LogLevel(ELogLevel::Trace)
	{
		LoggerThread.SetSleepDuration(200);
		LoggerThread.Launch();

		SEvent::Trace  .Subscribe(this, OnTrace);
		SEvent::Warning.Subscribe(this, OnWarning);
		SEvent::Error  .Subscribe(this, OnError);
	}

	FLogger::~FLogger()
	{
		LoggerThread.Stop();

		SEvent::Trace  .Unsubscribe(OnTrace);
		SEvent::Warning.Unsubscribe(OnWarning);
		SEvent::Error  .Unsubscribe(OnError);
	}


// Modifiers:

	void FLogger::SetLevel(ELogLevel Level)
	{
		LogLevel = Level;
	}


// Private Functions:

	void FLogger::Trace(FLogData Data)
	{
		if (LogLevel == ELogLevel::Trace)
		{
			std::cout << "[ " << Data.GetTimeStamp() << " ]" << "[  Trace  ]" << "::" << Data.GetFunctionName() << ": " << Data.GetMessage() << std::endl;
		}
	}

	void FLogger::Warning(FLogData Data)
	{
		if (LogLevel <= ELogLevel::Warning)
		{
			std::cout << "[ " << Data.GetTimeStamp() << " ]" << "[ Warning ]" << "::" << Data.GetFunctionName() << ": " << Data.GetMessage() << std::endl;
		}
	}

	void FLogger::Error(FLogData Data)
	{
		if (LogLevel <= ELogLevel::Error)
		{
			std::cout << "[ " << Data.GetTimeStamp() << " ]" << "[  Error  ]" << "::" << Data.GetFunctionName() << ": " << Data.GetMessage() << std::endl;
		}
	}


// Event Callbacks:

	bool8 FLogger::OnTrace(FObject Instance, const FLogData& Data)
	{
		FLogger* Logger = Instance.Get<FLogger>();

		Logger->LoggerThread.ScheduleJob(TJob(Logger, &FLogger::Trace, Data));

		return false;
	}

	bool8 FLogger::OnWarning(FObject Instance, const FLogData& Data)
	{
		FLogger* Logger = Instance.Get<FLogger>();

		Logger->LoggerThread.ScheduleJob(TJob(Logger, &FLogger::Warning, Data));

		return false;
	}

	bool8 FLogger::OnError(FObject Instance, const FLogData& Data)
	{
		FLogger* Logger = Instance.Get<FLogger>();

		Logger->LoggerThread.ScheduleJob(TJob(Logger, &FLogger::Error, Data));

		return false;
	}


}