#pragma once

namespace t3d
{
	struct FBoneInfo
	{
		// ID is an index in ...
		uint64 ID;

		// Offset matrix transforms Vertex from Model space to Bone space.
		glm::mat4 Offset;
	};
}