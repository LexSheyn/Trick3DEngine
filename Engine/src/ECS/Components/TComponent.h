#pragma once

#include "IComponent.h"
#include "../../Templates/TTypeID.h"

namespace t3d
{
	template<typename ComponentType>
	struct TComponent : public IComponent
	{
		static const T3D_ComponentID ID;

		static const uint64 Size;
	};

	template<typename ComponentType>
	const T3D_ComponentID TComponent<ComponentType>::ID = TTypeID<ComponentType>::GetID();

	template<typename ComponentType>
	const uint64 TComponent<ComponentType>::Size = sizeof(ComponentType);
}