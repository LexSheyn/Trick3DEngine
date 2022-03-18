#pragma once

#include "../ECS/Core/SEntityComponentSystem.h"

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

//	private:

	// Variables:

		// TEST
		SEntityComponentSystem ECS;

		T3D_EntityID TestEntity;

		FCamera TestCamera;

	// Systems:

		//
	};
}