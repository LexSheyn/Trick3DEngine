#include "../PrecompiledHeaders/t3dpch.h"
#include "SEventSystem.h"

namespace t3d
{
// Functions:

	void SEventSystem::PushEvent(const FEvent& Event)
	{
		EventQueue.push_back(Event);
	}

	void SEventSystem::ProcessEvents()
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

		//	LOG_TRACE("Listener[" + std::to_string(Entry->second->GetID()) + "] recieved event of type: " + std::to_string(Event->GetType()));
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
			LOG_ERROR("Listener[" + std::to_string(Listener->GetID()) + "] is already subscribed for event of type: " + std::to_string(static_cast<uint32>(Type)) + "!");

			return;
		}
		#endif

		ListenerRegistry.emplace(Type, Listener);

	//	LOG_TRACE("Listener[" + std::to_string(Listener->GetID()) + "] subscribed for event of type: " + std::to_string(EventType));
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

	void SEventSystem::UnsubscribeAll(IEventListener* Listener)
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