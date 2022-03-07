#pragma once

#include "FEntity.h"

namespace t3d
{
	class MEntityManager
	{
	public:

	// Functions:

		[[nodiscard]] static FEntity* CreateEntity();

		static void RemoveEntity(FEntity* Entity);

		static void Reserve(uint64 Amount);

	private:

	// Private Constructors and Destructor:

		MEntityManager() {}

		~MEntityManager() {}

		T3D_NO_COPY(MEntityManager);
		T3D_NO_MOVE(MEntityManager);

	// Variables:

		static std::unordered_map<T3D_EntityID, FEntity> Entities;
	};
}