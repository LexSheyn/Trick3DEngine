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

	private:

	// Variables:

		SEntityComponentSystem EntityComponentSystem;
	};
}