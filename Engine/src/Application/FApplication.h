#pragma once

#include "../ECS/Systems/FRenderSystem.h"
#include "../SFX/FSoundSystem.h"
#include "../Scene/MSceneManager.h"
#include "../Time/FClock.h"
#include "../Time/FDeltaTime.h"
#include "../Logger/FLoggerEx.h"
#include "../Threads/TWorkerThread.h"
#include "../Updater/FUpdaterEx.h"

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
		void Render         ();

	private:

		// TEST:
		static T3D_INLINE void T3D_CALL FixedUpdate(FObject Instance, const FLogData& Data)
		{
			Instance.Get<FApplication>()->Updater.FixedUpdate();
		}

		TWorkerThread<FLogData> FixedUpdateThread;
		FLoggerEx     Logger;

	// Variables:

		int32 Width;
		int32 Height;

		FClock Clock;

		FWindow   Window;
		FDevice   Device;
		FRenderer Renderer;

		FUpdaterEx    Updater;
		FRenderSystem RenderSystem;
		FSoundSystem  SoundSystem;

		MSceneManager SceneManager;
	};
}