#include "../../../PrecompiledHeaders/t3dpch.h"
#include "RMeshRenderSystem.h"

// Disable warnings from Vulkan SDK:
#pragma warning( push ) // Vulkan SDK - Begin
#pragma warning( disable : 26812 ) // Uncoped Enum

namespace t3d
{
// Constructors and Destructor:

	RMeshRenderSystem::RMeshRenderSystem(FRenderer& Renderer)
		: IRenderSystem(Renderer)
	{
		this->CreateDescriptorPool();
		this->CreatePipelineLayout();
		this->CreatePipeline();

		LOG_TRACE("Created.");
	}

	RMeshRenderSystem::~RMeshRenderSystem()
	{
		for (uint64 i = 0u; i < UniformBuffers.Size(); i++)
		{
			delete UniformBuffers[i];
		}

		LOG_TRACE("Deleted.");
	}


// Functions:

	void RMeshRenderSystem::Render(FScene& Scene)
	{
	// Camera:

		MeshUniform.CameraProjection  = Scene.TestCamera.GetProjection();
		MeshUniform.CameraView        = Scene.TestCamera.GetView();

	// Directional Light:

		MeshUniform.LightDirection = SEntityComponentSystem::GetComponent<CDirectionalLight>(Scene.LightSource)->Direction;
		MeshUniform.LightAmbient   = SEntityComponentSystem::GetComponent<CDirectionalLight>(Scene.LightSource)->Ambient;

	// Uniform submition:

		UniformBuffers[Renderer.GetFrameIndex()]->WriteToBuffer(&MeshUniform);
		UniformBuffers[Renderer.GetFrameIndex()]->Flush();

		for (uint64 i = 0u; i < Scene.EntityList.size(); i++)
		{
		// Binding Pipeline and Descriptor sets:

			Pipeline->Bind(Renderer.GetCurrentCommandBuffer());

			vkCmdBindDescriptorSets(Renderer.GetCurrentCommandBuffer(), VK_PIPELINE_BIND_POINT_GRAPHICS, PipelineLayout, 0, 1, &DescriptorSets[Renderer.GetFrameIndex()], 0, nullptr);

		// Transform:

			MeshConstant.Translation = SEntityComponentSystem::GetComponent<CTransform>(Scene.EntityList[i])->Translation;
			MeshConstant.Rotation    = SEntityComponentSystem::GetComponent<CTransform>(Scene.EntityList[i])->Rotation;
			MeshConstant.Scale       = SEntityComponentSystem::GetComponent<CTransform>(Scene.EntityList[i])->Scale;

			vkCmdPushConstants(Renderer.GetCurrentCommandBuffer(), PipelineLayout, VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT, 0, sizeof(FMeshPushConstant), &MeshConstant);

		// Draw command submition:

			SEntityComponentSystem::GetComponent<CModel>(Scene.EntityList[i])->Mesh->Bind(Renderer.GetCurrentCommandBuffer());
			SEntityComponentSystem::GetComponent<CModel>(Scene.EntityList[i])->Mesh->Draw(Renderer.GetCurrentCommandBuffer());
		}
	}


// Private Functions:

	void RMeshRenderSystem::CreateDescriptorPool()
	{
		DescriptorPool = FDescriptorPool::Constructor(Renderer.GetDevice())
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
			UniformBuffers[i] = new FDeviceBuffer(Renderer.GetDevice(),
				                                  sizeof(FMeshUniform),
				                                  1,
				                                  VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT,
				                                  VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT);

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

		if (vkCreatePipelineLayout(Renderer.GetDevice().Device(), &PipelineLayoutInfo, nullptr, &PipelineLayout) != VK_SUCCESS)
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
		
		Pipeline = new FPipeline(Renderer.GetDevice(),
			                     PipelineConfig,
			                     "D:/T3D_Shaders/SPIR-V/MeshShader_vert.spv",
			                     "D:/T3D_Shaders/SPIR-V/MeshShader_frag.spv");
	}

	void RMeshRenderSystem::Update()
	{
		LOG_TRACE("UPDATED!");
	}

}

#pragma warning( pop ) // Vulkan SDK - End