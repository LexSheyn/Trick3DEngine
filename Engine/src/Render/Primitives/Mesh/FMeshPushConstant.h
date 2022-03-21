#pragma once

namespace t3d
{
	struct FMeshPushConstant
	{
	// Transform:

		alignas(16) FVec3 Translation;
		alignas(16) FVec3 Rotation;
		alignas(16) FVec3 Scale;
	};
}