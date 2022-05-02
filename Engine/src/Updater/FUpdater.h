#pragma once

#include "../ECS/Systems/ISystem.h"

namespace t3d
{
	class FUpdater
	{
	public:

	// Constructors and Destructor:

		 FUpdater    () {}
		~FUpdater    () {}

		T3D_NO_COPY(FUpdater);
		T3D_NO_MOVE(FUpdater);

	// Functions:

		void Register          (uint64 Group, ISystem* System);
		void Unregister        (uint64 Group, ISystem* System);
		void UnregisterAll     ();
		void Update            (uint64 Group);

	private:

	// Variables:

		static constexpr uint64 GroupsMax = 4;

		TArray<std::vector<ISystem*>, GroupsMax> SystemGroups;
	};
}