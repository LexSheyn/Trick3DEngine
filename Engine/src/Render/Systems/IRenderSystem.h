#pragma once

#include "../Core/FRenderer.h"
#include "../Pipeline/FPipeline.h"
#include "../Primitives/Mesh/FMesh.h"
#include "../../Scene/FScene.h"

namespace t3d
{
	// Protected class.
	class IRenderSystem
	{
	protected:

	// Constructors and Destructor:

		         IRenderSystem (FDevice& Device, FRenderer& Renderer);
		virtual ~IRenderSystem ();

		T3D_NO_COPY(IRenderSystem);
		T3D_NO_MOVE(IRenderSystem);

	// Functions:

		virtual void T3D_CALL Render(FScene& Scene) = 0;

	// Functions:

		virtual void T3D_CALL CreateDescriptorPool    () = 0;
		virtual void T3D_CALL CreatePipelineLayout    () = 0;
		virtual void T3D_CALL CreatePipeline          () = 0;

	// Variables:

		FDevice& Device;

		FRenderer& Renderer;

		VkPipelineLayout PipelineLayout;

		FPipeline* Pipeline;

		TArray<FDeviceBuffer*, FSwapchain::MAX_FRAMES_IN_FLIGHT> UniformBuffers;

		TArray<VkDescriptorSet, FSwapchain::MAX_FRAMES_IN_FLIGHT> DescriptorSets;

		FDescriptorSetLayout* DescriptorSetLayout;

		FDescriptorPool* DescriptorPool;

	private:

	// Private Functions:

		void Initialize();
	};
}