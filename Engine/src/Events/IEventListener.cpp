#include "../PCH/t3dpch.h"
#include "IEventListener.h"

namespace t3d
{
// Accessors:

	const uint64& IEventListener::GetId() const
	{
		return Id;
	}


// Protected Constructors and Destructor:

	IEventListener::IEventListener()
	{
		static uint64 NewId = 0;

		Id = NewId++;
	}

	IEventListener::~IEventListener()
	{
	}


// SEventSystem Interface:

	void IEventListener::Subscribe(EEventType Type, IEventListener* Listener)
	{
		SEventSystem::Subscribe(Type, Listener);
	}

	void IEventListener::Unsubscribe(EEventType Type, IEventListener* Listener)
	{
		SEventSystem::Unsubscribe(Type, Listener);
	}

	void IEventListener::UnsubscribeFromAll(IEventListener* Listener)
	{
		SEventSystem::UnsubscribeFromAll(Listener);
	}

	bool8 IEventListener::IsSubscribed(EEventType Type, IEventListener* Listener)
	{
		return SEventSystem::IsSubscribed(Type, Listener);
	}


}