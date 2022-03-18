#pragma once

#include "../Entity/FEntity.h"
#include "../Components/Components.h"

namespace t3d
{
	class SEntityComponentSystem
	{
	public:

	// Constructors and Destructor:

		 SEntityComponentSystem () {}
		~SEntityComponentSystem () {}

		T3D_NO_COPY(SEntityComponentSystem);
		T3D_NO_MOVE(SEntityComponentSystem);

	// Entity Functions:

		T3D_NO_DISCARD T3D_EntityID CreateEntity();

		void AddChild                  (T3D_EntityID Parent, T3D_EntityID Child);
		void RemoveChild               (T3D_EntityID Parent, T3D_EntityID Child);
		void RemoveEntity              (T3D_EntityID& EntityID);
		void ReserveEntities           (uint64 NumEntities);
		void ReserveEntityReuseList    (uint64 NumEntities);

	// Component Functions:

		template<typename ComponentType>
		void AddComponent(T3D_EntityID EntityID)
		{
			AddComponentInternal(EntityID, CreateComponent<ComponentType>(Components[ComponentType::ID], EntityID));
		}

		template<typename ComponentType>
		void RemoveComponent(T3D_EntityID EntityID)
		{
			RemoveComponentInternal(EntityID, ComponentType::ID, ComponentType::Size);
		}

		template<typename ComponentType>
		ComponentType* GetComponent(T3D_EntityID EntityID)
		{
			return static_cast<ComponentType*>(GetComponentInternal(EntityID, ComponentType::ID));
		}

		void RemoveAllComponents(T3D_EntityID EntityID);

	private:

	// Private Component Functions:

		template<typename ComponentType>
		FComponentDescription CreateComponent(std::vector<uint8>& Memory, T3D_EntityID EntityID)
		{
			uint64 Index = Memory.size();

			Memory.resize(Index + ComponentType::Size);

			ComponentType* Component = new(&Memory[Index]) ComponentType();

			Component->SetEntityID(EntityID);

			return FComponentDescription{ ComponentType::ID, ComponentType::Size, Index };
		}
		
		void DeleteComponent            (T3D_ComponentID ID, uint64 Size, uint64 Index);		
		void AddComponentInternal       (T3D_EntityID EntityID, FComponentDescription ComponentDescription);	
		void RemoveComponentInternal    (T3D_EntityID EntityID, T3D_ComponentID ID, uint64 Size);

		IComponent* GetComponentInternal(T3D_EntityID EntityID, T3D_ComponentID ID);

	// Variables:

		std::vector<FEntity> Entities;
		std::vector<uint64>  EntityReuseList;

		std::unordered_map<T3D_ComponentID, std::vector<uint8>> Components;
	};
}