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

		void T3D_CALL Update();
		void T3D_CALL Render(FScene& Scene) override;

	private:

	// Private Functions:

		void T3D_CALL CreateDescriptorPool    () override;
		void T3D_CALL CreatePipelineLayout    () override;
		void T3D_CALL CreatePipeline          () override;
	};
}