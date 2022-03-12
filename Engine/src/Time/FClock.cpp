#include "../PrecompiledHeaders/t3dpch.h"
#include "FClock.h"

namespace t3d
{
// Constructor:

	FClock::FClock()
		: StartTime(std::chrono::steady_clock::now())
	{		
	}


// Functions:

	FTime FClock::Restart()
	{
		const std::chrono::steady_clock::time_point Now = std::chrono::steady_clock::now();

		FTime ElapsedTime = FTime::Microseconds(std::chrono::duration_cast<std::chrono::microseconds>(Now - StartTime).count());

		StartTime = Now;

		return ElapsedTime;
	}


// Accessors:

	FTime FClock::GetElapsedTime() const
	{
		return FTime::Microseconds(std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - StartTime).count());
	}

}