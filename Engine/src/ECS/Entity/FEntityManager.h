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

		FEntityManager() {}

		FEntityManager(const FEntityManager&) = delete;

		FEntityManager(FEntityManager&&) = delete;

		~FEntityManager() {}

	// Operators:

		FEntityManager& operator=(const FEntityManager&) = delete;

		FEntityManager& operator=(FEntityManager&&) = delete;

	// Functions:

		void AddComponent()
		{

		}

	private:

	// Variables:

		static std::unordered_map<EComponentType, std::unordered_map<T3D_EntityID, IComponent>> Components;

		static std::unordered_map<EComponentType, IComponentSystem> Systems;
	};
}