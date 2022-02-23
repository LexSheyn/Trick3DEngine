#pragma once

#include "DComponent.h"
#include "../Window/FWindow.h"
#include "../GameObjects/OGameObject.h"

namespace t3d
{
	class CMovementComponent : DComponent
	{
	public:

	// Constructors and Destructor:

		//

	// Functions:

		void MoveInPlaneXZ(FWindow& Window, OGameObject& GameObject, const float32& DeltaTime);

		void Move(FWindow& Window, OGameObject& Object, const float32& DeltaTime);

	// Variables:

		float32 MoveSpeed{ 3.0f };
		float32 TurnSpeed{ 1.5f };
	};
}