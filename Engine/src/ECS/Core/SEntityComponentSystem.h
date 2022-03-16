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

		T3D_NO_DISCARD T3D_EntityID T3D_CALL CreateEntity();

		void T3D_CALL AddChild                  (T3D_EntityID Parent, T3D_EntityID Child);
		void T3D_CALL RemoveChild               (T3D_EntityID Parent, T3D_EntityID Child);
		void T3D_CALL RemoveEntity              (T3D_EntityID& EntityID);
		void T3D_CALL ReserveEntities           (uint64 NumEntities);
		void T3D_CALL ReserveEntityReuseList    (uint64 NumEntities);

	// Component Functions:

		template<typename ComponentType>
		void T3D_CALL AddComponent(T3D_EntityID EntityID)
		{
			AddComponentInternal(EntityID, CreateComponent<ComponentType>(Components[ComponentType::ID], EntityID));
		}

		template<typename ComponentType>
		void T3D_CALL RemoveComponent(T3D_EntityID EntityID)
		{
			RemoveComponentInternal(EntityID, ComponentType::ID, ComponentType::Size);
		}

		template<typename ComponentType>
		ComponentType* T3D_CALL GetComponent(T3D_EntityID EntityID)
		{
			return static_cast<ComponentType*>(GetComponentInternal(EntityID, ComponentType::ID));
		}

		void T3D_CALL RemoveAllComponents(T3D_EntityID EntityID);

	private:

	// Private Component Functions:

		template<typename ComponentType>
		FComponentDescription T3D_CALL CreateComponent(std::vector<uint8>& Memory, T3D_EntityID EntityID)
		{
			uint64 Index = Memory.size();

			Memory.resize(Index + ComponentType::Size);

			ComponentType* Component = new(&Memory[Index]) ComponentType();

			Component->SetEntityID(EntityID);

			return FComponentDescription{ ComponentType::ID, ComponentType::Size, Index };
		}
		
		void T3D_CALL DeleteComponent            (T3D_ComponentID ID, uint64 Size, uint64 Index);		
		void T3D_CALL AddComponentInternal       (T3D_EntityID EntityID, FComponentDescription ComponentDescription);	
		void T3D_CALL RemoveComponentInternal    (T3D_EntityID EntityID, T3D_ComponentID ID, uint64 Size);

		IComponent* GetComponentInternal(T3D_EntityID EntityID, T3D_ComponentID ID);

	// Variables:

		std::vector<FEntity> Entities;
		std::vector<uint64>  EntityReuseList;

		std::unordered_map<T3D_ComponentID, std::vector<uint8>> Components;
	};
}