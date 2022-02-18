#pragma once

namespace t3d
{	
	// Scalar float32 : N = 4 bytes.
	// Therefore vec2 : 2N = 8 bytes.
	// And vec3 : 4N = 16 bytes.
	struct FPushConstantData
	{
		// 4x4 Identity matrix by default
		alignas(16) glm::mat4 MeshMatrix   { 1.0f };

		// 4x4 Identity matrix by default
		alignas(16) glm::mat4 NormalMatrix { 1.0f };
	};
}