#include "../../PrecompiledHeaders/t3dpch.h"
#include "PGraphicsPipeline.h"

// Disable warnings from Vulkan SDK:
#pragma warning( push ) // Vulkan SDK - Begin
#pragma warning( disable : 26812 ) // Uncoped Enum

namespace t3d
{
// Constructors and Destructor:

	PGraphicsPipeline::PGraphicsPipeline(FRenderer& Renderer)
		: IPipeline(Renderer)
	{
		this->Init();

		this->Configure();
		this->CreateUniformBuffers();
		this->CreateDescriptors();
		this->CreatePipelineLayout();
		this->Create();

		LOG_TRACE("Created.");
	}

	PGraphicsPipeline::~PGraphicsPipeline()
	{
		vkDeviceWaitIdle(Renderer.GetDevice().Device());

		vkDestroyShaderModule(Renderer.GetDevice().Device(), FragmentShaderModule, VK_NULL_HANDLE);
		vkDestroyShaderModule(Renderer.GetDevice().Device(), VertexShaderModule  , VK_NULL_HANDLE);

		delete DescriptorPool;

		// When a pool is destroyed, all descriptor sets allocated from the pool are implicitly freed and become invalid.
		// Descriptor sets allocated from a given pool do not need to be freed before destroying that descriptor pool.

		delete DescriptorSetLayout;

		for (uint64 i = 0u; i < UniformBuffers.Size(); i++)
		{
			delete UniformBuffers[i];
		}

		LOG_TRACE("Deleted.");
	}


// IPipeline Public Interface:

	void PGraphicsPipeline::Bind(VkCommandBuffer CommandBuffer)
	{
		vkCmdBindPipeline(CommandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, VulkanPipeline);

		vkCmdBindDescriptorSets(Renderer.GetCurrentCommandBuffer(), VK_PIPELINE_BIND_POINT_GRAPHICS, PipelineLayout, 0, 1, &DescriptorSets[Renderer.GetFrameIndex()], 0, VK_NULL_HANDLE);
	}

	void PGraphicsPipeline::SubmitUniforms()
	{
		UniformBuffers[Renderer.GetFrameIndex()]->WriteToBuffer(&MeshUniform);
		UniformBuffers[Renderer.GetFrameIndex()]->Flush();
	}

	void PGraphicsPipeline::PushConstants()
	{
		vkCmdPushConstants(Renderer.GetCurrentCommandBuffer(), PipelineLayout, VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT, 0, sizeof(FMeshPushConstant), &MeshConstant);
	}


// IPipeline Private Interface:

	void PGraphicsPipeline::CreateShaderModule(VkShaderModule* ShaderModule, const std::vector<uint32>& ShaderCode)
	{
		VkShaderModuleCreateInfo CreateInfo{};

		CreateInfo.sType    = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
		CreateInfo.pNext    = VK_NULL_HANDLE;
		CreateInfo.flags    = {};
		CreateInfo.codeSize = ShaderCode.size() * sizeof(uint32); // Size in bytes, uint32 type size is 4 bytes.
		CreateInfo.pCode    = ShaderCode.data();

		if (vkCreateShaderModule(Renderer.GetDevice().Device(), &CreateInfo, VK_NULL_HANDLE, ShaderModule) != VK_SUCCESS)
		{
			LOG_ERROR("Failed to create shader module!");
			throw;
		}
	}

	void PGraphicsPipeline::Configure()
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

	void PGraphicsPipeline::CreateUniformBuffers()
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
	}

	void PGraphicsPipeline::CreateDescriptors()
	{
		DescriptorPool = FDescriptorPool::Constructor(Renderer.GetDevice())
			             .SetMaxSets(FSwapchain::MaxFramesInFlight)
			             .AddPoolSize(VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, FSwapchain::MaxFramesInFlight)
			             .Create();

		DescriptorSetLayout = FDescriptorSetLayout::Constructor(Renderer.GetDevice())
	                          .AddBinding(0, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, VK_SHADER_STAGE_ALL_GRAPHICS)
	                          .Create();

		for (uint64 i = 0u; i < DescriptorSets.Size(); i++)
		{
			VkDescriptorBufferInfo BufferInfo = UniformBuffers[i]->DescriptorInfo();

			FDescriptorWriter(*DescriptorSetLayout, *DescriptorPool).WriteBuffer(0, &BufferInfo).Build(DescriptorSets[i]);
		}
	}

	void PGraphicsPipeline::CreatePipelineLayout()
	{
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

		if (vkCreatePipelineLayout(Renderer.GetDevice().Device(), &PipelineLayoutInfo, VK_NULL_HANDLE, &PipelineLayout) != VK_SUCCESS)
		{
			LOG_ERROR("Failed to create pipeline layout!");
			throw;
		}
	}

	void PGraphicsPipeline::Create()
	{
		// TEST
	//	MShaderManager::SaveAsSPV(MShaderManager::LoadGLSL("Shaders/GLSL/MeshShader.vert"), "Shaders/SPIR-V/MeshShader.vert_TEST.spv", EShaderKind::Vertex);
	//	std::vector<uint32> VertexShaderCode   = MShaderManager::LoadSPV("Shaders/SPIR-V/MeshShader.vert_TEST.spv");

		std::vector<uint32> VertexShaderCode   = MShaderManager::TranslateToSPV("Shaders/GLSL/MeshShader.vert", EShaderOptimization::Performance);
		std::vector<uint32> FragmentShaderCode = MShaderManager::TranslateToSPV("Shaders/GLSL/MeshShader.frag", EShaderOptimization::Performance);

		this->CreateShaderModule(&VertexShaderModule  , VertexShaderCode);
		this->CreateShaderModule(&FragmentShaderModule, FragmentShaderCode);

		VkPipelineShaderStageCreateInfo ShaderStages[2]{};

		ShaderStages[0].sType               = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
		ShaderStages[0].stage               = VK_SHADER_STAGE_VERTEX_BIT;
		ShaderStages[0].module              = VertexShaderModule;
		ShaderStages[0].pName               = "main";
		ShaderStages[0].flags               = 0;
		ShaderStages[0].pNext               = VK_NULL_HANDLE;
		ShaderStages[0].pSpecializationInfo = VK_NULL_HANDLE;

		ShaderStages[1].sType               = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
		ShaderStages[1].stage               = VK_SHADER_STAGE_FRAGMENT_BIT;
		ShaderStages[1].module              = FragmentShaderModule;
		ShaderStages[1].pName               = "main";
		ShaderStages[1].flags               = 0;
		ShaderStages[1].pNext               = VK_NULL_HANDLE;
		ShaderStages[1].pSpecializationInfo = VK_NULL_HANDLE;

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

		if (vkCreateGraphicsPipelines(Renderer.GetDevice().Device(), VK_NULL_HANDLE, 1, &PipelineInfo, VK_NULL_HANDLE, &VulkanPipeline) != VK_SUCCESS)
		{
			LOG_ERROR("Failed to create graphics pipeline!");
			throw;
		}
	}


// Private Functions:

	void PGraphicsPipeline::Init()
	{
		for (uint64 i = 0u; i < UniformBuffers.Size(); i++)
		{
			UniformBuffers[i] = nullptr;
		}

		DescriptorSetLayout = nullptr;

		for (uint64 i = 0u; i < DescriptorSets.Size(); i++)
		{
			DescriptorSets[i] = VK_NULL_HANDLE;
		}

		DescriptorPool = nullptr;

		VertexShaderModule   = VK_NULL_HANDLE;
		FragmentShaderModule = VK_NULL_HANDLE;
	}

}

#pragma warning( pop ) // Vulkan SDK - End