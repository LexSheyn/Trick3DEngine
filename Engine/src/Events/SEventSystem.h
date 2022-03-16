#pragma once

#include "IEventListener.h"

namespace t3d
{
	class SEventSystem
	{
	public:

	// Functions:

		static void  T3D_CALL PushEvent                (const FEvent& Event);
		static void  T3D_CALL ProcessEvents            ();
		static void  T3D_CALL Dispatch                 (FEvent* Event);
		static void  T3D_CALL Subscribe                (EEventType Type, IEventListener* Listener);
		static void  T3D_CALL Unsubscribe              (EEventType Type, IEventListener* Listener);
		static void  T3D_CALL UnsubscribeFromAll       (IEventListener* Listener);
		static bool8 T3D_CALL IsSubscribed             (EEventType Type, IEventListener* Listener);
		static void  T3D_CALL ClearEventQueue          ();
		static void  T3D_CALL ClearListenerRegistry    ();

		// Clear all data function here!

	private:

	// Private Constructors and Destructor:

		 SEventSystem () {}
		~SEventSystem () {}

		T3D_NO_COPY(SEventSystem);
		T3D_NO_MOVE(SEventSystem);

	// Variables:

		static std::list<FEvent> EventQueue;

		static std::multimap<EEventType, IEventListener*> ListenerRegistry;
	};
}