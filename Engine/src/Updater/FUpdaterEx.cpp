#include "../PCH/t3dpch.h"
#include "FUpdaterEx.h"

namespace t3d
{
// Constructors and Destructor:

	FUpdaterEx::FUpdaterEx()
		:
		FixedUpdateDelay(10)
	{
		SystemRecords.reserve(10);
	}

	FUpdaterEx::~FUpdaterEx()
	{
	}


// Functions:

	void FUpdaterEx::Register(ISystem* System)
	{
		SystemRecords.push_back(FSystemRecord(System, &ISystem::OnUpdate, &ISystem::OnFixedUpdate, &ISystem::OnLateUpdate));
	}

	void  FUpdaterEx::Unregister(ISystem* System)
	{
		for (size_t i = 0u; i < SystemRecords.size(); i++)
		{
			if (SystemRecords.at(i).IsEqual(System))
			{
				SystemRecords.erase(SystemRecords.begin() + i);

				return;
			}
		}
	}

	void FUpdaterEx::UnregisterAll()
	{
		SystemRecords.clear();
	}

	bool8 FUpdaterEx::IsRegistered(ISystem* System)
	{
		for (auto& Record : SystemRecords)
		{
			if (Record.IsEqual(System))
			{
				return true;
			}
		}

		return false;
	}

	void FUpdaterEx::Update()
	{
		for (auto& System : SystemRecords)
		{
			System.InvokeUpdate();
		}
	}

	void FUpdaterEx::FixedUpdate()
	{
		for (auto& System : SystemRecords)
		{
			System.InvokeFixedUpdate();
		}
	}

	void FUpdaterEx::LateUpdate()
	{
		for (auto& System : SystemRecords)
		{
			System.InvokeLateUpdate();
		}
	}


// Accessors:

	const int32& FUpdaterEx::GetFixedUpdateDelay()
	{
		return FixedUpdateDelay;
	}


// Modifiers:

	void FUpdaterEx::SetFixedUpdateDelay(int32 Delay)
	{
		FixedUpdateDelay = Delay;
	}


}