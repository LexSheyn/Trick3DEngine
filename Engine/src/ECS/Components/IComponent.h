#pragma once

#include "EComponentType.h"
#include "../Entity/ECSTypes.h"

namespace t3d
{
	struct IComponent
	{
		T3D_EntityID EntityID;
	};
}