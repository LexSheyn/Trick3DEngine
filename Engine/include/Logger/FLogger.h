#pragma once

#include "ELogLevel.h"

namespace t3d
{
	class FLogger
	{
	public:

	// Levels:



	// Functions:

		static void Trace      (const std::string& FunctionName, const std::string& Message );
		static void Warning    (const std::string& FunctionName, const std::string& Message );
		static void Error      (const std::string& FunctionName, const std::string& Message );

	// Modifiers:

		static void SetLevel(ELogLevel Level);

	private:

	// Private Constructors and Destructor:

		FLogger  () {}
		~FLogger () {}

		T3D_NO_COPY(FLogger);
		T3D_NO_MOVE(FLogger);

	// Variables:

		static ELogLevel LogLevel;
	};

#if _MSC_VER && !__INTEL_COMPILER

	// Show trace Message in console.
	#define LOG_TRACE( Message ) FLogger::Trace( __FUNCTION__, Message )

	// Show warning Message in console.
	#define LOG_WARNING( Message ) FLogger::Warning( __FUNCTION__, Message )

	// Show error Message in console.
	#define LOG_ERROR( Message ) FLogger::Error( __FUNCTION__, Message )

#else

	// Show trace Message in console.
	#define LOG_TRACE( Message ) FLogger::Trace( __func__, Message )

	// Show warning Message in console.
	#define LOG_WARNING( Message ) FLogger::Warning( __func__, Message )

	// Show error Message in console.
	#define LOG_ERROR( Message ) FLogger::Error( __func__, Message )

#endif

}