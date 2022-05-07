#pragma once

#include "../../ECS/Core/SEntityComponentSystem.h"

namespace t3d
{
	class ISystem
	{
	public:

	// Constructors and Destructor:

		         ISystem    ();
		virtual ~ISystem    ();

	// Interface:

		virtual void OnUpdate         ();
		virtual void OnFixedUpdate    ();
		virtual void OnLateUpdate     ();
	};
}