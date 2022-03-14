#pragma once

namespace t3d
{
	struct FMeshPushConstant
	{
		alignas(16) glm::mat4 MeshMatrix   { 1.0f };
		alignas(16) glm::mat4 NormalMatrix { 1.0f };
	};
}