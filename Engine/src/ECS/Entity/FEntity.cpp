#include "../../PrecompiledHeaders/t3dpch.h"
#include "FEntity.h"

namespace t3d
{
// Constructors and Destructor:

	FEntity::FEntity(T3D_EntityID Value)
		: ID(Value),
		  Parent(T3D_ENTITY_INVALID_ID)
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

	const T3D_EntityID& FEntity::GetParent() const
	{
		return Parent;
	}

	std::vector<T3D_EntityID>& FEntity::GetChildren()
	{
		return Children;
	}


// Modifiers:

	void FEntity::SetParent(T3D_EntityID EntityID)
	{
		Parent = EntityID;
	}

}