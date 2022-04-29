#pragma once

#include "TEventDispatcher.h"
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

	// TEST:

		static TEventDispatcher<FEventCallbackFramebufferSize, FFramebufferSizeData> EventFramebufferSize;
		static TEventDispatcher<FEventCallbackKey            , FKeyData>             EventKey;
		static TEventDispatcher<FEventCallbackChar           , FCharData>            EventChar;
		static TEventDispatcher<FEventCallbackCharMods       , FCharModsData>        EventCharMods;
		static TEventDispatcher<FEventCallbackMouseButton    , FMouseButtonData>     EventMouseButton;
		static TEventDispatcher<FEventCallbackMousePosition  , FCursorPositionData>  EventMouseMove;
		static TEventDispatcher<FEventCallbackMouseEnter     , FCursorEnterData>     EventMouseEnter;
		static TEventDispatcher<FEventCallbackMouseScroll    , FScrollData>          EventMouseScroll;
		static TEventDispatcher<FEventCallbackMouseDropPath  , FDropData>            EventMouseDropPath;

	private:

	// Variables:

		static std::list<FEvent> EventQueue;

		static std::multimap<EEventType, IEventListener*> ListenerRegistry;
	};
}