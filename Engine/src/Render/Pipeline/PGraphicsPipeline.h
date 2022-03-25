#pragma once

#include "IPipeline.h"
#include "../Primitives/Mesh/FMesh.h"

namespace t3d
{
	class PGraphicsPipeline : public IPipeline
	{
	public:

	// Constructors and Destructor:

		 PGraphicsPipeline (FRenderer& Renderer);
		~PGraphicsPipeline ();

		T3D_NO_COPY(PGraphicsPipeline);
		T3D_NO_MOVE(PGraphicsPipeline);

	// IPipeline Public Interface:

		void Bind (VkCommandBuffer CommandBuffer) override;

	private:

	// IPipeline Private Interface:
		
		void Configure               () override;
		void CreateShaderModule      (VkShaderModule* ShaderModule, const std::vector<char8>& ShaderCode) override;
		void CreateUniformBuffers    () override;
		void CreateDescriptors       () override;
		void CreatePipelineLayout    () override;
		void Create                  () override;

	// Private Functions:

		void Init();

	// Variables:

		TArray<FDeviceBuffer*, FSwapchain::MaxFramesInFlight> UniformBuffers;

		FDescriptorSetLayout* DescriptorSetLayout;
		TArray<VkDescriptorSet, FSwapchain::MaxFramesInFlight> DescriptorSets;
		FDescriptorPool* DescriptorPool;

		VkShaderModule VertexShaderModule;
		VkShaderModule FragmentShaderModule;

	// TEST

		FMeshUniform      MeshUniform;
		FMeshPushConstant MeshConstant;

		friend class NRenderSystem;
	};
}