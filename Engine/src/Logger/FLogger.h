#pragma once

namespace t3d
{
	class FLogger
	{
	public:

	// Levels:

		enum class Level : uint32
		{
			Trace = 0,
			Warning,
			Error
		};

	// Constructors and Destructor:

		FLogger();

		~FLogger();

	// Functions:

		/// <summary>
		/// Show trace Message in console.
		/// </summary>
		/// <param name="FunctionName"> - Name of the function that Message came from. </param>
		/// <param name="Message"> - Actual Message. </param>
		static void Trace(const std::string& FunctionName, const std::string& Message );

		/// <summary>
		/// Show warning Message in console.
		/// </summary>
		/// <param name="FunctionName"> - Name of the function that Message came from. </param>
		/// <param name="Message"> - Actual Message. </param>
		static void Warning(const std::string& FunctionName, const std::string& Message );

		/// <summary>
		/// Show error Message in console.
		/// </summary>
		/// <param name="FunctionName"> - Name of the function that Message came from. </param>
		/// <param name="Message"> - Actual Message. </param>
		static void Error(const std::string& FunctionName, const std::string& Message );

	// Modifiers:

		/// <summary>
		/// Set log messeges level.
		/// <para> TRACES - Show all messeges include trace Messages. </para>
		/// <para> WARNINGS - Show only warning and error Messages. </para>
		/// <para> ERRORS - Show error Messages only. </para>
		/// </summary>
		/// <param name="logLevel">
		/// - Log level enum.
		/// </param>
		static void SetLevel( const Level LogLevel );

	private:

	// Variables:

		static Level LogLevel;
	};

#if _MSC_VER && !__INTEL_COMPILER

	#define LOG_TRACE( Message ) FLogger::Trace( __FUNCTION__, Message )

	#define LOG_WARNING( Message ) FLogger::Warning( __FUNCTION__, Message )

	#define LOG_ERROR( Message ) FLogger::Error( __FUNCTION__, Message )

#else

	#define LOG_TRACE( Message ) FLogger::Trace( __func__, Message )

	#define LOG_WARNING( Message ) FLogger::Warning( __func__, Message )

	#define LOG_ERROR( Message ) FLogger::Error( __func__, Message )

#endif

}