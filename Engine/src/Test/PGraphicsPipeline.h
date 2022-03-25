#pragma once

#include "IPipeline.h"

namespace t3d
{
	class PGraphicsPipeline : public IPipeline
	{
	public:

	// Constructors and Destructor:

		 PGraphicsPipeline (FRenderer& Renderer);
		~PGraphicsPipeline ();

		T3D_NO_COPY(PGraphicsPipeline);
		T3D_NO_MOVE(PGraphicsPipeline);

	// IPipeline Public Interface:

		void Bind (VkCommandBuffer CommandBuffer) override;

	private:

	// IPipeline Private Interface:

		void CreateUniformBuffers    () override;
		void CreateDescriptors       () override;
		void CreatePipelineLayout    () override;
		void Configure               () override;
		void Create                  () override;
	};
}