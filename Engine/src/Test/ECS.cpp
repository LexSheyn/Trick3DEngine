#include "../PrecompiledHeaders/t3dpch.h"
#include "ECS.h"

namespace t3d
{
// Constructors and Destructor:

	ECS::ECS()
	{
	}

	ECS::~ECS()
	{
		for (std::map<uint64, std::vector<uint8>>::iterator it = Components.begin(); it != Components.end(); it++)
		{
			uint64 TypeSize = BaseECSComponent::GetTypeSize(it->first);

			BaseECSComponent::ECSComponentFreeFunction FreeFunction = BaseECSComponent::GetTypeFreeFunction(it->first);

			for (uint64 i = 0u; i < it->second.size(); i += TypeSize)
			{
				FreeFunction(reinterpret_cast<BaseECSComponent*>(&it->second[i])); // Pointless, does not work.
			}
		}

		for (uint64 i = 0u; i < Entities.size(); i++)
		{
			delete Entities[i];
		}
	}


// Entity Functions:

	EntityHandle ECS::MakeEntity(BaseECSComponent** EntityComponents, const uint64* ComponentIDs, uint64 NumComponents)
	{
	// Creating Entity:

		std::pair<uint64, std::vector<std::pair<uint64, uint64>>>* NewEntity = new std::pair<uint64, std::vector<std::pair<uint64, uint64>>>();

		EntityHandle Handle = static_cast<EntityHandle>(NewEntity);

	// Adding Components:

		for (uint64 i = 0u; i < NumComponents; i++)
		{
			if (BaseECSComponent::IsTypeValid(ComponentIDs[i]))
			{
				LOG_ERROR("Invalid Component ID: " + std::to_string(ComponentIDs[i]));

				delete NewEntity;
				
				return ENTITY_NULL_HANDLE;
			}

			this->AddComponentInternal(Handle, NewEntity->second, ComponentIDs[i], EntityComponents[i]);
		}

	// Putting Entity into storage:

		NewEntity->first = Entities.size();

		Entities.push_back(NewEntity);

		return Handle;
	}

	void ECS::RemoveEntity(EntityHandle Handle)
	{
		std::vector<std::pair<uint64, uint64>> Entity = this->HandleToEntity(Handle);

		for (uint64 i = 0u; i < Entity.size(); i++)
		{
			this->DeleteComponent(Entity[i].first, Entity[i].second);
		}

		uint64 DestinationIndex = this->HandleToEntityIndex(Handle);

		uint64 SourceIndex = Entities.size() - 1u;

		delete Entities[DestinationIndex]; // Pointless, does not work.

		Entities[DestinationIndex] = Entities[SourceIndex];

		Entities[DestinationIndex]->first = DestinationIndex;

		Entities.pop_back();
	}

	void ECS::UpdateSystems(const float32& DeltaTime, ECSSystemList& Systems)
	{
		std::vector<BaseECSComponent*> ComponentParameters;
		std::vector<std::vector<uint8>*> ComponentArrays;

		for (uint64 i = 0u; i < Systems.Size(); i++)
		{
			const std::vector<uint64>& ComponentTypes = Systems[i]->GetComponentTypes();

			if (ComponentTypes.size() == 1u)
			{
				uint64 TypeSize = BaseECSComponent::GetTypeSize(ComponentTypes[0]);

				std::vector<uint8>& ComponentArray = Components[ComponentTypes[0]];

				for (uint64 j = 0u; j < ComponentArray.size(); j += TypeSize)
				{
					BaseECSComponent* Component = reinterpret_cast<BaseECSComponent*>(&ComponentArray[j]);

					Systems[i]->UpdateComponents(DeltaTime, &Component);
				}
			}
			else
			{
				this->UpdateSystemWithMultipleComponents(i, Systems, DeltaTime, ComponentTypes, ComponentParameters, ComponentArrays);
			}
		}
	}


// Private Functions:

	void ECS::AddComponentInternal(EntityHandle Handle, std::vector<std::pair<uint64, uint64>>& Entity, uint64 ComponentID, BaseECSComponent* Component)
	{
		BaseECSComponent::ECSComponentCreateFunction CreateFunction = BaseECSComponent::GetTypeCreateFunction(ComponentID);

		std::pair<uint64, uint64> NewPair;

		NewPair.first = ComponentID;

		NewPair.second = CreateFunction(Components[ComponentID], Handle, Component);

		Entity.push_back(NewPair);
	}

	void ECS::DeleteComponent(uint64 ComponentID, uint64 Index)
	{
		std::vector<uint8>& ComponentArray = Components[ComponentID];

		BaseECSComponent::ECSComponentFreeFunction FreeFunction = BaseECSComponent::GetTypeFreeFunction(ComponentID);

		uint64 TypeSize = BaseECSComponent::GetTypeSize(ComponentID);

		uint64 SourceIndex = ComponentArray.size() - TypeSize;

		BaseECSComponent* DestinationComponent = reinterpret_cast<BaseECSComponent*>(&ComponentArray[Index]);

		BaseECSComponent* SourceComponent = reinterpret_cast<BaseECSComponent*>(&ComponentArray[SourceIndex]);

		FreeFunction(DestinationComponent); // Pointless, does not work.

		if (Index == SourceIndex)
		{
			ComponentArray.resize(SourceIndex);

			return;
		}

		memcpy_s(DestinationComponent, TypeSize, SourceComponent, TypeSize);

		std::vector<std::pair<uint64, uint64>>& SourceComponents = this->HandleToEntity(SourceComponent->Entity);

		for (uint64 i = 0u; i < SourceComponents.size(); i++)
		{
			if (ComponentID == SourceComponents[i].first) // && SourceIndex == SourceComponents[i].second )
			{
				SourceComponents[i].second = Index;

				break;
			}
		}

		ComponentArray.resize(SourceIndex);
	}

	bool8 ECS::RemoveComponentInternal(EntityHandle Handle, uint64 ComponentID)
	{
		std::vector<std::pair<uint64, uint64>>& EntityComponents = this->HandleToEntity(Handle);

		for (uint64 i = 0u; i < EntityComponents.size(); i++)
		{
			if (ComponentID == EntityComponents[i].first)
			{
				this->DeleteComponent(EntityComponents[i].first, EntityComponents[i].second);

				uint64 SourceIndex = EntityComponents.size() - 1u;

				uint64 DestinationIndex = i;

				EntityComponents[DestinationIndex] = EntityComponents[SourceIndex];

				EntityComponents.pop_back();

				return true;
			}
		}

		return false;
	}

	BaseECSComponent* ECS::GetComponentInternal(std::vector<std::pair<uint64, uint64>>& EntityComponents, std::vector<uint8>& ComponentArray, uint64 ComponentID)
	{
		for (uint64 i = 0u; i < EntityComponents.size(); i++)
		{
			if (ComponentID == EntityComponents[i].first)
			{
				return reinterpret_cast<BaseECSComponent*>(&ComponentArray[EntityComponents[i].second]);
			}
		}

		return nullptr;
	}

	void ECS::UpdateSystemWithMultipleComponents(uint64 Index, ECSSystemList& Systems, const float32& DeltaTime, const std::vector<uint64>& ComponentTypes, std::vector<BaseECSComponent*>& ComponentParameters, std::vector<std::vector<uint8>*>& ComponentArrays)
	{
		const std::vector<BaseECSSystem::Flags>& ComponentFlags = Systems[Index]->GetComponentFlags();

		ComponentParameters.resize(std::max(ComponentParameters.size(), ComponentTypes.size()));
		ComponentArrays.resize(std::max(ComponentArrays.size(), ComponentTypes.size()));

		for (uint64 i = 0u; i < ComponentTypes.size(); i++)
		{
			ComponentArrays[i] = &Components[ComponentTypes[i]];
		}

		uint64 MinSizeIndex = this->FindLeastCommonComponent(ComponentTypes, ComponentFlags);

		uint64 TypeSize = BaseECSComponent::GetTypeSize(ComponentTypes[MinSizeIndex]);

		std::vector<uint8>& ComponentArray = *ComponentArrays[MinSizeIndex];

		for (uint64 i = 0u; i < ComponentArray.size(); i += TypeSize)
		{
			ComponentParameters[MinSizeIndex] = reinterpret_cast<BaseECSComponent*>(&ComponentArray[i]);

			std::vector<std::pair<uint64, uint64>>& EntityComponents = this->HandleToEntity(ComponentParameters[MinSizeIndex]->Entity);

			bool8 IsValid = true;

			for (uint64 j = 0u; j < ComponentTypes.size(); j ++)
			{
				if (j == MinSizeIndex)
				{
					continue;
				}

				ComponentParameters[j] = this->GetComponentInternal(EntityComponents, *ComponentArrays[j], ComponentTypes[j]);

				if ( (ComponentParameters[j] == nullptr) && ((ComponentFlags[j] & BaseECSSystem::Flags::Optional) == 0) )
				{
					IsValid = false;

					break;
				}
			}

			if (IsValid)
			{
				Systems[Index]->UpdateComponents(DeltaTime, &ComponentParameters[0]);
			}
			
		}
	}

	uint64 ECS::FindLeastCommonComponent(const std::vector<uint64>& ComponentTypes, const std::vector<BaseECSSystem::Flags>& ComponentFlags)
	{
		uint64 MinSize  = UINT64_MAX;

		uint64 MinIndex = UINT64_MAX;

		for (uint64 i = 0u; i < ComponentTypes.size(); i++)
		{
			if ( (ComponentFlags[i] & BaseECSSystem::Flags::Optional) != 0 )
			{
				continue;
			}

			uint64 TypeSize = BaseECSComponent::GetTypeSize(ComponentTypes[i]);

			uint64 Size = Components[ComponentTypes[i]].size() / TypeSize;

			if (Size <= MinSize)
			{
				MinSize  = Size;

				MinIndex = i;
			}
		}

		return MinIndex;
	}

}