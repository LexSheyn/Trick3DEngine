#pragma once

#include "../ECS/Systems/FRenderSystem.h"
#include "../SFX/FSoundSystem.h"
#include "../Scene/MSceneManager.h"
#include "../Time/FClock.h"
#include "../Updater/FUpdater.h"
#include "../Time/FDeltaTime.h"
#include "../Logger/FLoggerEx.h"
#include "../Threads/TWorkerThread.h"

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

		TWorkerThread<FLogData> TestWorkerThread;
		FLoggerEx     Logger;

	// Variables:

		int32 Width;
		int32 Height;

		FClock Clock;

		FUpdater  Updater;
		FWindow   Window;
		FDevice   Device;
		FRenderer Renderer;
		FRenderSystem RenderSystem;
		FSoundSystem  SoundSystem;

		MSceneManager SceneManager;
	};
}