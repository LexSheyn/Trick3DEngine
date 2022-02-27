#pragma once

namespace t3d
{
	class FVertex
	{
	public:

	// Accessors:

		static std::vector<VkVertexInputBindingDescription>   GetBindingDescriptions();

		static std::vector<VkVertexInputAttributeDescription> GetAttributeDescriptions();

	// Operators:

		bool8 operator==(const FVertex& Other) const;

	// Public Variables:

		glm::vec3 Position {};
		glm::vec3 Color    {};
		glm::vec3 Normal   {};
		glm::vec2 TexCoord {};
	};
}

#include "../../../Templates/THashFunctions.h"

namespace std
{
	template<>
	class hash<t3d::FVertex>
	{
	public:

		uint64 operator()(t3d::FVertex const& Vertex) const
		{
			uint64 Seed = 0u;

			t3d::HashCombine(Seed, Vertex.Position, Vertex.Color, Vertex.Normal, Vertex.TexCoord);

			return Seed;
		}
	};
}