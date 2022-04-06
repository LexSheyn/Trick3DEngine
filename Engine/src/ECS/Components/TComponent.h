#pragma once

#include "IComponent.h"
#include "../../Templates/TTypeID.h"

namespace t3d
{
	template<typename T>
	struct TComponent : public IComponent
	{
		static const T3D_ComponentID ID;

		static const uint64 Size;
	};

	template<typename T>
	const T3D_ComponentID TComponent<T>::ID = TTypeID<T>::GetID();

	template<typename T>
	const uint64 TComponent<T>::Size = sizeof(T);
}