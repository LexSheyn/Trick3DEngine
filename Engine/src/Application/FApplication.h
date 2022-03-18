#pragma once

#include "../ECS/Systems/Render/RMeshRenderSystem.h"
#include "../Scene/MSceneManager.h"
#include "../SFX/FSound.h"
#include "../Time/FClock.h"
#include "../Time/FDeltaTime.h"
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
		RMeshRenderSystem MeshRenderSystem;

		MSceneManager SceneManager;
	};
}