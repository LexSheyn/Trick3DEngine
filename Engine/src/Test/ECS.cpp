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

	EntityHandle ECS::MakeEntity(BaseECSComponent* EntityComponents, const uint64* ComponentIDs, uint64 NumComponents)
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

			this->AddComponentInternal(Handle, NewEntity->second, ComponentIDs[i], &EntityComponents[i]);
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

		Entities.pop_back();
	}

	bool8 ECS::RemoveSystem(BaseECSSystem& System)
	{
		for (uint64 i = 0u; i < Systems.size(); i++)
		{
			if (&System == Systems[i])
			{
				Systems.erase(Systems.begin() + i);

				return true;
			}
		}

		return false;
	}

	void ECS::UpdateSystems(const float32& DeltaTime)
	{
		std::vector<BaseECSComponent*> ComponentParameters;

		for (uint64 i = 0u; i < Systems.size(); i++)
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
				this->UpdateSystemWithMultipleComponents(i, DeltaTime, ComponentTypes, ComponentParameters);
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
		std::vector<uint8>& Array = Components[ComponentID];

		BaseECSComponent::ECSComponentFreeFunction FreeFunction = BaseECSComponent::GetTypeFreeFunction(ComponentID);

		uint64 TypeSize = BaseECSComponent::GetTypeSize(ComponentID);

		uint64 SourceIndex = Array.size() - TypeSize;

		BaseECSComponent* DestinationComponent = reinterpret_cast<BaseECSComponent*>(&Array[Index]);

		BaseECSComponent* SourceComponent = reinterpret_cast<BaseECSComponent*>(&Array[SourceIndex]);

		FreeFunction(DestinationComponent); // Pointless, does not work.

		if (Index == SourceIndex)
		{
			Array.resize(SourceIndex);

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

		Array.resize(SourceIndex);
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

	BaseECSComponent* ECS::GetComponentInternal(std::vector<std::pair<uint64, uint64>>& EntityComponents, uint64 ComponentID)
	{
		for (uint64 i = 0u; i < EntityComponents.size(); i++)
		{
			if (ComponentID == EntityComponents[i].first)
			{
				return reinterpret_cast<BaseECSComponent*>(&Components[ComponentID][EntityComponents[i].second]);
			}
		}

		return nullptr;
	}

	void ECS::UpdateSystemWithMultipleComponents(uint64 Index, const float32& DeltaTime, const std::vector<uint64>& ComponentTypes, std::vector<BaseECSComponent*>& ComponentParameters)
	{
		ComponentParameters.resize(std::max(ComponentParameters.size(), ComponentTypes.size()));

		uint64 TypeSize = BaseECSComponent::GetTypeSize(ComponentTypes[0]);

		std::vector<uint8>& ComponentArray = Components[ComponentTypes[0]];

		for (uint64 i = 0u; i < ComponentArray.size(); i += TypeSize)
		{
			ComponentParameters[0] = reinterpret_cast<BaseECSComponent*>(&ComponentArray[i]);

			std::vector<std::pair<uint64, uint64>>& EntityComponents = this->HandleToEntity(ComponentParameters[0]->Entity);

			bool8 IsValid = true;

			for (uint64 j = 0u; j < ComponentTypes.size(); j ++)
			{
				if (j == 0u)
				{
					continue;
				}

				ComponentParameters[j] = this->GetComponentInternal(EntityComponents, ComponentTypes[j]);

				if (!ComponentParameters[j])
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

}