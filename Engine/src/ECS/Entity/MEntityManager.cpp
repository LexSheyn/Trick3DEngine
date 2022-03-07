#include "../../PrecompiledHeaders/t3dpch.h"
#include "MEntityManager.h"

namespace t3d
{
// Functions:

	FEntity* MEntityManager::CreateEntity()
	{
		FEntity NewEntity;

		T3D_EntityID ID = NewEntity.GetID();

		Entities.emplace(NewEntity.GetID(), std::move(NewEntity));

		return &Entities.at(ID);
	}

	void MEntityManager::RemoveEntity(FEntity* Entity)
	{
		Entities.erase(Entity->GetID());
	}

	void MEntityManager::Reserve(uint64 Amount)
	{
		Entities.reserve(Amount);
	}


// Static Variables:

	std::unordered_map<T3D_EntityID, FEntity> MEntityManager::Entities;
}