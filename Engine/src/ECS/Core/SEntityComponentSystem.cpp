#include "../../PrecompiledHeaders/t3dpch.h"
#include "SEntityComponentSystem.h"

namespace t3d
{
// Entity Functions:

	FEntity* SEntityComponentSystem::CreateEntity()
	{
		FEntity* NewEntity = nullptr;

		if (!EntityReuseList.empty())
		{
			NewEntity = &Entities.at(EntityReuseList.at(0));

			EntityReuseList.at(0) = EntityReuseList.back();
			EntityReuseList.pop_back();
		}
		else
		{
			Entities.push_back(FEntity());

			NewEntity = &Entities.back();

			NewEntity->SetIndex(Entities.size() - 1u);
		}

		return NewEntity;
	}

	void SEntityComponentSystem::RemoveEntity(FEntity* Entity)
	{
		RemoveAllComponents(Entity);

		// Mark Entity as 'Removed' so it is no longer gets updated.

		EntityReuseList.push_back(Entity->GetIndex());

		Entity = nullptr;
	}

	void SEntityComponentSystem::ReserveEntities(uint64 NumEntities)
	{
		Entities.reserve(NumEntities);
	}

	void SEntityComponentSystem::ReserveEntityReuseList(uint64 NumEntities)
	{
		EntityReuseList.reserve(NumEntities);
	}

// Component Functions:

	void SEntityComponentSystem::RemoveAllComponents(FEntity* Entity)
	{
		std::vector<FComponentDescription>& ComponentDescriptions = Entity->GetComponentDescriptions();

		for (uint64 i = 0u; i < ComponentDescriptions.size(); i++)
		{
			DeleteComponent(ComponentDescriptions[i].ID, ComponentDescriptions[i].Size, ComponentDescriptions[i].Index);
		}

		ComponentDescriptions.clear();
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

				ComponentDescriptions[i] = ComponentDescriptions.back();

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

	std::vector<FEntity> SEntityComponentSystem::Entities;
	std::vector<uint64>  SEntityComponentSystem::EntityReuseList;

	std::unordered_map<T3D_ComponentID, std::vector<uint8>> SEntityComponentSystem::Components;

}