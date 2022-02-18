#pragma once

namespace t3d
{
	struct FPointLightPushConstant
	{
		alignas(16) glm::vec4 Position{};
		alignas(16) glm::vec4 Color   {};

		alignas(4) float32 Radius;
	};
}