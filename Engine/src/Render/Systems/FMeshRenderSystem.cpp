#include "../../PrecompiledHeaders/t3dpch.h"
#include "FMeshRenderSystem.h"

// Disable warnings from Vulkan SDK:
#pragma warning( push ) // Vulkan SDK - Begin
#pragma warning( disable : 26812 ) // Uncoped Enum

namespace t3d
{
// Constructors and Destructor:

	FMeshRenderSystem::FMeshRenderSystem(FDevice& Device, VkRenderPass RenderPass, VkDescriptorSetLayout GlobalDescriptorSetLayout)
		: Device(Device)
	{
		this->CreatePipelineLayout(GlobalDescriptorSetLayout);

		this->CreatePipeline(RenderPass);

		LOG_TRACE("Created.");
	}

	FMeshRenderSystem::~FMeshRenderSystem()
	{
		vkDestroyPipelineLayout(Device.Device(), PipelineLayout, nullptr);
	}


// Functions:

	void FMeshRenderSystem::Render(FFrameInfo& FrameInfo)
	{
		Pipeline->Bind(FrameInfo.CommandBuffer);

		vkCmdBindDescriptorSets(FrameInfo.CommandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, PipelineLayout, 0, 1, &FrameInfo.GlobalDescriptorSet, 0, nullptr);

		for (auto& Entry : FrameInfo.GameObjects)
		{
			OGameObject& Object = Entry.second;

			if (Object.Mesh == nullptr)
			{
				continue;
			}

			FPushConstantData PushConstantData{};

			PushConstantData.MeshMatrix   = Object.GetTransform().Mat4();
			PushConstantData.NormalMatrix = Object.GetTransform().NormalMatrix();

			vkCmdPushConstants(FrameInfo.CommandBuffer, PipelineLayout, VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT, 0, sizeof(FPushConstantData), &PushConstantData);
		
			Object.Mesh->Bind(FrameInfo.CommandBuffer);
			Object.Mesh->Draw(FrameInfo.CommandBuffer);
		}
	}


// Private Functions:

	void FMeshRenderSystem::CreatePipelineLayout(VkDescriptorSetLayout GlobalDescriptorSetLayout)
	{
		VkPushConstantRange PushConstantRange{};

		PushConstantRange.stageFlags = VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT;
		PushConstantRange.offset     = 0;
		PushConstantRange.size       = sizeof(FPushConstantData);

		std::vector<VkDescriptorSetLayout> DescriptorSetLayouts{ GlobalDescriptorSetLayout };

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

	void FMeshRenderSystem::CreatePipeline(VkRenderPass RenderPass)
	{
		FPipelineConfigInfo PipelineConfig{};

		FPipeline::CreateDefaultPipelineConfigInfo(PipelineConfig);
		
		PipelineConfig.RenderPass     = RenderPass;
		PipelineConfig.PipelineLayout = PipelineLayout;
		
		Pipeline = std::make_unique<FPipeline>(Device,
			                                   PipelineConfig,
			                                   "D:/VULKAN_TUTORIAL_SHADERS/SPV/vert.spv",
			                                   "D:/VULKAN_TUTORIAL_SHADERS/SPV/frag.spv");
	}

}

#pragma warning( pop ) // Vulkan SDK - End