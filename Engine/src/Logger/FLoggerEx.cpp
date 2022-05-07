#include "../PCH/t3dpch.h"
#include "FLoggerEx.h"

namespace t3d
{
// Constructors and Destructor:

	FLoggerEx::FLoggerEx()
		:
		LogLevel(ELogLevel::Trace)
	{
		LoggerThread.SetSleepDuration(200);
		LoggerThread.Launch();

		SEvent::Trace  .Subscribe(this, OnTrace);
		SEvent::Warning.Subscribe(this, OnWarning);
		SEvent::Error  .Subscribe(this, OnError);
	}

	FLoggerEx::~FLoggerEx()
	{
		LoggerThread.Stop();

		SEvent::Trace  .Unsubscribe(OnTrace);
		SEvent::Warning.Unsubscribe(OnWarning);
		SEvent::Error  .Unsubscribe(OnError);
	}


// Modifiers:

	void FLoggerEx::SetLevel(ELogLevel Level)
	{
		LogLevel = Level;
	}


// Private Functions:

	void FLoggerEx::Trace(FLogData Data)
	{
		if (LogLevel == ELogLevel::Trace)
		{
			std::cout << "[ " << Data.GetTimeStamp() << " ]" << "[  Trace  ]" << "::" << Data.GetFunctionName() << ": " << Data.GetMessage() << std::endl;
		}
	}

	void FLoggerEx::Warning(FLogData Data)
	{
		if (LogLevel <= ELogLevel::Warning)
		{
			std::cout << "[ " << Data.GetTimeStamp() << " ]" << "[ Warning ]" << "::" << Data.GetFunctionName() << ": " << Data.GetMessage() << std::endl;
		}
	}

	void FLoggerEx::Error(FLogData Data)
	{
		if (LogLevel <= ELogLevel::Error)
		{
			std::cout << "[ " << Data.GetTimeStamp() << " ]" << "[  Error  ]" << "::" << Data.GetFunctionName() << ": " << Data.GetMessage() << std::endl;
		}
	}


// Event Callbacks:

	bool8 FLoggerEx::OnTrace(FObject Instance, const FLogData& Data)
	{
		FLoggerEx* Logger = Instance.Get<FLoggerEx>();

		Logger->LoggerThread.ScheduleJob(TJobEx(Logger, &FLoggerEx::Trace, Data));

		return false;
	}

	bool8 FLoggerEx::OnWarning(FObject Instance, const FLogData& Data)
	{
		FLoggerEx* Logger = Instance.Get<FLoggerEx>();

		Logger->LoggerThread.ScheduleJob(TJobEx(Logger, &FLoggerEx::Warning, Data));

		return false;
	}

	bool8 FLoggerEx::OnError(FObject Instance, const FLogData& Data)
	{
		FLoggerEx* Logger = Instance.Get<FLoggerEx>();

		Logger->LoggerThread.ScheduleJob(TJobEx(Logger, &FLoggerEx::Error, Data));

		return false;
	}


}