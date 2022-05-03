#pragma once

#include "ELogLevel.h"
#include "../Time/FTimeStamp.h"
#include "../Events/Experimental/SEvent.h"

namespace t3d
{
	class FLoggerEx
	{
	public:

	// Constructors and Destructor:

		 FLoggerEx    ();
		~FLoggerEx    ();

	// Functions:

		static bool8 T3D_CALL OnTrace      (FObject Instance, const FLogData& Data);
		static bool8 T3D_CALL OnWarning    (FObject Instance, const FLogData& Data);
		static bool8 T3D_CALL OnError      (FObject Instance, const FLogData& Data);

	// Modifiers:

		static void T3D_CALL SetLevel    (ELogLevel Level);

	private:

	// Variables:

		static ELogLevel LogLevel;
	};
}