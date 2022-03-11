#pragma once

#include "../Components/Components.h"
#include "../Components/FComponentDescription.h"
#include "../Entity/FEntity.h"

namespace t3d
{
	class SEntityComponentSystem
	{
	public:

	// Entity Functions:

		[[nodiscard]] static FEntity* CreateEntity();

		static void RemoveEntity(FEntity* Entity);

		static void ReserveEntities(uint64 NumEntities);

		static void ReserveEntityReuseList(uint64 NumEntities);

	// Component Functions:

		template<typename ComponentType>
		static void AddComponent(FEntity* Entity)
		{
			FComponentDescription ComponentDescription = CreateComponent<ComponentType>(Components[ComponentType::ID], Entity);

			AddComponentInternal(Entity, ComponentDescription);
		}

		template<typename ComponentType>
		static void RemoveComponent(FEntity* Entity)
		{
			RemoveComponentInternal(Entity, ComponentType::ID, ComponentType::Size);
		}

		template<typename ComponentType>
		static ComponentType* GetComponent(FEntity* Entity)
		{
			return static_cast<ComponentType*>(GetComponentInternal(Entity, ComponentType::ID));
		}

		static void RemoveAllComponents(FEntity* Entity);

	private:

	// Private Component Functions:

		template<typename ComponentType>
		static FComponentDescription CreateComponent(std::vector<uint8>& Memory, FEntity* Entity)
		{
			uint64 Index = Memory.size();

			Memory.resize(Index + ComponentType::Size);

			ComponentType* Component = new(&Memory[Index]) ComponentType();

			Component->Entity = Entity;

			return FComponentDescription{ ComponentType::ID, ComponentType::Size, Index };
		}
		
		static void DeleteComponent(T3D_ComponentID ID, uint64 Size, uint64 Index);
		
		static void AddComponentInternal(FEntity* Entity, FComponentDescription& ComponentDescription);
		
		static void RemoveComponentInternal(FEntity* Entity, T3D_ComponentID ID, uint64 Size);
		
		static IComponent* GetComponentInternal(FEntity* Entity, T3D_ComponentID ID);

	// Private Constructors and Destructor:

		SEntityComponentSystem() {}

		~SEntityComponentSystem() {}

		T3D_NO_COPY(SEntityComponentSystem);
		T3D_NO_MOVE(SEntityComponentSystem);

	// Variables:

		static std::vector<FEntity> Entities;
		static std::vector<uint64>  EntityReuseList;

		static std::unordered_map<T3D_ComponentID, std::vector<uint8>> Components;
	};
}