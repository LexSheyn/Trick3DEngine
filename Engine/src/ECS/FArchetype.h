#pragma once

#include "TTypeIDGenerator.h"

namespace t3d
{
	typedef uint8* T3D_ComponentData;
	
	struct FArchetype
	{
		T3D_ArchetypeID Type;

		std::vector<T3D_ComponentData> ComponentData;

		std::vector<T3D_EntityID>      EntityIDs;

		std::vector<size_t>            ComponentDataSize;
	};
}