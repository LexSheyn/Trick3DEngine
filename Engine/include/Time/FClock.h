#pragma once

#include "FTime.h"

namespace t3d
{
	class FClock
	{
	public:

	// Constructor:

		FClock();

	// Functions:

		FTime Restart();

	// Accessors:

		FTime GetElapsedTime() const;

	private:

	// Variables:

		std::chrono::steady_clock::time_point StartTime;
	};
}