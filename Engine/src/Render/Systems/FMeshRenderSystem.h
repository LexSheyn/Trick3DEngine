#pragma once

#include "../Pipeline/FPipeline.h"
#include "../Core/FPushConstantData.h"
#include "../Core/FUniformBufferData.h"
#include "../Core/FFrameInfo.h"

#include "../../GameObjects/OGameObject.h"

namespace t3d
{
	class FMeshRenderSystem
	{
	public:

	// Constructors and Destructor:

		FMeshRenderSystem(FDevice& Device, VkRenderPass RenderPass, VkDescriptorSetLayout GlobalDescriptorSetLayout);

		~FMeshRenderSystem();

		T3D_NO_COPY(FMeshRenderSystem);
		T3D_NO_MOVE(FMeshRenderSystem);

	// Functions:

		void Render(FFrameInfo& FrameInfo);

	private:

	// Private Functions:

		void CreatePipelineLayout(VkDescriptorSetLayout GlobalDescriptorSetLayout);

		void CreatePipeline(VkRenderPass RenderPass);

	// Variables:

		FDevice& Device;

		VkPipelineLayout PipelineLayout;

		FPipeline* Pipeline;
	};
}