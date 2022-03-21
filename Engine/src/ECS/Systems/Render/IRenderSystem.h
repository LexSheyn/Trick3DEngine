#pragma once

#include "../Base/ISystem.h"
#include "../../../Render/Core/FRenderer.h"
#include "../../../Render/Pipeline/FPipeline.h"
#include "../../../Render/Primitives/Mesh/FMesh.h"
#include "../../../Scene/FScene.h"

namespace t3d
{
	// Protected class.
	class IRenderSystem : public ISystem
	{
	protected:

	// Constructors and Destructor:

		         IRenderSystem (FRenderer& Renderer);
		virtual ~IRenderSystem ();

		T3D_NO_COPY(IRenderSystem);
		T3D_NO_MOVE(IRenderSystem);

	// Interface:

		virtual void Render(FScene& Scene) = 0;

		virtual void CreateDescriptorPool    () = 0;
		virtual void CreatePipelineLayout    () = 0;
		virtual void CreatePipeline          () = 0;

	// Variables:

		FRenderer& Renderer;
		VkPipelineLayout PipelineLayout;
		FPipeline*       Pipeline;
		
		FDescriptorSetLayout* DescriptorSetLayout;
		TArray<VkDescriptorSet, FSwapchain::MAX_FRAMES_IN_FLIGHT> DescriptorSets;
		FDescriptorPool*      DescriptorPool;

	private:

	// Private Functions:

		void Initialize();

	public:

	// ISystem Interface:

		virtual void Update() = 0;
	};
}