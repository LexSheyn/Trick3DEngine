#pragma once

#include "FEvent.h"
#include "IEventListener.h"

namespace t3d
{
	class SEventSystem
	{
	private:

	// Constructors and Destructor:

		 SEventSystem () = delete;
		~SEventSystem () = delete;

	// Functions:

		static void  T3D_CALL PushEvent                (FEvent&& Event);
		static void  T3D_CALL PollEvents               ();
		static void  T3D_CALL Dispatch                 (FEvent* Event);
		static void  T3D_CALL Subscribe                (EEventType Type, IEventListener* Listener);
		static void  T3D_CALL Unsubscribe              (EEventType Type, IEventListener* Listener);
		static void  T3D_CALL UnsubscribeFromAll       (IEventListener* Listener);
		static bool8 T3D_CALL IsSubscribed             (EEventType Type, IEventListener* Listener);
		static void  T3D_CALL ClearEventQueue          ();
		static void  T3D_CALL ClearListenerRegistry    ();

	// Variables:

		static std::list<FEvent> EventQueue;

		static std::multimap<EEventType, IEventListener*> ListenerRegistry;

	// Friends:

		friend class IEventListener;
		friend class IEventSender;
		friend class FApplication;
	};
}