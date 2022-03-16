#include "../../PrecompiledHeaders/t3dpch.h"
#include "FPointLightRenderSystem.h"

// Disable warnings from Vulkan SDK:
#pragma warning( push ) // Vulkan SDK - Begin
#pragma warning( disable : 26812 ) // Uncoped Enum

namespace t3d
{
// Constructors and Destructor:

	FPointLightRenderSystem::FPointLightRenderSystem(FDevice& Device, FRenderer& Renderer)
		: IRenderSystem(Device, Renderer)
	{
		this->CreateDescriptorPool();
		this->CreatePipelineLayout();
		this->CreatePipeline();

		LOG_TRACE("Created.");
	}

	FPointLightRenderSystem::~FPointLightRenderSystem()
	{
		delete Pipeline;

		vkDestroyPipelineLayout(Device.Device(), PipelineLayout, nullptr);
	}


// Functions:

	void FPointLightRenderSystem::Update()
	{
		
	}

	void FPointLightRenderSystem::Render(FScene& Scene)
	{
		Pipeline->Bind(Renderer.GetCurrentCommandBuffer());

		vkCmdBindDescriptorSets(Renderer.GetCurrentCommandBuffer(), VK_PIPELINE_BIND_POINT_GRAPHICS, PipelineLayout, 0, 1, &DescriptorSets[Renderer.GetFrameIndex()], 0, nullptr);

	//	for (auto& Entry : FrameInfo.GameObjects)
	//	{
	//		OGameObject& Object = Entry.second;
	//
	//		if (Object.Light == 0)
	//		{
	//			continue;
	//		}
	//
	//		FPointLightPushConstant PushConstant{};
	//
	//		PushConstant.Position = FVec4(Object.GetTransform().GetTranslation(), 1.0f);
	//		PushConstant.Color    = FVec4(Object.Color, Object.LightIntensity);
	//		PushConstant.Radius   = Object.GetTransform().GetScale().x;
	//
	//		vkCmdPushConstants(FrameInfo.CommandBuffer, PipelineLayout, VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT, 0, sizeof(FPointLightPushConstant), &PushConstant);
	//
	//		vkCmdDraw(FrameInfo.CommandBuffer, 6, 1, 0, 0);
	//	}		
	}


// Private Functions:

	void FPointLightRenderSystem::CreateDescriptorPool()
	{
		DescriptorPool = FDescriptorPool::Constructor(Device)
			             .SetMaxSets(FSwapchain::MAX_FRAMES_IN_FLIGHT)
			             .AddPoolSize(VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, FSwapchain::MAX_FRAMES_IN_FLIGHT)
			             .Create();
	}

	void FPointLightRenderSystem::CreatePipelineLayout()
	{
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//// Creating DescriptorSetLayout
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////

		for (uint64 i = 0u; i < UniformBuffers.Size(); i++)
		{
			UniformBuffers[i] = new FDeviceBuffer(Device,
				                                  sizeof(FMeshUniform),
				                                  1,
				                                  VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT,
				                                  VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT);

			UniformBuffers[i]->Map();
		}

		DescriptorSetLayout = FDescriptorSetLayout::Constructor(Device)
	                          .AddBinding(0, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, VK_SHADER_STAGE_ALL_GRAPHICS)
	                          .Create();

		for (uint64 i = 0u; i < DescriptorSets.Size(); i++)
		{
			VkDescriptorBufferInfo BufferInfo = UniformBuffers[i]->DescriptorInfo();

			FDescriptorWriter(*DescriptorSetLayout, *DescriptorPool).WriteBuffer(0, &BufferInfo).Build(DescriptorSets[i]);
		}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////

		VkPushConstantRange PushConstantRange{};
	
		PushConstantRange.stageFlags = VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT;
		PushConstantRange.offset     = 0;
		PushConstantRange.size       = sizeof(FPointLightPushConstant);

		std::vector<VkDescriptorSetLayout> DescriptorSetLayouts{ DescriptorSetLayout->GetDescriptorSetLayout() };

		VkPipelineLayoutCreateInfo PipelineLayoutInfo{};

		PipelineLayoutInfo.sType                  = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
		PipelineLayoutInfo.setLayoutCount         = static_cast<uint32>(DescriptorSetLayouts.size());
		PipelineLayoutInfo.pSetLayouts            = DescriptorSetLayouts.data();
		PipelineLayoutInfo.pushConstantRangeCount = 1;
		PipelineLayoutInfo.pPushConstantRanges    = &PushConstantRange;

		if (vkCreatePipelineLayout(Device.Device(), &PipelineLayoutInfo, nullptr, &PipelineLayout) != VK_SUCCESS)
		{
			LOG_ERROR("Failed to create pipeline layout!");
			throw;
		}
	}

	void FPointLightRenderSystem::CreatePipeline()
	{
		FPipelineConfigInfo PipelineConfig{};

		FPipeline::CreateDefaultPipelineConfigInfo(PipelineConfig);
		
		PipelineConfig.BindingDescriptions.clear();
		PipelineConfig.AttributeDescriptions.clear();
		PipelineConfig.RenderPass     = Renderer.GetSwapchainRenderPass();
		PipelineConfig.PipelineLayout = PipelineLayout;
		
		Pipeline = new FPipeline(Device,
			                     PipelineConfig,
			                     "D:/VULKAN_TUTORIAL_SHADERS/SPV/point_light.vert.spv",
			                     "D:/VULKAN_TUTORIAL_SHADERS/SPV/point_light.frag.spv");
	}

}

#pragma warning( pop ) // Vulkan SDK - End