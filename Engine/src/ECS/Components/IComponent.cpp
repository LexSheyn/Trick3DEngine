#include "../../PCH/t3dpch.h"
#include "IComponent.h"

namespace t3d
{
// Accessors:

	const T3D_EntityID& IComponent::GetEntityID() const
	{
		return EntityID;
	}


// Modifiers:

	void IComponent::SetEntityID(T3D_EntityID ID)
	{
		EntityID = ID;
	}

}