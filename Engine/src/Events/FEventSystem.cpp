#include "../PrecompiledHeaders/t3dpch.h"
#include "FEventSystem.h"

namespace t3d
{
// Functions:

	void FEventSystem::PushEvent(const FEvent& Event)
	{
		EventQueue.push_back(Event);
	}

	void FEventSystem::ProcessEvents()
	{
		while (EventQueue.size() > 0u)
		{
			Dispatch(&EventQueue.front());

			EventQueue.pop_front();
		}
	}

	void FEventSystem::Dispatch(FEvent* Event)
	{
		std::pair Range = ListenerRegistry.equal_range(Event->GetType());

		for (auto& Entry = Range.first; Entry != Range.second; Entry++)
		{
			Entry->second->OnEvent(Event);

		//	LOG_TRACE("Listener[" + std::to_string(Entry->second->GetID()) + "] recieved event of type: " + std::to_string(Event->GetType()));
		}
	}

	void FEventSystem::Subscribe(EEventType Type, IEventListener* Listener)
	{		
		#if _DEBUG
		if (!Listener)
		{
			LOG_ERROR("Passed nullptr to the function!");

			return;
		}
		else if (IsSubscribed(Type, Listener))
		{
			LOG_ERROR("Listener[" + std::to_string(Listener->GetID()) + "] is already subscribed for event of type: " + std::to_string(static_cast<uint32>(Type)) + "!");

			return;
		}
		#endif

		ListenerRegistry.emplace(Type, Listener);

	//	LOG_TRACE("Listener[" + std::to_string(Listener->GetID()) + "] subscribed for event of type: " + std::to_string(EventType));
	}

	void FEventSystem::Unsubscribe(EEventType Type, IEventListener* Listener)
	{
		#if _DEBUG
		if (!Listener)
		{
			LOG_ERROR("Passed nullptr to the function!");

			return;
		}
		else if (!IsSubscribed(Type, Listener))
		{
			LOG_ERROR("Listener[" + std::to_string(Listener->GetID()) + "] is not subscribed for event of type: " + std::to_string(static_cast<uint32>(Type)) + "!");

			return;
		}
		#endif

		uint32 ID = Listener->GetID();

		std::pair Range = ListenerRegistry.equal_range(Type);

		for (auto& Entry = Range.first; Entry != Range.second; Entry++)
		{
			if (Entry->second == Listener)
			{
				Entry = ListenerRegistry.erase(Entry);

			//	LOG_TRACE("Listener[" + std::to_string(ID) + "] unsubscribed from event of type: " + std::to_string(EventType));

				return;
			}
		}
	}

	void FEventSystem::UnsubscribeAll(IEventListener* Listener)
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

	bool8 FEventSystem::IsSubscribed(EEventType Type, IEventListener* Listener)
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

	void FEventSystem::ClearEventQueue()
	{
		EventQueue.clear();
	}

	void FEventSystem::ClearListenerRegistry()
	{
		ListenerRegistry.clear();
	}


// Static Variables:

	std::list<FEvent> FEventSystem::EventQueue;

	std::multimap<EEventType, IEventListener*> FEventSystem::ListenerRegistry;

}