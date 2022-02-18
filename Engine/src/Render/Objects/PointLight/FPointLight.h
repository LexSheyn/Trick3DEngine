#pragma once

#include "FPointLightPushConstant.h"

namespace t3d
{
	struct FPointLight
	{
		glm::vec4 Position{}; // Ignore W.
		glm::vec4 Color   {}; // W is intensity.
	};
}