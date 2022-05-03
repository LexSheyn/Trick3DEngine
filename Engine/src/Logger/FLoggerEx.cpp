#include "../PCH/t3dpch.h"
#include "FLoggerEx.h"

namespace t3d
{
// Constructors and Destructor:

	FLoggerEx::FLoggerEx()
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
		if (LogLevel == ELogLevel::Trace)
		{
			std::cout << "[ " << FTimeStamp::GetAsString() << " ]" << "[  Trace  ]::" << Data.FunctionName << ": " << Data.Message << std::endl;
		}

		return false;
	}

	bool8 FLoggerEx::OnWarning(FObject Instance, const FLogData& Data)
	{
		if (LogLevel <= ELogLevel::Warning)
		{
			std::cout << "[ " << FTimeStamp::GetAsString() << " ]" << "[ Warning ]::" << Data.FunctionName << ": " << Data.Message << std::endl;
		}

		return false;
	}

	bool8 FLoggerEx::OnError(FObject Instance, const FLogData& Data)
	{
		if (LogLevel <= ELogLevel::Error)
		{
			std::cout << "[ " << FTimeStamp::GetAsString() << " ]" << "[  Error  ]::" << Data.FunctionName << ": " << Data.Message << std::endl;
		}

		return false;
	}


// Modifiers:

	void FLoggerEx::SetLevel(ELogLevel Level)
	{
		LogLevel = Level;
	}


// Static Variables:

	ELogLevel FLoggerEx::LogLevel = ELogLevel::Trace;


}