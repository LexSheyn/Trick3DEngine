#pragma once

namespace t3d
{
	struct FMeshPushConstant
	{
		alignas(16) FMat4 MeshMatrix   { 1.0f };
		alignas(16) FMat4 NormalMatrix { 1.0f };
	};
}