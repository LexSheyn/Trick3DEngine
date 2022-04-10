#include "../PCH/t3dpch.h"
#include "FLogger.h"

namespace t3d
{
// Functions:

	void FLogger::Trace(const std::string& FunctionName, const std::string& Message)
	{
		if ( LogLevel == ELogLevel::Trace )
		{
			std::cout << "[ " << FTimeStamp::GetAsString() << " ]" << "[  Trace  ]::" << FunctionName << ": " << Message << std::endl;
		}
	}

	void FLogger::Warning(const std::string& FunctionName, const std::string& Message)
	{
		if ( LogLevel <= ELogLevel::Warning )
		{
			std::cout << "[ " << FTimeStamp::GetAsString() << " ]" << "[ Warning ]::" << FunctionName << ": " << Message << std::endl;
		}
	}

	void FLogger::Error(const std::string& FunctionName, const std::string& Message)
	{
		if ( LogLevel <= ELogLevel::Error )
		{
			std::cout << "[ " << FTimeStamp::GetAsString() << " ]" << "[  Error  ]::" << FunctionName << ": " << Message << std::endl;
		}
	}


// Modifiers:

	void FLogger::SetLevel(ELogLevel Level)
	{
		LogLevel = Level;
	}


// Static Variables:

	ELogLevel FLogger::LogLevel = ELogLevel::Trace;

}