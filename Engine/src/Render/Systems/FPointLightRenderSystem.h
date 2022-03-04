#pragma once

#include "../Pipeline/FPipeline.h"
#include "../Core/FPushConstantData.h"
#include "../Core/FUniformBufferData.h"
#include "../Core/FFrameInfo.h"

#include "../../GameObjects/OGameObject.h"

namespace t3d
{
	class FPointLightRenderSystem
	{
	public:

	// Constructors and Destructor:

		FPointLightRenderSystem(FDevice& Device, VkRenderPass RenderPass, VkDescriptorSetLayout GlobalDescriptorSetLayout);

		~FPointLightRenderSystem();

		T3D_NO_COPY(FPointLightRenderSystem);
		T3D_NO_MOVE(FPointLightRenderSystem);

	// Functions:

		void Update(FFrameInfo& FrameInfo, FUniformBufferData& UniformBufferData);

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