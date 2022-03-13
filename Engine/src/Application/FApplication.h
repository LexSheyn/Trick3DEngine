#pragma once

#include "../Render/Systems/FMeshRenderSystem.h"
#include "../Render/Systems/FPointLightRenderSystem.h"
#include "../Render/Core/FRenderer.h"

//#include "../Events/SEventSystem.h"

namespace t3d
{
	class FApplication
	{
	public:

	// Constructors and Destructor:

		FApplication  ();
		~FApplication ();

		T3D_NO_COPY(FApplication);
		T3D_NO_MOVE(FApplication);

	// Functions:

		void InitRenderer    ();
		void Run             ();
		void Update          ();
		void Render          ();

	private:

	// Private Functions:

		void LoadGameObjects ();

	// Variables:

		int32 Width;
		int32 Height;

		FWindow   Window;
		FDevice   Device;
		FRenderer Renderer;

		// Note: Order of declaration matters!
		FDescriptorPool* DescriptorPool;

		std::unordered_map<uint32, OGameObject> GameObjects;

		std::map<std::string, FMesh*> Meshes;
	};
}