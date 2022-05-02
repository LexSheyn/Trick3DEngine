#pragma once

//#include "FEvent.h"

namespace t3d
{
	class IEventListener
	{
	public:

	// Interface:

		virtual void OnEvent    (const class FEvent* const Event) = 0;

	// Accessors:

		const uint64& GetId() const;

	protected:

	// Protected Constructors and Destructor:

		         IEventListener();
		virtual ~IEventListener();

	// SEventSystem Interface:

		static void  T3D_CALL Subscribe             (EEventType Type, IEventListener* Listener);
		static void  T3D_CALL Unsubscribe           (EEventType Type, IEventListener* Listener);
		static void  T3D_CALL UnsubscribeFromAll    (IEventListener* Listener);
		static bool8 T3D_CALL IsSubscribed          (EEventType Type, IEventListener* Listener);

	private:

	// Variables:

		uint64 Id;
	};
}