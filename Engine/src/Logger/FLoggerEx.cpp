#include "../PCH/t3dpch.h"
#include "FLoggerEx.h"

namespace t3d
{
// Constructors and Destructor:

	FLoggerEx::FLoggerEx() : LogLevel(ELogLevel::Trace)
	{
		SEvent::Trace.Subscribe(this, OnTrace);
		SEvent::Warning.Subscribe(this, OnWarning);
		SEvent::Error.Subscribe(this, OnError);
	}

	FLoggerEx::~FLoggerEx()
	{
		SEvent::Trace.Unsubscribe(OnTrace);
		SEvent::Warning.Unsubscribe(OnWarning);
		SEvent::Error.Unsubscribe(OnError);
	}


// Functions:

	bool8 FLoggerEx::OnTrace(FObject Instance, const FLogData& Data)
	{
		FLoggerEx* Logger = Instance.Get<FLoggerEx>();

		if (Logger->LogLevel == ELogLevel::Trace)
		{
			Logger->Log("[  Trace  ]", Data.FunctionName, Data.Message);
		}

		return false;
	}

	bool8 FLoggerEx::OnWarning(FObject Instance, const FLogData& Data)
	{
		FLoggerEx* Logger = Instance.Get<FLoggerEx>();

		if (Logger->LogLevel <= ELogLevel::Warning)
		{
			Logger->Log("[ Warning ]", Data.FunctionName, Data.Message);
		}

		return false;
	}

	bool8 FLoggerEx::OnError(FObject Instance, const FLogData& Data)
	{
		FLoggerEx* Logger = Instance.Get<FLoggerEx>();

		if (Logger->LogLevel <= ELogLevel::Error)
		{
			Logger->Log("[  Error  ]", Data.FunctionName, Data.Message);
		}

		return false;
	}


// Modifiers:

	void FLoggerEx::SetLevel(ELogLevel Level)
	{
		LogLevel = Level;
	}


// Private Functions:

	void FLoggerEx::Log(const char8* LogLevel, const char8* FunctionName, const char8* Message)
	{
		std::cout << "[ " << FTimeStamp::GetAsString() << " ]" << LogLevel << "::" << FunctionName << ": " << Message << std::endl;
	}


}