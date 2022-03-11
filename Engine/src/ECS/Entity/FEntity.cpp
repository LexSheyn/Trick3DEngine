#include "../../PrecompiledHeaders/t3dpch.h"
#include "FEntity.h"

namespace t3d
{
// Constructors and Destructor:

	FEntity::FEntity()
		: Index(0)
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

	const uint64& FEntity::GetIndex() const
	{
		return Index;
	}

	std::vector<FComponentDescription>& FEntity::GetComponentDescriptions()
	{
		return ComponentDescriptions;
	}


// Modifiers:

	void FEntity::SetIndex(uint64 Value)
	{
		Index = Value;
	}

}