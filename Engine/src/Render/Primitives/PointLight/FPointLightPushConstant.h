#pragma once

namespace t3d
{
	struct FPointLightPushConstant
	{
		alignas(16) FVec4 Position{};
		alignas(16) FVec4 Color   {};

		alignas(4) float32 Radius;
	};
}