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

	// ISystem Interface:

		void OnUpdate         () override;
		void OnFixedUpdate    () override;
		void OnLateUpdate     () override;

	// Functions:

		void Render    (FScene& Scene);

	private:

	// Variables:

		FRenderer&        Renderer;
		PGraphicsPipeline GraphicsPipeline;
	};
}