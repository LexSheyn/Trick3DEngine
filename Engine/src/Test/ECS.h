#pragma once

#include "ECSSystem.h"

namespace t3d
{
	class ECS
	{
	public:

	// Constructors and Destructor:

		ECS();

		~ECS();

		T3D_NO_COPY(ECS);
		T3D_NO_MOVE(ECS);

	// Entity Functions:

		EntityHandle MakeEntity(BaseECSComponent** EntityComponents, const uint64* ComponentIDs, uint64 NumComponents);

		void RemoveEntity(EntityHandle Handle);

	// Component Functions:

		template<typename ComponentType>
		void AddComponent(EntityHandle Entity, ComponentType* Component)
		{
			this->AddComponentInternal(Entity, this->HandleToEntity(Entity), ComponentType::ID, Component);
		}

		template<typename ComponentType>
		bool8 RemoveComponent(EntityHandle Entity)
		{
			return this->RemoveComponentInternal(Entity, ComponentType::ID);
		}

		template<typename ComponentType>
		ComponentType* GetComponent(EntityHandle Entity)
		{
			return static_cast<ComponentType*>(this->GetComponentInternal(this->HandleToEntity(Entity), Components[ComponentType::ID], ComponentType::ID));
		}

	// System Functions:

		void UpdateSystems(const float32& DeltaTime, ECSSystemList& Systems);

	private:

	// Private Functions:

		T3D_INLINE std::pair<uint64, std::vector<std::pair<uint64, uint64>>>* HandleToRawType(EntityHandle Handle)
		{
			return static_cast<std::pair<uint64, std::vector<std::pair<uint64, uint64>>>*>(Handle);
		}

		T3D_INLINE uint64 HandleToEntityIndex(EntityHandle Handle)
		{
			return this->HandleToRawType(Handle)->first;
		}

		T3D_INLINE std::vector<std::pair<uint64, uint64>>& HandleToEntity(EntityHandle Handle)
		{
			return this->HandleToRawType(Handle)->second;
		}

		void AddComponentInternal(EntityHandle Handle, std::vector<std::pair<uint64, uint64>>& Entity, uint64 ComponentID, BaseECSComponent* Component);

		void DeleteComponent(uint64 ComponentID, uint64 Index);

		bool8 RemoveComponentInternal(EntityHandle Handle, uint64 ComponentID);

		BaseECSComponent* GetComponentInternal(std::vector<std::pair<uint64, uint64>>& EntityComponents, std::vector<uint8>& ComponentArray, uint64 ComponentID);

		void UpdateSystemWithMultipleComponents(uint64 Index, ECSSystemList& Systems, const float32& DeltaTime, const std::vector<uint64>& ComponentTypes, std::vector<BaseECSComponent*>& ComponentParameters, std::vector<std::vector<uint8>*>& ComponentArrays);

		uint64 FindLeastCommonComponent(const std::vector<uint64>& ComponentTypes, const std::vector<BaseECSSystem::Flags>& ComponentFlags);

	// Variables:

	//	std::vector<BaseECSSystem*> Systems;

		std::map<uint64, std::vector<uint8>> Components;

		// Vector of pointers to pairs of ComponentID and ComponentIndex.
		std::vector< std::pair<uint64, std::vector<std::pair<uint64, uint64>>>* > Entities;

//	public:
//		typedef uint64 EntityID;
//		typedef uint64 ComponentID;
//
//		struct ComponentData
//		{
//			ComponentID ID;
//
//			uint64 Index;
//		};
//
//		struct Entity
//		{
//			EntityID ID;
//
//			std::vector<ComponentData> ComponentData;
//		};
//
//		std::vector<Entity> Entities;
	};
}