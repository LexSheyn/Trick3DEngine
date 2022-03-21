#pragma once

namespace t3d
{
	struct FMeshUniform
	{
	// Camera:

		alignas(16) FMat4 CameraProjection;
		alignas(16) FMat4 CameraView;

	// Light:

		alignas(16) FVec3 LightDirection;
	};
}