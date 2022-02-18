#include "../../../PrecompiledHeaders/t3dpch.h"
#include "FVertex.h"

namespace t3d
{
// Accessors:

	std::vector<VkVertexInputBindingDescription> FVertex::GetBindingDescriptions()
	{
		std::vector<VkVertexInputBindingDescription> BindingDescriptions(1);

		BindingDescriptions[0].binding   = 0;
		BindingDescriptions[0].stride    = sizeof(FVertex);
		BindingDescriptions[0].inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

		return BindingDescriptions;
	}

	std::vector<VkVertexInputAttributeDescription> FVertex::GetAttributeDescriptions()
	{
		std::vector<VkVertexInputAttributeDescription> AttributeDescriptions(4);
				
		AttributeDescriptions[0].location = 0;
		AttributeDescriptions[0].binding  = 0;
		AttributeDescriptions[0].format   = VK_FORMAT_R32G32B32_SFLOAT;
		AttributeDescriptions[0].offset   = offsetof(FVertex, Position);
				
		AttributeDescriptions[1].location = 1;
		AttributeDescriptions[1].binding  = 0;
		AttributeDescriptions[1].format   = VK_FORMAT_R32G32B32_SFLOAT;
		AttributeDescriptions[1].offset   = offsetof(FVertex, Color);

		AttributeDescriptions[2].location = 2;
		AttributeDescriptions[2].binding  = 0;		
		AttributeDescriptions[2].format   = VK_FORMAT_R32G32B32_SFLOAT;
		AttributeDescriptions[2].offset   = offsetof(FVertex, Normal);

		AttributeDescriptions[3].location = 3;
		AttributeDescriptions[3].binding  = 0;		
		AttributeDescriptions[3].format   = VK_FORMAT_R32G32_SFLOAT;
		AttributeDescriptions[3].offset   = offsetof(FVertex, TexCoord);

		return AttributeDescriptions;
	}


// Operators:

	bool8 FVertex::operator==(const FVertex& Other) const
	{
		return Position == Other.Position
			&& Color    == Other.Color
			&& Normal   == Other.Normal
			&& TexCoord == Other.TexCoord;
	}

}