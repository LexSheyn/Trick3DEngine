#pragma once

#include "../Entity/ECSTypes.h"
#include "../../Templates/TAutoID.h"

namespace t3d
{
	class IComponent
	{
	public:

	// Constructors and Destructor:

		IComponent() : EntityID(T3D_INVALID_ENTITY_ID), PoolIndex(T3D_INVALID_POOL_INDEX) {}

		virtual ~IComponent() {}

	// Interface:

		virtual bool8 Initialize(void* Data) = 0; // To do...

	// Accessors:

		T3D_INLINE const T3D_EntityID& GetEntityID()  const { return EntityID; }

		T3D_INLINE const uint64&       GetPoolIndex() const { return PoolIndex; }

	// Modifiers: // private?

		T3D_INLINE void SetEntityID(T3D_EntityID ID) { EntityID = ID; }

		T3D_INLINE void SetPoolIndex(uint64 Index)   { PoolIndex = Index; }

	private:

	// Variables:

		T3D_EntityID EntityID;

		uint64 PoolIndex;
	};
}