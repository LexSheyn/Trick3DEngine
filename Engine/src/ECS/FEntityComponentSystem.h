#pragma once

#include "FArchetype.h"
#include "FRecord.h"

namespace t3d
{
	class FEntityComponentSystem
	{
	public:

	// Constructors and Destructor:

		FEntityComponentSystem();

		~FEntityComponentSystem();

	// Functions:

		T3D_INLINE T3D_EntityID GetNewID() { return EntityIDCounter++; }

		// First record is empty, because entity does not have any components yet.
		void RegisterEntity(const T3D_EntityID& EntityID);

		void RemoveEntity(const T3D_EntityID& EntityID);

		void RegisterSystem(const uint8& Layer, class ISystem* System);

		void RunSystems(const uint8& Layer, const float32& ElapsedMilliseconds);

	// Accessors:

		FArchetype* GetArchetype(const T3D_ArchetypeID& ArchetypeID);

	// Template Functions:

		template<class C>
		void RegisterComponent()
		{
			T3D_ComponentTypeID ComponentTypeID = TComponent<C>::GetTypeID();

			if (ComponentMap.contains(ComponentTypeID))
			{
				LOG_TRACE("Component already registered!");
				return;
			}

			ComponentMap.emplace(ComponentTypeID, new TComponent<C>); // Need brackets???
		}

		template<class C>
		bool8 IsComponentRegistered()
		{

		}

		template<class C, typename... Args>
		C* AddComponent(const T3D_EntityID& EntityID, Args&&... Arguments)
		{
			T3D_ComponentTypeID NewComponentTypeID = TComponent<C>::GetTypeID();

			if (!this->IsComponentRegistered<C>())
			{
				LOG_ERROR("Component is not registered!");
				throw;
			}

			const size_t& ComponentDataSize = ComponentMap.at(NewComponentTypeID)->GetSize();

		// This ensures that the entity is added to dummy archetype if needed:

			FRecord& Record = EntityArchetypeMap.at(EntityID);

			FArchetype* OldArchetype = Record.Archetype;

			C* NewComponent = nullptr; // Will be returned.

			FArchetype* NewArchetype = nullptr;


		}

		template<class C>
		void RemoveComponent(const T3D_EntityID& EntityID)
		{

		}

		template<class C>
		C* GetComponent(const T3D_EntityID& EntityID)
		{

		}

		template<class C>
		bool8 HasComponent(const T3D_EntityID& EntityID)
		{

		}

		template<class... C>
		std::vector<T3D_EntityID> GetEntitiesWidth()
		{

		}

	private:

	// Variables:

		std::unordered_map<T3D_EntityID, FRecord> EntityArchetypeMap;

		std::vector<FArchetype*> Archetypes;

		T3D_EntityID EntityIDCounter;

		std::unordered_map<uint8, std::vector<class ISystem*>> Systems;

		std::unordered_map<T3D_ComponentTypeID, class IComponent*> ComponentMap;

	};
}