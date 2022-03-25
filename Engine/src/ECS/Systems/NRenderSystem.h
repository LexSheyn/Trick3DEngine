#pragma once

#include "ISystem.h"
#include "../../Render/Core/FRenderer.h"
#include "../../Render/Pipeline/PGraphicsPipeline.h"
#include "../../Scene/FScene.h"

namespace t3d
{
	class NRenderSystem : public ISystem
	{
	public:

	// Constructors and Destructor:

		 NRenderSystem (FRenderer& Renderer);
		~NRenderSystem ();

		T3D_NO_COPY(NRenderSystem);
		T3D_NO_MOVE(NRenderSystem);

	// Functions:

		void Render (FScene& Scene);

	private:

	// Variables:

		FRenderer& Renderer;

		PGraphicsPipeline GraphicsPipeline;

	public:

	// ISystem Interface:

		void Update () override;
	};
}