#pragma once

#include "ISystem.h"
#include "../../Render/Core/FRenderer.h"
#include "../../Render/Pipeline/PGraphicsPipeline.h"
#include "../../Scene/FScene.h"
#include "../../Time/FDeltaTime.h"
#include "../../Events/Experimental/SEvent.h"

namespace t3d
{
	class FRenderSystem : public ISystem
	{
	public:

	// Constructors and Destructor:

		 FRenderSystem    (FRenderer& Renderer);
		~FRenderSystem    ();

		T3D_NO_COPY(FRenderSystem);
		T3D_NO_MOVE(FRenderSystem);

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