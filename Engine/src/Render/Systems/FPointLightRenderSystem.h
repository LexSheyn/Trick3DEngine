#pragma once

#include "IRenderSystem.h"
#include "../Pipeline/FPipeline.h"
#include "../Core/FPushConstantData.h"
#include "../Core/FUniformBufferData.h"

namespace t3d
{
	class FPointLightRenderSystem : public IRenderSystem
	{
	public:

	// Constructors and Destructor:

		 FPointLightRenderSystem (FDevice& Device, FRenderer& Renderer);
		~FPointLightRenderSystem () override;

		T3D_NO_COPY(FPointLightRenderSystem);
		T3D_NO_MOVE(FPointLightRenderSystem);

	// Functions:

		void Update();

		void Render(FScene& Scene) override;

	private:

	// Private Functions:

		void CreateDescriptorPool    () override;
		void CreatePipelineLayout    () override;
		void CreatePipeline          () override;
	};
}