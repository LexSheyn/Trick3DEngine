#pragma once

#include "EComponentType.h"
#include "../Entity/ECSTypes.h"

namespace t3d
{
	class IComponent
	{
	public:

	// Constructors and Destructor:

		IComponent() {}

		virtual ~IComponent() {}
	};
}