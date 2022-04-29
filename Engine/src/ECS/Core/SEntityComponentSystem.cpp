#include "../../PCH/t3dpch.h"
#include "SEntityComponentSystem.h"

namespace t3d
{
// Entity Functions:

	T3D_EntityID SEntityComponentSystem::CreateEntity()
	{
		T3D_EntityID NewEntity = 0;

		if (EntityReuseList.empty())
		{
			Entities.push_back(std::move(FEntity(Entities.size())));

			NewEntity = Entities.back().GetID();
		}
		else
		{
			NewEntity = EntityReuseList.front();

			EntityReuseList.front() = EntityReuseList.back();
			EntityReuseList.pop_back();
		}

		return NewEntity;
	}

	void SEntityComponentSystem::AddChild(T3D_EntityID Parent, T3D_EntityID Child)
	{
		Entities[Parent].GetChildren().emplace_back(Child);
		Entities[Child].SetParent(Parent);
	}

	void SEntityComponentSystem::RemoveChild(T3D_EntityID Parent, T3D_EntityID Child)
	{
		std::vector<T3D_EntityID>& Children = Entities[Parent].GetChildren();

		for (uint64 i = 0u; i < Children.size(); i++)
		{
			if (Children[i] == Child)
			{
				Children[i] = Children.back();
				Children.pop_back();

				return;
			}
		}
	}

	void SEntityComponentSystem::RemoveEntity(T3D_EntityID& EntityID)
	{
		RemoveAllComponents(EntityID);

		// Mark Entity as 'Removed' so it is no longer gets updated.

		EntityReuseList.push_back(EntityID);

		EntityID = T3D_ENTITY_INVALID_ID;
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

	void SEntityComponentSystem::RemoveAllComponents(T3D_EntityID EntityID)
	{
		std::vector<FComponentDescription>& ComponentDescriptions = Entities.at(EntityID).GetComponentDescriptions();

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

		uint64 IndexLast = ComponentArray.size() - Size;

		IComponent* ComponentToReplace = reinterpret_cast<IComponent*>(&ComponentArray[Index]);

		IComponent* ComponentLast      = reinterpret_cast<IComponent*>(&ComponentArray[IndexLast]);

	// If Component to replace is the last Component - just trim last Component of the array:

		if (Index == IndexLast)
		{
			ComponentArray.resize(IndexLast);

			return;
		}

	// Otherwise replace Component by the last Component in the array:

		MemoryCopy(ComponentToReplace, Size, ComponentLast);

	// Find Entity that owns the last Component in the array and change Component index for this Entity, because
	// it has been moved to the index of replaced Component:

		std::vector<FComponentDescription>& ComponentDescriptions = Entities.at(ComponentLast->GetEntityID()).GetComponentDescriptions();

		for (uint64 i = 0u; i < ComponentDescriptions.size(); i++)
		{
			if (ComponentDescriptions[i].ID == ID)
			{
				ComponentDescriptions[i].Index = Index;

				break;
			}
		}

	// Trim last Component of the array:

		ComponentArray.resize(IndexLast);
	}

	void SEntityComponentSystem::AddComponentInternal(T3D_EntityID EntityID, FComponentDescription ComponentDescription)
	{
		Entities.at(EntityID).GetComponentDescriptions().push_back( ComponentDescription );
	}

	void SEntityComponentSystem::RemoveComponentInternal(T3D_EntityID EntityID, T3D_ComponentID ID, uint64 Size)
	{
		std::vector<FComponentDescription>& ComponentDescriptions = Entities.at(EntityID).GetComponentDescriptions();

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

	IComponent* SEntityComponentSystem::GetComponentInternal(T3D_EntityID EntityID, T3D_ComponentID ID)
	{
		std::vector<FComponentDescription>& ComponentDescriptions = Entities.at(EntityID).GetComponentDescriptions();

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