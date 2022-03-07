#pragma once

#include "../../Types/ECSTypes.h"

namespace t3d
{
	struct IComponent
	{
		class FEntity* Entity = T3D_ENTITY_NULL_HANDLE;
	};
}