#pragma once

#include "IRenderSystem.h"
#include "../../../Render/Core/FPushConstantData.h"
#include "../../../Render/Core/FUniformBufferData.h"

namespace t3d
{
	class FPointLightRenderSystem : public IRenderSystem
	{
	public:

	// Constructors and Destructor:

		 FPointLightRenderSystem (FRenderer& Renderer);
		~FPointLightRenderSystem () override;

		T3D_NO_COPY(FPointLightRenderSystem);
		T3D_NO_MOVE(FPointLightRenderSystem);

	// Functions:

		void Render(FScene& Scene) override;

	private:

	// Private Functions:

		void CreateDescriptorPool    () override;
		void CreatePipelineLayout    () override;
		void CreatePipeline          () override;

	// Variables:

		TArray<FDeviceBuffer*, FSwapchain::MAX_FRAMES_IN_FLIGHT> UniformBuffers;

	public:

	// ISystem Interface:

		void Update() override {}
	};
}