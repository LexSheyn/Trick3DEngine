#pragma once

namespace t3d
{
	struct FSkeletalVertex
	{
		glm::vec3 Position;

		glm::vec3 Normal;

		glm::vec2 TexCoord;

		glm::vec3 Tangent;   // ???

		glm::vec3 Bitangent; // ???

		// Bone indices which will influence this Vertex.
		uint64 BoneIDs[T3D_MAX_BONE_INFLUENCE];

		// Weights from each bone.
		float32 Weights[T3D_MAX_BONE_INFLUENCE];
	};
}