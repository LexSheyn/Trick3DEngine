#pragma once

namespace t3d
{
	struct FVertex
	{
	// Accessors:

		static std::vector<VkVertexInputBindingDescription>   T3D_CALL GetBindingDescriptions();
		static std::vector<VkVertexInputAttributeDescription> T3D_CALL GetAttributeDescriptions();

	// Operators:

		bool8 operator == (const FVertex& Other) const;

	// Public Variables:

		FVec3 Position {};
		FVec3 Color    {};
		FVec3 Normal   {};
		FVec2 TexCoord {};
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