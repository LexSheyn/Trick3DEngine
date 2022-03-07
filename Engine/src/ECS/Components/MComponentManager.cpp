#include "../../PrecompiledHeaders/t3dpch.h"
#include "MComponentManager.h"

namespace t3d
{
// Functions:

	void MComponentManager::RemoveAllComponents(FEntity* Entity)
	{
		std::vector<FComponentDescription>& ComponentDescriptions = Entity->GetComponentDescriptions();

		for (uint64 i = 0u; i < ComponentDescriptions.size(); i++)
		{
			DeleteComponent(ComponentDescriptions[i].ID, ComponentDescriptions[i].Size, ComponentDescriptions[i].Index);
		}
	}


// Private Functions:

	void MComponentManager::DeleteComponent(T3D_ComponentID ID, uint64 Size, uint64 Index)
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

	void MComponentManager::AddComponentInternal(FEntity* Entity, FComponentDescription& ComponentDescription)
	{
		Entity->GetComponentDescriptions().push_back( ComponentDescription );
	}

	void MComponentManager::RemoveComponentInternal(FEntity* Entity, T3D_ComponentID ID, uint64 Size)
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

	IComponent* MComponentManager::GetComponentInternal(FEntity* Entity, T3D_ComponentID ID)
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

	std::unordered_map<T3D_ComponentID, std::vector<uint8>> MComponentManager::Components;

}