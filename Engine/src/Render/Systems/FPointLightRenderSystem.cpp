#include "../../PrecompiledHeaders/t3dpch.h"
#include "FPointLightRenderSystem.h"

// Disable warnings from Vulkan SDK:
#pragma warning( push ) // Vulkan SDK - Begin
#pragma warning( disable : 26812 ) // Uncoped Enum

namespace t3d
{
// Constructors and Destructor:

	FPointLightRenderSystem::FPointLightRenderSystem(FDevice& Device, VkRenderPass RenderPass, VkDescriptorSetLayout GlobalDescriptorSetLayout)
		: Device(Device)
	{
		this->CreatePipelineLayout(GlobalDescriptorSetLayout);

		this->CreatePipeline(RenderPass);

		LOG_TRACE("Created.");
	}

	FPointLightRenderSystem::~FPointLightRenderSystem()
	{
		vkDestroyPipelineLayout(Device.Device(), PipelineLayout, nullptr);
	}


// Functions:

	void FPointLightRenderSystem::Update(FFrameInfo& FrameInfo, FUniformBufferData& UniformBufferData)
	{
		glm::mat4 RotationMatrix = glm::rotate(glm::mat4(1.0f), FrameInfo.FrameTime, { 0.0f, -1.0f, 0.0f });

		uint32 LightIndex = 0u;

		for (auto& Entry : FrameInfo.GameObjects)
		{
			OGameObject& Object = Entry.second;

			if (Object.PointLight == nullptr)
			{
				continue;
			}

			if (LightIndex >= MAX_LIGHTS)
			{
				LOG_ERROR("Point light exceed maximum specified limit of " + std::to_string(MAX_LIGHTS) + "!");
			}

		// Update light positions:

			Object.GetTransform().SetTranslation( glm::vec3(RotationMatrix * glm::vec4(Object.GetTransform().GetTranslation(), 1.0f)) );

		// Copy light to UniformBufferData:

			UniformBufferData.PointLights[LightIndex].Position = glm::vec4(Object.GetTransform().GetTranslation(), 1.0f);
			UniformBufferData.PointLights[LightIndex].Color    = glm::vec4(Object.Color, Object.PointLight->LightIntensity);

			LightIndex++;
		}

		UniformBufferData.NumLights = LightIndex;
	}

	void FPointLightRenderSystem::Render(FFrameInfo& FrameInfo)
	{
		Pipeline->Bind(FrameInfo.CommandBuffer);

		vkCmdBindDescriptorSets(FrameInfo.CommandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, PipelineLayout, 0, 1, &FrameInfo.GlobalDescriptorSet, 0, nullptr);

		for (auto& Entry : FrameInfo.GameObjects)
		{
			OGameObject& Object = Entry.second;

			if (Object.PointLight == nullptr)
			{
				continue;
			}

			FPointLightPushConstant PushConstant{};

			PushConstant.Position = glm::vec4(Object.GetTransform().GetTranslation(), 1.0f);
			PushConstant.Color    = glm::vec4(Object.Color, Object.PointLight->LightIntensity);
			PushConstant.Radius   = Object.GetTransform().GetScale().x;

			vkCmdPushConstants(FrameInfo.CommandBuffer, PipelineLayout, VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT, 0, sizeof(FPointLightPushConstant), &PushConstant);

			vkCmdDraw(FrameInfo.CommandBuffer, 6, 1, 0, 0);
		}		
	}


// Private Functions:

	void FPointLightRenderSystem::CreatePipelineLayout(VkDescriptorSetLayout GlobalDescriptorSetLayout)
	{
		VkPushConstantRange PushConstantRange{};
	
		PushConstantRange.stageFlags = VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT;
		PushConstantRange.offset     = 0;
		PushConstantRange.size       = sizeof(FPointLightPushConstant);

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

	void FPointLightRenderSystem::CreatePipeline(VkRenderPass RenderPass)
	{
		FPipelineConfigInfo PipelineConfig{};

		FPipeline::CreateDefaultPipelineConfigInfo(PipelineConfig);
		
		PipelineConfig.BindingDescriptions.clear();
		PipelineConfig.AttributeDescriptions.clear();
		PipelineConfig.RenderPass     = RenderPass;
		PipelineConfig.PipelineLayout = PipelineLayout;
		
		Pipeline = std::make_unique<FPipeline>(Device,
			                                   PipelineConfig,
			                                   "D:/VULKAN_TUTORIAL_SHADERS/SPV/point_light.vert.spv",
			                                   "D:/VULKAN_TUTORIAL_SHADERS/SPV/point_light.frag.spv");
	}

}

#pragma warning( pop ) // Vulkan SDK - End