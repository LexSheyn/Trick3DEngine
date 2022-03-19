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

	// Functions;

		const FMat4& ToMatrix4x4 (CTransform* Transform);

	// Variables:

		FRenderer& Renderer;
		VkPipelineLayout PipelineLayout;
		FPipeline*       Pipeline;
		
		FDescriptorSetLayout* DescriptorSetLayout;
		TArray<VkDescriptorSet, FSwapchain::MAX_FRAMES_IN_FLIGHT> DescriptorSets;
		FDescriptorPool*      DescriptorPool;
		
		float32 Sin1; // Z
		float32 Cos1;
		
		float32 Sin2; // Y
		float32 Cos2;
		
		float32 Sin3; // X
		float32 Cos3;

		FMat4 TransformationMatrix;

	private:

	// Private Functions:

		void Initialize();

	public:

	// ISystem Interface:

		virtual void Update() = 0;
	};
}