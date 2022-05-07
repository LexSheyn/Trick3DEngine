#pragma once

#include "ELogLevel.h"
#include "../Time/FTimeStamp.h"
#include "../Events/Experimental/SEvent.h"
#include "../Threads/TWorkerThreadEx.h"

namespace t3d
{
	class FLoggerEx
	{
	public:

	// Constructors and Destructor:

		 FLoggerEx    ();
		~FLoggerEx    ();

	// Modifiers:

		void T3D_CALL SetLevel    (ELogLevel Level);

	private:

	// Private Functions:

		void Trace      (FLogData Data);
		void Warning    (FLogData Data);
		void Error      (FLogData Data);

	// Event Callbacks:

		static bool8 T3D_CALL OnTrace      (FObject Instance, const FLogData& Data);
		static bool8 T3D_CALL OnWarning    (FObject Instance, const FLogData& Data);
		static bool8 T3D_CALL OnError      (FObject Instance, const FLogData& Data);

	// Variables:

		ELogLevel LogLevel;
		TWorkerThreadEx<FLoggerEx, FLogData> LoggerThread;
	};
}