#pragma once

#include "FEvent.h"
#include "IEventListener.h"

namespace t3d
{
	class SEventSystem
	{
	public:

	// Functions:

		static void  PushEvent                (const FEvent& Event);
		static void  ProcessEvents            ();
		static void  Dispatch                 (FEvent* Event);
		static void  Subscribe                (EEventType Type, IEventListener* Listener);
		static void  Unsubscribe              (EEventType Type, IEventListener* Listener);
		static void  UnsubscribeFromAll       (IEventListener* Listener);
		static bool8 IsSubscribed             (EEventType Type, IEventListener* Listener);
		static void  ClearEventQueue          ();
		static void  ClearListenerRegistry    ();

		// Clear all data function here!

	private:

	// Private Constructors and Destructor:

		SEventSystem  () {}
		~SEventSystem () {}

		T3D_NO_COPY(SEventSystem);
		T3D_NO_MOVE(SEventSystem);

	// Variables:

		static std::list<FEvent> EventQueue;

		static std::multimap<EEventType, IEventListener*> ListenerRegistry;
	};
}