#pragma once

#include "FPointLightPushConstant.h"

namespace t3d
{
	struct FPointLight
	{
		alignas(16) FVec4 Position{}; // Ignore W.
		alignas(16) FVec4 Color   {}; // W is intensity.
	};
}