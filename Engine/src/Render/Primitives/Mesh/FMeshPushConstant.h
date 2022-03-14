#pragma once

namespace t3d
{
	struct FMeshPushConstant
	{
		// 4x4 Identity matrix by default
		alignas(16) glm::mat4 MeshMatrix{ 1.0f };

		// 4x4 Identity matrix by default
		alignas(16) glm::mat4 NormalMatrix{ 1.0f };
	};
}