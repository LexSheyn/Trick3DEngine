#pragma once

#include "../ECS/Core/SEntityComponentSystem.h"
#include "../ResourceManagers/Model/MModelManager.h"

namespace t3d
{
	class FScene
	{
	public:

	// Constructors and Destructor:

		 FScene ();
		~FScene ();

		T3D_NO_COPY(FScene);
		T3D_NO_MOVE(FScene);

	// Functions:

		void Update ();
		void CreateTestEntity();
		void DeleteTestEntity();
		void LoadTestMesh();

//	private:

	// Variables:

		// TEST
		SEntityComponentSystem ECS;

		std::vector<T3D_EntityID> EntityList;

		FMesh* MeshPtr;

		FCamera TestCamera;

	// Systems:

		//
	};
}