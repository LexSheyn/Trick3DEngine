#pragma once

#include "../Render/Systems/RMeshRenderSystem.h"
#include "../Render/Systems/FPointLightRenderSystem.h"
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

		void Run       ();
		void Update    ();
		void Render    ();

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