#pragma once

namespace t3d
{
	struct FQueueFamilyIndices
	{
		int32 GraphicsFamily = -1;
		int32 PresentFamily  = -1;

	// Accessors:

		bool IsComplete() { return GraphicsFamily >= 0 && PresentFamily >= 0; }
	};
}