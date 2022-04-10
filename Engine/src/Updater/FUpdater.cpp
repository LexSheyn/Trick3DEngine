#include "../PCH/t3dpch.h"
#include "FUpdater.h"

namespace t3d
{
// Functions:

	void FUpdater::Register(uint64 Group, ISystem* System)
	{
		SystemGroups[Group].push_back(System);
	}

	void FUpdater::Unregister(uint64 Group, ISystem* System)
	{
		for (uint64 i = 0u; i < SystemGroups[Group].size(); i++)
		{
			if (SystemGroups[Group][i] == System)
			{
				SystemGroups[Group][i] = SystemGroups[Group].back();

				SystemGroups[Group].pop_back();

				return;
			}
		}
	}

	void FUpdater::UnregisterAll()
	{
		for (uint64 i = 0u; i < SystemGroups.Size(); i++)
		{
			SystemGroups[i].clear();
		}
	}

	void FUpdater::Update(uint64 Group)
	{
		for (auto& System : SystemGroups[Group])
		{
			System->Update();
		}
	}


// Static Variables:

	TArray<std::vector<ISystem*>, FUpdater::GroupsMax> FUpdater::SystemGroups;

}