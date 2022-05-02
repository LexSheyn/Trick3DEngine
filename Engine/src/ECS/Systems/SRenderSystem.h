#pragma once

#include "ISystem.h"
#include "../../Render/Core/FRenderer.h"
#include "../../Render/Pipeline/PGraphicsPipeline.h"
#include "../../Scene/FScene.h"

namespace t3d
{
	class SRenderSystem : public ISystem
	{
	public:

	// Constructors and Destructor:

		 SRenderSystem    (FRenderer& Renderer);
		~SRenderSystem    ();

		T3D_NO_COPY(SRenderSystem);
		T3D_NO_MOVE(SRenderSystem);

	// Functions:

		void Render    (FScene& Scene);

	private:

	// Variables:

		FRenderer& Renderer;

		PGraphicsPipeline GraphicsPipeline;

	public:

	// ISystem Interface:

		void Update    () override;
	};
}