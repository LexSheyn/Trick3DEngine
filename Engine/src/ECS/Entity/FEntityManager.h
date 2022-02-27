#pragma once

#include "FEntity.h"
#include "../Components/IComponent.h"
#include "../Systems/IComponentSystem.h"

namespace t3d
{
	class FEntityManager
	{
	public:

	// Constructors and Destructor:

		FEntityManager();

		FEntityManager(const FEntityManager&) = delete;

		FEntityManager(FEntityManager&&) = delete;

		~FEntityManager();

	// Operators:

		FEntityManager& operator=(const FEntityManager&) = delete;

		FEntityManager& operator=(FEntityManager&&) = delete;

	// Functions:

		void CreateSystems();

		void Update(); // Requires global DeltaTime.

		[[nodiscard]] T3D_EntityID CreateEntity();

		void DestroyEntity(const T3D_EntityID& EntityID);

	private:

	// Variables:

		std::unordered_map<T3D_EntityID, FEntity> Entities;
		
		std::vector<std::vector<IComponent*>>     Components;

		std::vector<IComponentSystem>             Systems;
	};
}