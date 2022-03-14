#pragma once

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

	//	VkViewport Viewport;
	//	VkRect2D   Scissor;

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