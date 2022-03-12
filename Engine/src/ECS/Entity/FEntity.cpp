#include "../../PrecompiledHeaders/t3dpch.h"
#include "FEntity.h"

namespace t3d
{
// Constructors and Destructor:

	FEntity::FEntity(T3D_EntityID Value)
		: ID(Value)
	{
		ComponentDescriptions.reserve(5);
	}

	FEntity::~FEntity()
	{
	}


// Accessors:

	const T3D_EntityID& FEntity::GetID() const
	{
		return ID;
	}

	std::vector<FComponentDescription>& FEntity::GetComponentDescriptions()
	{
		return ComponentDescriptions;
	}

}