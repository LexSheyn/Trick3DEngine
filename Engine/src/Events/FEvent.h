#pragma once

#include "EEventCategory.h"
#include "EEventType.h"
#include "EventData.h"

#pragma warning( push )
#pragma warning( disable : 26495 ) // Uninitialized variables. Unions does not allow default initialization.

namespace t3d
{
	class FEvent
	{
	public:

	// Constructorss:

	//	FEvent    (EEventType Type)                                           : Type (Type)                                            {}
		FEvent    (EEventType Type, FFramebufferSizeData FrameBufferSizeData) : Type (Type), FramebufferSizeData (FrameBufferSizeData) {}
		FEvent    (EEventType Type, FKeyData             KeyData)             : Type (Type), KeyData             (KeyData)             {}
		FEvent    (EEventType Type, FCharData            CharData)            : Type (Type), CharData            (CharData)            {}
		FEvent    (EEventType Type, FCharModsData        CharModsData)        : Type (Type), CharModsData        (CharModsData)        {}
		FEvent    (EEventType Type, FMouseButtonData     MouseButtonData)     : Type (Type), MouseButtonData     (MouseButtonData)     {}
		FEvent    (EEventType Type, FCursorPositionData  CursorPositionData)  : Type (Type), CursorPositionData  (CursorPositionData)  {}
		FEvent    (EEventType Type, FCursorEnterData     CursorEnterData)     : Type (Type), CursorEnterData     (CursorEnterData)     {}
		FEvent    (EEventType Type, FScrollData          ScrollData)          : Type (Type), ScrollData          (ScrollData)          {}
		FEvent    (EEventType Type, FDropData            DropData)            : Type (Type), DropData            (DropData)            {}

		T3D_NO_COPY(FEvent);
		T3D_DEFAULT_MOVE(FEvent);

	// Functions:

		T3D_INLINE void Handle () { Handled = true; }

	// Accessors:

		T3D_INLINE const EEventCategory& GetCategory    () const { return Category; }
		T3D_INLINE const EEventType&     GetType        () const { return Type; }
		T3D_INLINE const bool8&          IsHandled      () const { return Handled; }

	// Public Variables:

		union
		{
			FFramebufferSizeData FramebufferSizeData;
			FKeyData             KeyData;            
			FCharData            CharData;           
			FCharModsData        CharModsData;       
			FMouseButtonData     MouseButtonData;    
			FCursorPositionData  CursorPositionData; 
			FCursorEnterData     CursorEnterData;    
			FScrollData          ScrollData;         
			FDropData            DropData;           
		};

	private:

	// Variables:

		EEventCategory Category {}; // Temporary unused.
		EEventType     Type;

		bool8 Handled = false;
	};
}

#pragma warning( pop )