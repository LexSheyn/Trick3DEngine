#pragma once

#include "IComponent.h"
#include "FKeyMap.h"
#include "../Window/FWindow.h"
#include "../GameObjects/OGameObject.h"

namespace t3d
{
	class CMovementComponent : IComponent
	{
	public:

	// Constructors and Destructor:

		//

	// Functions:

		void MoveInPlaneXZ(FWindow& Window, OGameObject& GameObject, const float32& DeltaTime);

		void Move(FWindow& Window, OGameObject& Object, const float32& DeltaTime);

	// Variables:

	//	FWindow& Window;

		FKeyMap Keys;

		float32 MoveSpeed{ 3.0f };
		float32 TurnSpeed{ 1.5f };
	};
}