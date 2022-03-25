#include "../PrecompiledHeaders/t3dpch.h"
#include "Test_Pipeline.h"

// Disable warnings from Vulkan SDK:
#pragma warning( push ) // Vulkan SDK - Begin
#pragma warning( disable : 26812 ) // Uncoped Enum

namespace t3d
{
// Constructors and Destructor:

	Test_Pipeline::Test_Pipeline(FRenderer& Renderer)
		: Renderer(Renderer)
	{
		this->Initialize();
	}

	Test_Pipeline::~Test_Pipeline()
	{
		vkDeviceWaitIdle(Renderer.GetDevice().Device());

		for (uint64 i = 0u; i < ShaderModules.Size(); i++)
		{
			vkDestroyShaderModule(Renderer.GetDevice().Device(), ShaderModules[i], nullptr);
		}

		vkDestroyPipeline(Renderer.GetDevice().Device(), VulkanPipeline, nullptr);
	}


// Functions:

	void Test_Pipeline::Create(EPipelineType Type)
	{
		if (Type == EPipelineType::Graphics)
		{
			this->ConfigureGraphicsPipeline();
			this->CreateGraphicsPipeline();
		}
		else if (Type == EPipelineType::Compute)
		{
			this->ConfigureComputePipeline();
			this->CreateComputePipeline();
		}
		else if (Type == EPipelineType::RayTracing)
		{
			this->ConfigureRayTracingPipeline();
			this->CreateRayTracingPipeline();
		}
		else if (Type == EPipelineType::SubpassShading)
		{
			this->ConfigureSubpassShadingPipeline();
			this->CreateSubpassShadingPipeline();
		}
	}

	void Test_Pipeline::Bind(VkCommandBuffer CommandBuffer)
	{
		vkCmdBindPipeline(CommandBuffer, Config.BindPoint, VulkanPipeline);
	}


// Private Functions:

	void Test_Pipeline::Initialize()
	{
		for (uint64 i = 0u; i < ShaderModules.Size(); i++)
		{
			ShaderModules[i] = nullptr;
		}
	}


// Private Configuration Functions:

	void Test_Pipeline::ConfigureGraphicsPipeline()
	{
		Config.ViewportInfo.sType         = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
		Config.ViewportInfo.viewportCount = static_cast<uint32>(Renderer.GetViewports().size());
		Config.ViewportInfo.pViewports    = Renderer.GetViewports().data();
		Config.ViewportInfo.scissorCount  = static_cast<uint32>(Renderer.GetScissors().size());
		Config.ViewportInfo.pScissors     = Renderer.GetScissors().data();

		Config.InputAssemblyInfo.sType                  = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
		Config.InputAssemblyInfo.topology               = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
		Config.InputAssemblyInfo.primitiveRestartEnable = VK_FALSE;

		Config.RasterizationInfo.sType                   = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
		Config.RasterizationInfo.depthClampEnable        = VK_FALSE;
		Config.RasterizationInfo.rasterizerDiscardEnable = VK_FALSE;
		Config.RasterizationInfo.polygonMode             = VK_POLYGON_MODE_FILL;
		Config.RasterizationInfo.lineWidth               = 1.0f;
		Config.RasterizationInfo.cullMode                = VK_CULL_MODE_NONE;
		Config.RasterizationInfo.frontFace               = VK_FRONT_FACE_CLOCKWISE;
		Config.RasterizationInfo.depthBiasEnable         = VK_FALSE;
		Config.RasterizationInfo.depthBiasConstantFactor = 0.0f; // Optional.
		Config.RasterizationInfo.depthBiasClamp          = 0.0f; // Optional.
		Config.RasterizationInfo.depthBiasSlopeFactor    = 0.0f; // Optional.

		Config.MultisampleInfo.sType                 = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
		Config.MultisampleInfo.sampleShadingEnable   = VK_FALSE;
		Config.MultisampleInfo.rasterizationSamples  = VK_SAMPLE_COUNT_1_BIT;
		Config.MultisampleInfo.minSampleShading      = 1.0f;     // Optional.
		Config.MultisampleInfo.pSampleMask           = nullptr;  // Optional.
		Config.MultisampleInfo.alphaToCoverageEnable = VK_FALSE; // Optional.
		Config.MultisampleInfo.alphaToOneEnable      = VK_FALSE; // Optional.

		Config.ColorBlendAttachment.colorWriteMask      = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
		Config.ColorBlendAttachment.blendEnable         = VK_FALSE;
		Config.ColorBlendAttachment.srcColorBlendFactor = VK_BLEND_FACTOR_ONE;  // Optional.
		Config.ColorBlendAttachment.dstColorBlendFactor = VK_BLEND_FACTOR_ZERO; // Optional.
		Config.ColorBlendAttachment.colorBlendOp        = VK_BLEND_OP_ADD;      // Optional.
		Config.ColorBlendAttachment.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE;  // Optional.
		Config.ColorBlendAttachment.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO; // Optional.
		Config.ColorBlendAttachment.alphaBlendOp        = VK_BLEND_OP_ADD;      // Optional.

		Config.ColorBlendInfo.sType             = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
		Config.ColorBlendInfo.logicOpEnable     = VK_FALSE;
		Config.ColorBlendInfo.logicOp           = VK_LOGIC_OP_COPY; // Optional.
		Config.ColorBlendInfo.attachmentCount   = 1;
		Config.ColorBlendInfo.pAttachments      = &Config.ColorBlendAttachment;
		Config.ColorBlendInfo.blendConstants[0] = 0.0f;  // Optional.
		Config.ColorBlendInfo.blendConstants[1] = 0.0f;  // Optional.
		Config.ColorBlendInfo.blendConstants[2] = 0.0f;  // Optional.
		Config.ColorBlendInfo.blendConstants[3] = 0.0f;  // Optional.

		Config.DepthStencilInfo.sType                 = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
		Config.DepthStencilInfo.depthTestEnable       = VK_TRUE;
		Config.DepthStencilInfo.depthWriteEnable      = VK_TRUE;
		Config.DepthStencilInfo.depthCompareOp        = VK_COMPARE_OP_LESS;
		Config.DepthStencilInfo.depthBoundsTestEnable = VK_FALSE;
		Config.DepthStencilInfo.minDepthBounds        = 0.0f; // Optional.
		Config.DepthStencilInfo.maxDepthBounds        = 1.0f; // Optional.
		Config.DepthStencilInfo.stencilTestEnable     = VK_FALSE;
		Config.DepthStencilInfo.front                 = {}; // Optional.
		Config.DepthStencilInfo.back                  = {}; // Optional.

		Config.DynamicStateEnables = { VK_DYNAMIC_STATE_VIEWPORT, VK_DYNAMIC_STATE_SCISSOR };
		
		Config.DynamicStateInfo.sType             = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
		Config.DynamicStateInfo.pDynamicStates    = Config.DynamicStateEnables.data();
		Config.DynamicStateInfo.dynamicStateCount = static_cast<uint32>(Config.DynamicStateEnables.size());
		Config.DynamicStateInfo.flags             = 0;

		Config.BindingDescriptions   = FVertex::GetBindingDescriptions();
		Config.AttributeDescriptions = FVertex::GetAttributeDescriptions();
	}

	void Test_Pipeline::ConfigureComputePipeline()
	{
	}

	void Test_Pipeline::ConfigureRayTracingPipeline()
	{
	}

	void Test_Pipeline::ConfigureSubpassShadingPipeline()
	{
	}


// Private Creation Functions:

	void Test_Pipeline::CreateGraphicsPipeline()
	{
		for (uint64 i = 0u; i < UniformBuffers.Size(); i++)
		{
			UniformBuffers[i] = new FDeviceBuffer(Renderer.GetDevice(),
				                                  sizeof(FMeshUniform),
				                                  1,
				                                  VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT,
				                                  VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT,
				                                  Renderer.GetDevice().Properties.limits.minUniformBufferOffsetAlignment);

			UniformBuffers[i]->Map();
		}

		DescriptorSetLayout = FDescriptorSetLayout::Constructor(Renderer.GetDevice())
	                          .AddBinding(0, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, VK_SHADER_STAGE_ALL_GRAPHICS)
	                          .Create();

		for (uint64 i = 0u; i < DescriptorSets.Size(); i++)
		{
			VkDescriptorBufferInfo BufferInfo = UniformBuffers[i]->DescriptorInfo();

			FDescriptorWriter(*DescriptorSetLayout, *DescriptorPool).WriteBuffer(0, &BufferInfo).Build(DescriptorSets[i]);
		}

		VkPushConstantRange PushConstantRange{};

		PushConstantRange.stageFlags = VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT;
		PushConstantRange.offset     = 0;
		PushConstantRange.size       = sizeof(FMeshPushConstant);

		std::vector<VkDescriptorSetLayout> DescriptorSetLayouts{ DescriptorSetLayout->GetDescriptorSetLayout() };

		VkPipelineLayoutCreateInfo PipelineLayoutInfo{};

		PipelineLayoutInfo.sType                  = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
		PipelineLayoutInfo.setLayoutCount         = static_cast<uint32>(DescriptorSetLayouts.size());
		PipelineLayoutInfo.pSetLayouts            = DescriptorSetLayouts.data();
		PipelineLayoutInfo.pushConstantRangeCount = 1;
		PipelineLayoutInfo.pPushConstantRanges    = &PushConstantRange;

		if (vkCreatePipelineLayout(Renderer.GetDevice().Device(), &PipelineLayoutInfo, nullptr, &PipelineLayout) != VK_SUCCESS)
		{
			LOG_ERROR("Failed to create pipeline layout!");
			throw;
		}

		std::vector<char8> VertexShaderCode   = MShaderManager::ReadAsBinary(T3D_SHADER_DIR + "MeshShader_vert.spv");
		std::vector<char8> FragmentShaderCode = MShaderManager::ReadAsBinary(T3D_SHADER_DIR + "MeshShader_frag.spv");

		this->CreateShaderModule(VertexShaderCode  , &ShaderModules[EShaderType::Vertex]);
		this->CreateShaderModule(FragmentShaderCode, &ShaderModules[EShaderType::Fragment]);

		VkPipelineShaderStageCreateInfo ShaderStages[2]{};

		ShaderStages[0].sType               = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
		ShaderStages[0].stage               = VK_SHADER_STAGE_VERTEX_BIT;
		ShaderStages[0].module              = ShaderModules[EShaderType::Vertex];
		ShaderStages[0].pName               = "main";
		ShaderStages[0].flags               = 0;
		ShaderStages[0].pNext               = nullptr;
		ShaderStages[0].pSpecializationInfo = nullptr;

		ShaderStages[1].sType               = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
		ShaderStages[1].stage               = VK_SHADER_STAGE_FRAGMENT_BIT;
		ShaderStages[1].module              = ShaderModules[EShaderType::Fragment];
		ShaderStages[1].pName               = "main";
		ShaderStages[1].flags               = 0;
		ShaderStages[1].pNext               = nullptr;
		ShaderStages[1].pSpecializationInfo = nullptr;

		const std::vector<VkVertexInputBindingDescription>&   BindingDescriptions   = Config.BindingDescriptions; //FVertex::GetBindingDescriptions();
		const std::vector<VkVertexInputAttributeDescription>& AttributeDescriptions = Config.AttributeDescriptions; //FVertex::GetAttributeDescriptions();

		VkPipelineVertexInputStateCreateInfo VertexInputInfo{};

		VertexInputInfo.sType                           = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
		VertexInputInfo.vertexBindingDescriptionCount   = static_cast<uint32>(BindingDescriptions.size());
		VertexInputInfo.pVertexBindingDescriptions      = BindingDescriptions.data();
		VertexInputInfo.vertexAttributeDescriptionCount = static_cast<uint32>(AttributeDescriptions.size());
		VertexInputInfo.pVertexAttributeDescriptions    = AttributeDescriptions.data();

		VkGraphicsPipelineCreateInfo PipelineInfo{};

		PipelineInfo.sType               = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
		PipelineInfo.stageCount          = 2;
		PipelineInfo.pStages             = ShaderStages;
		PipelineInfo.pVertexInputState   = &VertexInputInfo;
		PipelineInfo.pViewportState      = &Config.ViewportInfo;
		PipelineInfo.pInputAssemblyState = &Config.InputAssemblyInfo;
		PipelineInfo.pRasterizationState = &Config.RasterizationInfo;
		PipelineInfo.pMultisampleState   = &Config.MultisampleInfo;
		PipelineInfo.pColorBlendState    = &Config.ColorBlendInfo;
		PipelineInfo.pDepthStencilState  = &Config.DepthStencilInfo;
		PipelineInfo.pDynamicState       = &Config.DynamicStateInfo;
		
		PipelineInfo.layout     = PipelineLayout;
		PipelineInfo.renderPass = Renderer.GetSwapchainRenderPass();
		PipelineInfo.subpass    = Config.Subpass; // No Subpass yet.

		PipelineInfo.basePipelineIndex  = -1;
		PipelineInfo.basePipelineHandle = VK_NULL_HANDLE;

		if (vkCreateGraphicsPipelines(Renderer.GetDevice().Device(), VK_NULL_HANDLE, 1, &PipelineInfo, nullptr, &VulkanPipeline) != VK_SUCCESS)
		{
			LOG_ERROR("Failed to create graphics pipeline!");
			throw;
		}
	}

	void Test_Pipeline::CreateComputePipeline()
	{
	}

	void Test_Pipeline::CreateRayTracingPipeline()
	{
	}

	void Test_Pipeline::CreateSubpassShadingPipeline()
	{
	}

	void Test_Pipeline::CreateShaderModule(const std::vector<char8>& ShaderCode, VkShaderModule* ShaderModule)
	{
		VkShaderModuleCreateInfo CreateInfo{};

		CreateInfo.sType    = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
		CreateInfo.pNext    = nullptr;
		CreateInfo.flags    = 0u;
		CreateInfo.codeSize = ShaderCode.size();
		CreateInfo.pCode    = reinterpret_cast<const uint32*>(ShaderCode.data());

		if (vkCreateShaderModule(Renderer.GetDevice().Device(), &CreateInfo, nullptr, ShaderModule) != VK_SUCCESS)
		{
			LOG_ERROR("Failed to create shader module!");
			throw;
		}
	}

}

#pragma warning( pop ) // Vulkan SDK - End