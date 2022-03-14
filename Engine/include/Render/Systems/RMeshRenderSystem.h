#pragma once

#include "IRenderSystem.h"
#include "../Primitives/Mesh/FMesh.h"

namespace t3d
{
	class RMeshRenderSystem : public IRenderSystem
	{
	public:

	// Constructors and Destructor:

		 RMeshRenderSystem (FDevice& Device, FRenderer& Renderer);
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
	};
}