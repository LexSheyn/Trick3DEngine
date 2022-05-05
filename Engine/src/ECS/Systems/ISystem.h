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

		T3D_NO_COPY(ISystem);
		T3D_NO_MOVE(ISystem);

	// Interface:

		virtual void OnUpdate         ();
		virtual void OnFixedUpdate    ();
		virtual void OnLastUpdate     ();
	};
}