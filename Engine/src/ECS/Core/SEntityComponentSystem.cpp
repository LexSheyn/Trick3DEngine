#include "../../PrecompiledHeaders/t3dpch.h"
#include "SEntityComponentSystem.h"

namespace t3d
{
// Entity Functions:

	FEntity* SEntityComponentSystem::CreateEntity()
	{
		FEntity NewEntity;

		T3D_EntityID ID = NewEntity.GetID();

		Entities.emplace(NewEntity.GetID(), std::move(NewEntity));

		return &Entities.at(ID);
	}

	void SEntityComponentSystem::RemoveEntity(FEntity* Entity)
	{
		RemoveAllComponents(Entity);

		Entities.erase(Entity->GetID());
	}

	void SEntityComponentSystem::ReserveMemory(uint64 NumEntities)
	{
		Entities.reserve(NumEntities);
	}

// Component Functions:

	void SEntityComponentSystem::RemoveAllComponents(FEntity* Entity)
	{
		std::vector<FComponentDescription>& ComponentDescriptions = Entity->GetComponentDescriptions();

		for (uint64 i = 0u; i < ComponentDescriptions.size(); i++)
		{
			DeleteComponent(ComponentDescriptions[i].ID, ComponentDescriptions[i].Size, ComponentDescriptions[i].Index);
		}
	}


// Private Component Functions:

	void SEntityComponentSystem::DeleteComponent(T3D_ComponentID ID, uint64 Size, uint64 Index)
	{
		std::vector<uint8>& ComponentArray = Components[ID];

		uint64 SourceIndex = ComponentArray.size() - Size;

		IComponent* DestinationComponent = reinterpret_cast<IComponent*>(&ComponentArray[Index]);

		IComponent* SourceComponent      = reinterpret_cast<IComponent*>(&ComponentArray[SourceIndex]);

		if (Index == SourceIndex)
		{
			ComponentArray.resize(SourceIndex);

			return;
		}

		memcpy_s(DestinationComponent, Size, SourceComponent, Size);

		std::vector<FComponentDescription>& ComponentDescriptions = SourceComponent->Entity->GetComponentDescriptions();

		for (uint64 i = 0u; i < ComponentDescriptions.size(); i++)
		{
			if (ComponentDescriptions[i].ID == ID)
			{
				ComponentDescriptions[i].Index = Index;

				break;
			}
		}

		ComponentArray.resize(SourceIndex);
	}

	void SEntityComponentSystem::AddComponentInternal(FEntity* Entity, FComponentDescription& ComponentDescription)
	{
		Entity->GetComponentDescriptions().push_back( ComponentDescription );
	}

	void SEntityComponentSystem::RemoveComponentInternal(FEntity* Entity, T3D_ComponentID ID, uint64 Size)
	{
		std::vector<FComponentDescription>& ComponentDescriptions = Entity->GetComponentDescriptions();

		for (uint64 i = 0u; i < ComponentDescriptions.size(); i++)
		{
			if (ComponentDescriptions[i].ID == ID)
			{
				DeleteComponent(ComponentDescriptions[i].ID, Size, ComponentDescriptions[i].Index);

				ComponentDescriptions[i] = ComponentDescriptions[ComponentDescriptions.size() - 1u];

				ComponentDescriptions.pop_back();
			}
		}
	}

	IComponent* SEntityComponentSystem::GetComponentInternal(FEntity* Entity, T3D_ComponentID ID)
	{
		std::vector<FComponentDescription>& ComponentDescriptions = Entity->GetComponentDescriptions();

		for (uint64 i = 0u; i < ComponentDescriptions.size(); i++)
		{
			if (ComponentDescriptions[i].ID == ID)
			{
				return reinterpret_cast<IComponent*>(&Components[ID][ComponentDescriptions[i].Index]);
			}
		}

		return nullptr;
	}


// Static Variables:

	std::unordered_map<T3D_EntityID, FEntity> SEntityComponentSystem::Entities;

	std::unordered_map<T3D_ComponentID, std::vector<uint8>> SEntityComponentSystem::Components;

}