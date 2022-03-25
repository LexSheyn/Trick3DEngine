#pragma once

#include "../Render/Pipeline/FPipelineConfigInfo.h"
#include "../Render/Pipeline/FDescriptorWriter.h"
#include "../Render/Core/FRenderer.h"
#include "../Render/Primitives/Mesh/FMesh.h"
#include "../Test/EpipelineType.h"
#include "../Test/EShaderType.h"
#include "../ResourceManagers/Shaders/MShaderManager.h"

namespace t3d
{
	class Test_Pipeline
	{
	public:

	// Constructors and Destructor:

		 Test_Pipeline (FRenderer& Renderer);
		~Test_Pipeline ();

	// Functions:

		void Create    (EPipelineType Type);
		void Bind      (VkCommandBuffer CommandBuffer);

	// Accessors:

	//	FDeviceBuffer* GetUniform(uint64 FrameIndex);

	private:

	// Private Functions:

		void Initialize ();

	// Private Configuration Functions:

		void ConfigureGraphicsPipeline          ();
		void ConfigureComputePipeline           ();
		void ConfigureRayTracingPipeline        ();
		void ConfigureSubpassShadingPipeline    ();

	// Private Creation Functions:

		void CreateGraphicsPipeline          ();
		void CreateComputePipeline           ();
		void CreateRayTracingPipeline        ();
		void CreateSubpassShadingPipeline    ();

		void CreateShaderModule (const std::vector<char8>& ShaderCode, VkShaderModule* ShaderModule);

	// Variables:

		FRenderer& Renderer;

		FPipelineConfigInfo Config;
		VkPipelineLayout    PipelineLayout;
		VkPipeline          VulkanPipeline;

		FDescriptorSetLayout* DescriptorSetLayout;
		TArray<VkDescriptorSet, FSwapchain::MaxFramesInFlight> DescriptorSets;
		FDescriptorPool* DescriptorPool;

		FMeshUniform      MeshUniform;
		FMeshPushConstant MeshConstant;
		TArray<FDeviceBuffer*, FSwapchain::MaxFramesInFlight> UniformBuffers;

		TArray<VkShaderModule, 6> ShaderModules;
	};
}