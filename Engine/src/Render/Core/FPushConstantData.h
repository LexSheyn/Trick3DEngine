#pragma once

namespace t3d
{	
	// float32 : N = 4 bytes.
	// vec2    : 2N = 8 bytes.
	// vec3    : 4N = 16 bytes.
	struct FPushConstantData
	{
		// 4x4 Identity matrix by default
		alignas(16) FMat4 MeshMatrix   { 1.0f };

		// 4x4 Identity matrix by default
		alignas(16) FMat4 NormalMatrix { 1.0f };
	};
}