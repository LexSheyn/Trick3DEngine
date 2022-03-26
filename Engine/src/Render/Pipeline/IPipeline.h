#pragma once

#include "FPipelineConfigInfo.h"
#include "FDescriptorWriter.h"
#include "../Core/FRenderer.h"
#include "../../ResourceManagers/Shaders/MShaderManager.h"
#include "../../ResourceManagers/Shaders/MShaderManager.h"

namespace t3d
{
	class IPipeline
	{
	protected:

	// Constructors and Destructor:

		 IPipeline (FRenderer& Renderer);
		~IPipeline ();

		T3D_NO_COPY(IPipeline);
		T3D_NO_MOVE(IPipeline);

	// Public Interface:

		virtual void Bind              (VkCommandBuffer CommandBuffer) = 0;
		virtual void SubmitUniforms    () = 0;
		virtual void PushConstants     () = 0;
		
	// Private Interface:

		virtual void CreateShaderModule      (VkShaderModule* ShaderModule, const std::vector<uint32>& ShaderCode) = 0;
		virtual void Configure               () = 0;		
		virtual void CreateUniformBuffers    () = 0;
		virtual void CreateDescriptors       () = 0;
		virtual void CreatePipelineLayout    () = 0;		
		virtual void Create                  () = 0;
		
	// Variables:

		FRenderer& Renderer;
	
		FPipelineConfigInfo Config;

		VkPipelineLayout PipelineLayout;
		VkPipeline       VulkanPipeline;
	};
}