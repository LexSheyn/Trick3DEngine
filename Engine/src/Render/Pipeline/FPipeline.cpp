#include "../../PrecompiledHeaders/t3dpch.h"
#include "FPipeline.h"

// Disable warnings from Vulkan SDK:
#pragma warning( push ) // Vulkan SDK - Begin
#pragma warning( disable : 26812 ) // Uncoped Enum

#include "../Objects/Mesh/FVertex.h"

namespace t3d
{
// Constructors and Destructor:

	FPipeline::FPipeline(FDevice& Device, const FPipelineConfigInfo& ConfigInfo, const std::string& VertexShaderPath, const std::string& FragmentShaderPath)
		: Device(Device)
	{
		this->CreateGraphicsPipeline(ConfigInfo, VertexShaderPath, FragmentShaderPath);

		LOG_TRACE("Created.");
	}

	FPipeline::~FPipeline()
	{
		vkDestroyShaderModule(Device.Device(), VertexShaderModule, nullptr);
		vkDestroyShaderModule(Device.Device(), FragmentShaderModule, nullptr);

		vkDestroyPipeline(Device.Device(), GraphicsPipeline, nullptr);
	}


// Functions:

	void FPipeline::Bind(VkCommandBuffer CommandBuffer)
	{
		vkCmdBindPipeline(CommandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, GraphicsPipeline);
	}

	void FPipeline::CreateDefaultPipelineConfigInfo(FPipelineConfigInfo& ConfigInfo)
	{
		ConfigInfo.ViewportInfo.sType         = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
		ConfigInfo.ViewportInfo.viewportCount = 1;
		ConfigInfo.ViewportInfo.pViewports    = nullptr;
		ConfigInfo.ViewportInfo.scissorCount  = 1;
		ConfigInfo.ViewportInfo.pScissors     = nullptr;

		ConfigInfo.InputAssemblyInfo.sType                  = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
		ConfigInfo.InputAssemblyInfo.topology               = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
		ConfigInfo.InputAssemblyInfo.primitiveRestartEnable = VK_FALSE;

		ConfigInfo.RasterizationInfo.sType                   = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
		ConfigInfo.RasterizationInfo.depthClampEnable        = VK_FALSE;
		ConfigInfo.RasterizationInfo.rasterizerDiscardEnable = VK_FALSE;
		ConfigInfo.RasterizationInfo.polygonMode             = VK_POLYGON_MODE_FILL;
		ConfigInfo.RasterizationInfo.lineWidth               = 1.0f;
		ConfigInfo.RasterizationInfo.cullMode                = VK_CULL_MODE_NONE;
		ConfigInfo.RasterizationInfo.frontFace               = VK_FRONT_FACE_CLOCKWISE;
		ConfigInfo.RasterizationInfo.depthBiasEnable         = VK_FALSE;
		ConfigInfo.RasterizationInfo.depthBiasConstantFactor = 0.0f; // Optional.
		ConfigInfo.RasterizationInfo.depthBiasClamp          = 0.0f; // Optional.
		ConfigInfo.RasterizationInfo.depthBiasSlopeFactor    = 0.0f; // Optional.

		ConfigInfo.MultisampleInfo.sType                 = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
		ConfigInfo.MultisampleInfo.sampleShadingEnable   = VK_FALSE;
		ConfigInfo.MultisampleInfo.rasterizationSamples  = VK_SAMPLE_COUNT_1_BIT;
		ConfigInfo.MultisampleInfo.minSampleShading      = 1.0f;     // Optional.
		ConfigInfo.MultisampleInfo.pSampleMask           = nullptr;  // Optional.
		ConfigInfo.MultisampleInfo.alphaToCoverageEnable = VK_FALSE; // Optional.
		ConfigInfo.MultisampleInfo.alphaToOneEnable      = VK_FALSE; // Optional.

		ConfigInfo.ColorBlendAttachment.colorWriteMask      = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
		ConfigInfo.ColorBlendAttachment.blendEnable         = VK_FALSE;
		ConfigInfo.ColorBlendAttachment.srcColorBlendFactor = VK_BLEND_FACTOR_ONE;  // Optional.
		ConfigInfo.ColorBlendAttachment.dstColorBlendFactor = VK_BLEND_FACTOR_ZERO; // Optional.
		ConfigInfo.ColorBlendAttachment.colorBlendOp        = VK_BLEND_OP_ADD;      // Optional.
		ConfigInfo.ColorBlendAttachment.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE;  // Optional.
		ConfigInfo.ColorBlendAttachment.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO; // Optional.
		ConfigInfo.ColorBlendAttachment.alphaBlendOp        = VK_BLEND_OP_ADD;      // Optional.

		ConfigInfo.ColorBlendInfo.sType             = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
		ConfigInfo.ColorBlendInfo.logicOpEnable     = VK_FALSE;
		ConfigInfo.ColorBlendInfo.logicOp           = VK_LOGIC_OP_COPY; // Optional.
		ConfigInfo.ColorBlendInfo.attachmentCount   = 1;
		ConfigInfo.ColorBlendInfo.pAttachments      = &ConfigInfo.ColorBlendAttachment;
		ConfigInfo.ColorBlendInfo.blendConstants[0] = 0.0f;  // Optional.
		ConfigInfo.ColorBlendInfo.blendConstants[1] = 0.0f;  // Optional.
		ConfigInfo.ColorBlendInfo.blendConstants[2] = 0.0f;  // Optional.
		ConfigInfo.ColorBlendInfo.blendConstants[3] = 0.0f;  // Optional.

		ConfigInfo.DepthStencilInfo.sType                 = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
		ConfigInfo.DepthStencilInfo.depthTestEnable       = VK_TRUE;
		ConfigInfo.DepthStencilInfo.depthWriteEnable      = VK_TRUE;
		ConfigInfo.DepthStencilInfo.depthCompareOp        = VK_COMPARE_OP_LESS;
		ConfigInfo.DepthStencilInfo.depthBoundsTestEnable = VK_FALSE;
		ConfigInfo.DepthStencilInfo.minDepthBounds        = 0.0f; // Optional.
		ConfigInfo.DepthStencilInfo.maxDepthBounds        = 1.0f; // Optional.
		ConfigInfo.DepthStencilInfo.stencilTestEnable     = VK_FALSE;
		ConfigInfo.DepthStencilInfo.front                 = {}; // Optional.
		ConfigInfo.DepthStencilInfo.back                  = {}; // Optional.

		ConfigInfo.DynamicStateEnables = { VK_DYNAMIC_STATE_VIEWPORT, VK_DYNAMIC_STATE_SCISSOR };
		
		ConfigInfo.DynamicStateInfo.sType             = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
		ConfigInfo.DynamicStateInfo.pDynamicStates    = ConfigInfo.DynamicStateEnables.data();
		ConfigInfo.DynamicStateInfo.dynamicStateCount = static_cast<uint32>(ConfigInfo.DynamicStateEnables.size());
		ConfigInfo.DynamicStateInfo.flags             = 0;

		ConfigInfo.BindingDescriptions   = FVertex::GetBindingDescriptions();
		ConfigInfo.AttributeDescriptions = FVertex::GetAttributeDescriptions();
	}


// Private Functions:

	std::vector<char8> FPipeline::ReadFile(const std::string& FilePath)
	{
		std::ifstream InFile;

		InFile.open(FilePath, std::ios::ate | std::ios::binary);

		if (!InFile.is_open())
		{
			LOG_ERROR("Failed to open: " + FilePath);
			throw;
		}

		size_t FileSize = static_cast<size_t>(InFile.tellg());

		std::vector<char8> Buffer(FileSize);

		InFile.seekg(0);

		InFile.read(Buffer.data(), FileSize);

		InFile.close();

		return Buffer;
	}

	void FPipeline::CreateGraphicsPipeline(const FPipelineConfigInfo& ConfigInfo, const std::string& VertexShaderPath, const std::string& FragmentShaderPath)
	{
		if (ConfigInfo.PipelineLayout == VK_NULL_HANDLE)
		{
			LOG_ERROR("Cannot create grahics pipeline: no PipelineLayout provided in ConfigInfo!");
			throw;
		}
		
		if (ConfigInfo.RenderPass == VK_NULL_HANDLE)
		{
			LOG_ERROR("Cannot create grahics pipeline: no RenderPass provided in ConfigInfo!");
			throw;
		}

		std::vector<char8> VertexShaderCode   = this->ReadFile(VertexShaderPath);

		std::vector<char8> FragmentShaderCode = this->ReadFile(FragmentShaderPath);

		this->CreateShaderModule(VertexShaderCode, &VertexShaderModule);

		this->CreateShaderModule(FragmentShaderCode, &FragmentShaderModule);

		VkPipelineShaderStageCreateInfo ShaderStages[2];

		ShaderStages[0].sType               = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
		ShaderStages[0].stage               = VK_SHADER_STAGE_VERTEX_BIT;
		ShaderStages[0].module              = VertexShaderModule;
		ShaderStages[0].pName               = "main";
		ShaderStages[0].flags               = 0;
		ShaderStages[0].pNext               = nullptr;
		ShaderStages[0].pSpecializationInfo = nullptr;

		ShaderStages[1].sType               = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
		ShaderStages[1].stage               = VK_SHADER_STAGE_FRAGMENT_BIT;
		ShaderStages[1].module              = FragmentShaderModule;
		ShaderStages[1].pName               = "main";
		ShaderStages[1].flags               = 0;
		ShaderStages[1].pNext               = nullptr;
		ShaderStages[1].pSpecializationInfo = nullptr;

		const std::vector<VkVertexInputBindingDescription>&   BindingDescriptions   = ConfigInfo.BindingDescriptions; //FVertex::GetBindingDescriptions();
		const std::vector<VkVertexInputAttributeDescription>& AttributeDescriptions = ConfigInfo.AttributeDescriptions; //FVertex::GetAttributeDescriptions();

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
		PipelineInfo.pViewportState      = &ConfigInfo.ViewportInfo;
		PipelineInfo.pInputAssemblyState = &ConfigInfo.InputAssemblyInfo;
		PipelineInfo.pRasterizationState = &ConfigInfo.RasterizationInfo;
		PipelineInfo.pMultisampleState   = &ConfigInfo.MultisampleInfo;
		PipelineInfo.pColorBlendState    = &ConfigInfo.ColorBlendInfo;
		PipelineInfo.pDepthStencilState  = &ConfigInfo.DepthStencilInfo;
		PipelineInfo.pDynamicState       = &ConfigInfo.DynamicStateInfo;
		
		PipelineInfo.layout     = ConfigInfo.PipelineLayout;
		PipelineInfo.renderPass = ConfigInfo.RenderPass;
		PipelineInfo.subpass    = ConfigInfo.Subpass;

		PipelineInfo.basePipelineIndex  = -1;
		PipelineInfo.basePipelineHandle = VK_NULL_HANDLE;

		if (vkCreateGraphicsPipelines(Device.Device(), VK_NULL_HANDLE, 1, &PipelineInfo, nullptr, &GraphicsPipeline) != VK_SUCCESS)
		{
			LOG_ERROR("Failed to create graphics pipeline!");
			throw;
		}
	}

	void FPipeline::CreateShaderModule(const std::vector<char8>& ShaderCode, VkShaderModule* ShaderModule)
	{
		VkShaderModuleCreateInfo CreateInfo{};

		CreateInfo.sType    = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
		CreateInfo.codeSize = ShaderCode.size();
		CreateInfo.pCode    = reinterpret_cast<const uint32*>(ShaderCode.data());

		if (vkCreateShaderModule(Device.Device(), &CreateInfo, nullptr, ShaderModule) != VK_SUCCESS)
		{
			LOG_ERROR("Failed to create shader module!");
			throw;
		}
	}

}

#pragma warning( pop ) // Vulkan SDK - End