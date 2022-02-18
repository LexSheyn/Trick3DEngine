#pragma once

namespace t3d
{
	struct FPointLightPushConstant
	{
		glm::vec4 Position{};
		glm::vec4 Color   {};

		float32 Radius;
	};
}