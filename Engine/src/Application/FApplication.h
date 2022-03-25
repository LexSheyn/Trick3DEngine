#pragma once

#include "../ECS/Systems/NRenderSystem.h"
#include "../Scene/MSceneManager.h"
#include "../SFX/FSound.h"
#include "../Time/FClock.h"
#include "../Updater/FUpdater.h"

namespace t3d
{
	class FApplication
	{
	public:

	// Constructors and Destructor:

		 FApplication ();
		~FApplication ();

		T3D_NO_COPY(FApplication);
		T3D_NO_MOVE(FApplication);

	// Functions:

		void Run       ();
		void Update    ();
		void Render    ();

	private:

	// Variables:

		int32 Width;
		int32 Height;

		FClock Clock;

		FWindow   Window;
		FDevice   Device;
		FRenderer Renderer;
		NRenderSystem RenderSystem;

		MSceneManager SceneManager;
	};
}