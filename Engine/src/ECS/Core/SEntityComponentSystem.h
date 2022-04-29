#pragma once
#include "../Entity/FEntity.h"
#include "../Components/Components.h"

namespace t3d
{
	class SEntityComponentSystem
	{
	public:

	// Entity Functions:

		static T3D_NO_DISCARD T3D_EntityID CreateEntity();

		static void AddChild                  (T3D_EntityID Parent, T3D_EntityID Child);
		static void RemoveChild               (T3D_EntityID Parent, T3D_EntityID Child);
		static void RemoveEntity              (T3D_EntityID& EntityID);
		static void ReserveEntities           (uint64 NumEntities);
		static void ReserveEntityReuseList    (uint64 NumEntities);

	// Component Functions:

		template<typename ComponentType>
		static void AddComponent(T3D_EntityID EntityID)
		{
			AddComponentInternal(EntityID, CreateComponent<ComponentType>(Components[ComponentType::ID], EntityID));
		}

		template<typename ComponentType>
		static void RemoveComponent(T3D_EntityID EntityID)
		{
			RemoveComponentInternal(EntityID, ComponentType::ID, ComponentType::Size);
		}

		template<typename ComponentType>
		static ComponentType* GetComponent(T3D_EntityID EntityID)
		{
			return static_cast<ComponentType*>(GetComponentInternal(EntityID, ComponentType::ID));
		}

		static void RemoveAllComponents(T3D_EntityID EntityID);

	private:

	// Private Constructors and Destructor:

		 SEntityComponentSystem () {}
		~SEntityComponentSystem () {}

		T3D_NO_COPY(SEntityComponentSystem);
		T3D_NO_MOVE(SEntityComponentSystem);

	// Private Component Functions:

		template<typename ComponentType>
		static FComponentDescription CreateComponent(std::vector<uint8>& Memory, T3D_EntityID EntityID)
		{
			uint64 Index = Memory.size();

			Memory.resize(Index + ComponentType::Size);

			ComponentType* Component = new(&Memory[Index]) ComponentType();

			Component->SetEntityID(EntityID);

			return FComponentDescription{ ComponentType::ID, ComponentType::Size, Index };
		}
		
		static void DeleteComponent            (T3D_ComponentID ID, uint64 Size, uint64 Index);		
		static void AddComponentInternal       (T3D_EntityID EntityID, FComponentDescription ComponentDescription);	
		static void RemoveComponentInternal    (T3D_EntityID EntityID, T3D_ComponentID ID, uint64 Size);

		static IComponent* GetComponentInternal(T3D_EntityID EntityID, T3D_ComponentID ID);

	// Variables:

		static std::vector<FEntity>      Entities;
		static std::vector<T3D_EntityID> EntityReuseList;
		static std::unordered_map<T3D_ComponentID, std::vector<uint8>> Components;
	};
}