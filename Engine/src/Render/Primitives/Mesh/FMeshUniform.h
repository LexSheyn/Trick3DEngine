#pragma once

namespace t3d
{
	struct FMeshUniform
	{
	// Camera:

		alignas(16) FMat4 Projection;
		alignas(16) FMat4 View;
	};
}