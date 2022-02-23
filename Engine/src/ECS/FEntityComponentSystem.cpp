#include "../PrecompiledHeaders/t3dpch.h"
#include "FEntityComponentSystem.h"

namespace t3d
{
// Constructors and Destructor:

	FEntityComponentSystem::FEntityComponentSystem()
		: EntityIDCounter(1) // 0 is reserved for NULL_ENTITY
	{
	}

	FEntityComponentSystem::~FEntityComponentSystem()
	{
	}


// Functions:

	void FEntityComponentSystem::RegisterEntity(const T3D_EntityID& EntityID)
	{
		FRecord Record{};

		Record.Archetype = nullptr;
		Record.Index     = 0;

		EntityArchetypeMap[EntityID] = Record;
	}

	void FEntityComponentSystem::RemoveEntity(const T3D_EntityID& EntityID)
	{
	}

	void FEntityComponentSystem::RegisterSystem(const uint8& Layer, ISystem* System)
	{
		Systems[Layer].push_back(System);
	}

	void FEntityComponentSystem::RunSystems(const uint8& Layer, const float32& ElapsedMilliseconds)
	{
	//	for (ISystem* Sustem : Systems.at(Layer))
	//	{
	//		const T3D_ArchetypeID& Key = System->GetKey();
	//
	//		for (FArchetype* Archetype : Archetypes)
	//		{
	//			if (std::includes(Archetype->Type.begin(), Archetype->Type.end(), Key.begin(), Key.end()))
	//			{
	//			// This archetype has all the types required by the system
	//			// so we can pull it's relevant data, reinterpret them as 
	//			// their correct types, and call the function in the system.
	//
	//				System->DoAction(ElapsedMilliseconds, Archetype);
	//			}
	//		}
	//	}
	}

	FArchetype* FEntityComponentSystem::GetArchetype(const T3D_ArchetypeID& ArchetypeID)
	{
		for (FArchetype* Archetype : Archetypes)
		{
			if (Archetype->Type == ArchetypeID)
			{
				return Archetype;
			}
		}

	// Archetype does not exist, so create a new one.

		FArchetype* NewArchetype = new FArchetype;

		NewArchetype->Type = ArchetypeID;

		Archetypes.push_back(NewArchetype);

	// Add empty array for each component in the type.

		for (T3D_ArchetypeID::size_type i = 0u; i < ArchetypeID.size(); i++)
		{
			NewArchetype->ComponentData.push_back(new uint8[0]);
			NewArchetype->ComponentDataSize.push_back(0);
		}

		return NewArchetype;

		// To do...
	}

}