#include "../PCH/t3dpch.h"
#include "FUpdaterEx.h"

namespace t3d
{
// Constructors and Destructor:

	FUpdaterEx::FUpdaterEx()
		:
		FixedUpdateDelay(10)
	{
		Systems             .reserve(10);
		SystemCallbacks     .reserve(10);
		FixedSystemCallbacks.reserve(10);
		LastSystemCallbacks .reserve(10);
	}

	FUpdaterEx::~FUpdaterEx()
	{
	}


// Functions:

	void FUpdaterEx::Subscribe(ISystem* System)
	{
		Systems             .push_back(System);
		SystemCallbacks     .push_back(FSystemCallback(System, &ISystem::OnUpdate));
		FixedSystemCallbacks.push_back(FSystemCallback(System, &ISystem::OnFixedUpdate));
		LastSystemCallbacks .push_back(FSystemCallback(System, &ISystem::OnLastUpdate));
	}

	void  FUpdaterEx::Unsubscribe(ISystem* System)
	{
		for (size_t i = 0u; i < Systems.size(); i++)
		{
			if (Systems.at(i) == System)
			{
				Systems.at(i) = Systems.back();

				Systems.pop_back();

				break;
			}
		}

		for (size_t i = 0u; i < SystemCallbacks.size(); i++)
		{
			if (SystemCallbacks.at(i).IsEqual(System))
			{
				SystemCallbacks.at(i) = SystemCallbacks.back();

				SystemCallbacks.pop_back();

				break;
			}
		}

		for (size_t i = 0u; i < FixedSystemCallbacks.size(); i++)
		{
			if (FixedSystemCallbacks.at(i).IsEqual(System))
			{
				FixedSystemCallbacks.at(i) = FixedSystemCallbacks.back();

				FixedSystemCallbacks.pop_back();

				break;
			}
		}

		for (size_t i = 0u; i < LastSystemCallbacks.size(); i++)
		{
			if (LastSystemCallbacks.at(i).IsEqual(System))
			{
				LastSystemCallbacks.at(i) = LastSystemCallbacks.back();

				LastSystemCallbacks.pop_back();

				break;
			}
		}
	}

	void FUpdaterEx::UnsubscribeAll()
	{
		Systems             .clear();
		SystemCallbacks     .clear();
		FixedSystemCallbacks.clear();
		LastSystemCallbacks .clear();
	}

	bool8 FUpdaterEx::IsSubscribed(ISystem* System)
	{
		for (auto& SubscribedSystem : Systems)
		{
			if (SubscribedSystem == System)
			{
				return true;
			}
		}

		return false;
	}

	void FUpdaterEx::Update()
	{
		for (auto& SystemCallback : SystemCallbacks)
		{
			SystemCallback.Invoke();
		}
	}

	void FUpdaterEx::FixedUpdate()
	{
		for (auto& FixedSystemCallback : FixedSystemCallbacks)
		{
			FixedSystemCallback.Invoke();
		}
	}

	void FUpdaterEx::LastUpdate()
	{
		for (auto& LastSystemCallback : LastSystemCallbacks)
		{
			LastSystemCallback.Invoke();
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