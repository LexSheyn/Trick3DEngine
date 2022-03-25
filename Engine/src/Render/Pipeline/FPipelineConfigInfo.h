#pragma once

// Disable warnings from Vulkan SDK:
#pragma warning( push ) // Vulkan SDK - Begin
#pragma warning( disable : 26812 ) // Uncoped Enum

namespace t3d
{
	class FPipelineConfigInfo
	{
	public:

	// Constructors:

		FPipelineConfigInfo() {};

		T3D_NO_COPY(FPipelineConfigInfo);
		T3D_NO_MOVE(FPipelineConfigInfo);

	// Variables:

		VkPipelineBindPoint BindPoint;

		std::vector<VkVertexInputBindingDescription>   BindingDescriptions;
		std::vector<VkVertexInputAttributeDescription> AttributeDescriptions;

		VkPipelineViewportStateCreateInfo      ViewportInfo{};
		VkPipelineInputAssemblyStateCreateInfo InputAssemblyInfo{};
		VkPipelineRasterizationStateCreateInfo RasterizationInfo{};
		VkPipelineMultisampleStateCreateInfo   MultisampleInfo{};
		VkPipelineColorBlendAttachmentState    ColorBlendAttachment{};
		VkPipelineColorBlendStateCreateInfo    ColorBlendInfo{};
		VkPipelineDepthStencilStateCreateInfo  DepthStencilInfo{};

		std::vector<VkDynamicState>      DynamicStateEnables{};
		VkPipelineDynamicStateCreateInfo DynamicStateInfo{};

		VkPipelineLayout PipelineLayout{};

		VkRenderPass RenderPass{};
		uint32       Subpass{};
	};
}

#pragma warning( pop ) // Vulkan SDK - End