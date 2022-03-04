#include "../PrecompiledHeaders/t3dpch.h"
#include "FLogger.h"

namespace t3d
{
// Constructors and Destructor:

	FLogger::FLogger()
	{
	}

	FLogger::~FLogger()
	{
	}


// Functions:

	void FLogger::Trace(const std::string& FunctionName, const std::string& Message)
	{
		if ( LogLevel == Level::Trace )
		{
			std::cout << "[ " << FTimeStamp::GetAsString() << " ]" << "[  Trace  ]::" << FunctionName << ": " << Message << std::endl;
		}
	}

	void FLogger::Warning(const std::string& FunctionName, const std::string& Message)
	{
		if ( LogLevel <= Level::Warning )
		{
			std::cout << "[ " << FTimeStamp::GetAsString() << " ]" << "[ Warning ]::" << FunctionName << ": " << Message << std::endl;
		}
	}

	void FLogger::Error(const std::string& FunctionName, const std::string& Message)
	{
		if ( LogLevel <= Level::Error )
		{
			std::cout << "[ " << FTimeStamp::GetAsString() << " ]" << "[  Error  ]::" << FunctionName << ": " << Message << std::endl;
		}
	}


// Modifiers:

	void FLogger::SetLevel(const Level LogLevel)
	{
		FLogger::LogLevel = LogLevel;
	}


// Static Variables:

	FLogger::Level FLogger::LogLevel = Level::Trace;

}