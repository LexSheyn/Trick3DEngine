#pragma once

#include "IRenderSystem.h"
#include "../Primitives/Mesh/FMesh.h"
#include "../../ResourceManagers/Model/MModelManager.h"

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

		void T3D_CALL Render(FScene& Scene) override;

	private:

	// Private Functions:

		void T3D_CALL CreateDescriptorPool    () override;
		void T3D_CALL CreatePipelineLayout    () override;
		void T3D_CALL CreatePipeline          () override;

	// TEST

		FMeshData MeshData;

		FMeshPushConstant MeshPushConstant;

		FMesh* Mesh;
	};
}