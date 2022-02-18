#pragma once

namespace t3d
{
	struct FQueueFamilyIndices
	{
		int32 GraphicsFamily = -1;
		int32 PresentFamily  = -1;

	// Accessors:

		T3D_INLINE bool IsComplete() { return GraphicsFamily >= 0 && PresentFamily >= 0; }
	};
}