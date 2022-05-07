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
		FEvent    (EEventType Type, FMousePositionData   MousePositionData)   : Type (Type), MousePositionData   (MousePositionData)   {}
		FEvent    (EEventType Type, FMouseEnterData      MouseEnterData)      : Type (Type), MouseEnterData      (MouseEnterData)      {}
		FEvent    (EEventType Type, FMouseScrollData     MouseScrollData)     : Type (Type), MouseScrollData     (MouseScrollData)     {}
		FEvent    (EEventType Type, FMouseDropPathData   MouseDropPathData)   : Type (Type), MouseDropPathData   (MouseDropPathData)   {}

		T3D_NO_COPY(FEvent);
		T3D_DEFAULT_MOVE(FEvent);

	// Functions:

		void MarkHandled () { b_Handled = true; }

	// Accessors:

		const EEventCategory& GetCategory    () const { return Category; }
		const EEventType&     GetType        () const { return Type; }
		const bool8&          IsHandled      () const { return b_Handled; }

	// Public Variables:

		union
		{
			FFramebufferSizeData FramebufferSizeData;
			FKeyData             KeyData;            
			FCharData            CharData;           
			FCharModsData        CharModsData;       
			FMouseButtonData     MouseButtonData;    
			FMousePositionData   MousePositionData; 
			FMouseEnterData      MouseEnterData;    
			FMouseScrollData     MouseScrollData;         
			FMouseDropPathData   MouseDropPathData;           
		};

	private:

	// Variables:

		EEventCategory Category {}; // Temporary unused.
		EEventType     Type;

		bool8 b_Handled = false;
	};
}

#pragma warning( pop )