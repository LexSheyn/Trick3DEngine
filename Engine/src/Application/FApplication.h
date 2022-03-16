#pragma once

#include "../Render/Systems/RMeshRenderSystem.h"
#include "../Scene/MSceneManager.h"
#include "../SFX/FSound.h"

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

		void T3D_CALL Run       ();
		void T3D_CALL Update    ();
		void T3D_CALL Render    ();

	private:

	// Variables:

		int32 Width;
		int32 Height;

		FWindow   Window;
		FDevice   Device;
		FRenderer Renderer;
		RMeshRenderSystem MeshRenderSystem;

		MSceneManager SceneManager;
	};
}