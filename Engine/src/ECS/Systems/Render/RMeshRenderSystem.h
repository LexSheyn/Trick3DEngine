#pragma once

#include "IRenderSystem.h"
#include "../../../ResourceManagers/Model/MModelManager.h"

namespace t3d
{
	class RMeshRenderSystem : public IRenderSystem
	{
	public:

	// Constructors and Destructor:

		 RMeshRenderSystem (FRenderer& Renderer);
		~RMeshRenderSystem () override;

		T3D_NO_COPY(RMeshRenderSystem);
		T3D_NO_MOVE(RMeshRenderSystem);

	// Functions:

		void Render(FScene& Scene) override;

	private:

	// Private Functions:

		void CreateDescriptorPool    () override;
		void CreatePipelineLayout    () override;
		void CreatePipeline          () override;

	// TEST

		FMeshUniform      MeshUniform;
		FMeshPushConstant MeshConstant;
		TArray<FDeviceBuffer*, FSwapchain::MAX_FRAMES_IN_FLIGHT> UniformBuffers;

	public:

	// ISystem Interface:

		void Update() override;
	};
}