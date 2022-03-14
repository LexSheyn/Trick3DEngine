#include "../../PrecompiledHeaders/t3dpch.h"
#include "RMeshRenderSystem.h"

// Disable warnings from Vulkan SDK:
#pragma warning( push ) // Vulkan SDK - Begin
#pragma warning( disable : 26812 ) // Uncoped Enum

namespace t3d
{
// Constructors and Destructor:

	RMeshRenderSystem::RMeshRenderSystem(FDevice& Device, FRenderer& Renderer)
		: IRenderSystem(Device, Renderer)
	{
		this->CreateDescriptorPool();
		this->CreatePipelineLayout();
		this->CreatePipeline();

		LOG_TRACE("Created.");
	}

	RMeshRenderSystem::~RMeshRenderSystem()
	{
		LOG_TRACE("Destroyed.");
	}


// Functions:

	void RMeshRenderSystem::Render(FScene& Scene)
	{
		Pipeline->Bind(Renderer.GetCurrentCommandBuffer());

		vkCmdBindDescriptorSets(Renderer.GetCurrentCommandBuffer(), VK_PIPELINE_BIND_POINT_GRAPHICS, PipelineLayout, 0, 1, &DescriptorSets[Renderer.GetFrameIndex()], 0, nullptr);

	//	for (auto& Entry : FrameInfo.GameObjects)
	//	{
	//		OGameObject& Object = Entry.second;
	//
	//		if (Object.Mesh == nullptr)
	//		{
	//			continue;
	//		}
	//
	//		FMeshPushConstant MeshPushConstant{};
	//
	//		MeshPushConstant.MeshMatrix   = Object.GetTransform().Mat4();
	//		MeshPushConstant.NormalMatrix = Object.GetTransform().NormalMatrix();
	//
	//		vkCmdPushConstants(FrameInfo.CommandBuffer, PipelineLayout, VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT, 0, sizeof(FMeshPushConstant), &MeshPushConstant);
	//	
	//		Object.Mesh->Bind(FrameInfo.CommandBuffer);
	//		Object.Mesh->Draw(FrameInfo.CommandBuffer);
	//	}
	}


// Private Functions:

	void RMeshRenderSystem::CreateDescriptorPool()
	{
		DescriptorPool = FDescriptorPool::Constructor(Device)
			             .SetMaxSets(FSwapchain::MAX_FRAMES_IN_FLIGHT)
			             .AddPoolSize(VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, FSwapchain::MAX_FRAMES_IN_FLIGHT)
			             .Create();
	}

	void RMeshRenderSystem::CreatePipelineLayout()
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
		PushConstantRange.size       = sizeof(FMeshPushConstant);

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

	void RMeshRenderSystem::CreatePipeline()
	{
		FPipelineConfigInfo PipelineConfig{};

		FPipeline::CreateDefaultPipelineConfigInfo(PipelineConfig);
		
		PipelineConfig.RenderPass     = Renderer.GetSwapchainRenderPass();
		PipelineConfig.PipelineLayout = PipelineLayout;
		
		Pipeline = new FPipeline(Device,
			                     PipelineConfig,
			                     "D:/VULKAN_TUTORIAL_SHADERS/SPV/vert.spv",
			                     "D:/VULKAN_TUTORIAL_SHADERS/SPV/frag.spv");
	}

}

#pragma warning( pop ) // Vulkan SDK - End