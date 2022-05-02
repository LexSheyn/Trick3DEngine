#include "../PCH/t3dpch.h"
#include "SEventSystem.h"

namespace t3d
{
// Functions:

	void SEventSystem::PushEvent(FEvent&& Event)
	{
		EventQueue.push_back(std::move(Event));
	}

	void SEventSystem::PollEvents()
	{
		while (EventQueue.size() > 0u)
		{
			Dispatch(&EventQueue.front());

			EventQueue.pop_front();
		}
	}

	void SEventSystem::Dispatch(FEvent* Event)
	{
		std::pair Range = ListenerRegistry.equal_range(Event->GetType());

		for (auto& Entry = Range.first; Entry != Range.second; Entry++)
		{
			Entry->second->OnEvent(Event);

			if (Event->IsHandled())
			{
				return;
			}
		}
	}

	void SEventSystem::Subscribe(EEventType Type, IEventListener* Listener)
	{		
	#if _DEBUG
		if (!Listener)
		{
			LOG_ERROR("Passed nullptr to the function!");

			return;
		}
		else if (IsSubscribed(Type, Listener))
		{
			LOG_ERROR("Listener[" + std::to_string(Listener->GetId()) + "] is already subscribed for event of type: " + std::to_string(static_cast<uint32>(Type)) + "!");

			return;
		}
	#endif

		ListenerRegistry.emplace(Type, Listener);
	}

	void SEventSystem::Unsubscribe(EEventType Type, IEventListener* Listener)
	{
	#if _DEBUG
		if (!Listener)
		{
			LOG_ERROR("Passed nullptr to the function!");

			return;
		}
		else if (!IsSubscribed(Type, Listener))
		{
			LOG_ERROR("Listener[" + std::to_string(Listener->GetId()) + "] is not subscribed for event of type: " + std::to_string(static_cast<uint32>(Type)) + "!");

			return;
		}
	#endif

		std::pair Range = ListenerRegistry.equal_range(Type);

		for (auto& Entry = Range.first; Entry != Range.second; Entry++)
		{
			if (Entry->second == Listener)
			{
				Entry = ListenerRegistry.erase(Entry);

				return;
			}
		}
	}

	void SEventSystem::UnsubscribeFromAll(IEventListener* Listener)
	{
		std::multimap<EEventType, IEventListener*>::iterator Entry = ListenerRegistry.begin();

		while (Entry != ListenerRegistry.end())
		{
			if (Entry->second == Listener)
			{
				Entry = ListenerRegistry.erase(Entry);
			}
			else
			{
				Entry++;
			}
		}
	}

	bool8 SEventSystem::IsSubscribed(EEventType Type, IEventListener* Listener)
	{
		std::pair Range = ListenerRegistry.equal_range(Type);

		for (auto& Entry = Range.first; Entry != Range.second; Entry++)
		{
			if (Entry->second == Listener)
			{
				return true;
			}
		}

		return false;
	}

	void SEventSystem::ClearEventQueue()
	{
		EventQueue.clear();
	}

	void SEventSystem::ClearListenerRegistry()
	{
		ListenerRegistry.clear();
	}


// Static Variables:

	std::list<FEvent> SEventSystem::EventQueue;

	std::multimap<EEventType, IEventListener*> SEventSystem::ListenerRegistry;

}