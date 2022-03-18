#pragma once

#include "../ECS/Systems/Base/ISystem.h"

namespace t3d
{
	class FUpdater
	{
	public:

	// Functions:

		static void Register      (uint64 Group, ISystem* System);
		static void Unregister    (uint64 Group, ISystem* System);
		static void Update        (uint64 Group);

	private:

	// Private Constructors and Destructor:

		 FUpdater() {}
		~FUpdater() {}

		T3D_NO_COPY(FUpdater);
		T3D_NO_MOVE(FUpdater);

	// Variables:

		static constexpr uint64 GroupsMax = 4;

		static TArray<std::vector<ISystem*>, GroupsMax> SystemGroups;
	};
}