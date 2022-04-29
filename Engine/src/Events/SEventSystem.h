#pragma once

#include "TEvent.h"
#include "IEventListener.h"

namespace t3d
{
	class SEventSystem
	{
	public:

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

		// Clear all data function here!

	private:

	// Variables:

		static std::list<FEvent> EventQueue;

		static std::multimap<EEventType, IEventListener*> ListenerRegistry;

	public:

	// Events and Delegates:

		static TEvent<FFramebufferSizeData> EventFramebufferSize;
		static TEvent<FKeyData>             EventKey;
		static TEvent<FCharData>            EventChar;
		static TEvent<FCharModsData>        EventCharMods;
		static TEvent<FMouseButtonData>     EventMouseButton;
		static TEvent<FCursorPositionData>  EventMouseMove;
		static TEvent<FCursorEnterData>     EventMouseEnter;
		static TEvent<FScrollData>          EventMouseScroll;
		static TEvent<FDropPathData>        EventMouseDropPath;
	};
}