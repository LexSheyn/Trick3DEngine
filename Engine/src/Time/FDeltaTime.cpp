#include "../PCH/t3dpch.h"
#include "FDeltaTime.h"

namespace t3d
{
// Accessors:

	const float32& FDeltaTime::Get()
	{
		return Time;
	}


// Modifiers:

	void FDeltaTime::Set(float32 Seconds)
	{
		Time = Seconds;
	}


// Static Variables:

	float32 FDeltaTime::Time = 0.0f;

}