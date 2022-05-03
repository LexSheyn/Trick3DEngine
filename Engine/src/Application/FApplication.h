#pragma once

#include "../ECS/Systems/FRenderSystem.h"
#include "../Scene/MSceneManager.h"
#include "../SFX/FSound.h"
#include "../Time/FClock.h"
#include "../Updater/FUpdater.h"
#include "../Time/FDeltaTime.h"
#include "../Logger/FLoggerEx.h"

namespace t3d
{
	class FApplication
	{
	public:

	// Constructors and Destructor:

		 FApplication    ();
		~FApplication    ();

		T3D_NO_COPY(FApplication);
		T3D_NO_MOVE(FApplication);

	// Functions:

		void Run            ();
		void Update         ();
		void FixedUpdate    ();
		void LateUpdate     ();
		void Render         ();

	private:

		FLoggerEx Logger;

	// Variables:

		int32 Width;
		int32 Height;

		FClock Clock;

		FUpdater  Updater;
		FWindow   Window;
		FDevice   Device;
		FRenderer Renderer;
		FRenderSystem RenderSystem;

		MSceneManager SceneManager;
	};
}