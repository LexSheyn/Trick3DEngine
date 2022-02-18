#pragma once

#pragma warning( push )
#pragma warning( disable : 26495 ) // Uninitialized variables. Default initialization is not allowed for anonymous union.

#include "EEventCategory.h"
#include "EEventType.h"
#include "EventData.h"

namespace t3d
{
	class FEvent
	{
	public:

	// Constructors and Destructor:

		FEvent(EEventType Type, FFrameBufferSizeData FrameBufferSizeData) : Type(Type), FrameBufferSizeData(FrameBufferSizeData) {}
		FEvent(EEventType Type, FKeyData KeyData)                         : Type(Type), KeyData(KeyData)                         {}
		FEvent(EEventType Type, FCharData CharData)                       : Type(Type), CharData(CharData)                       {}
		FEvent(EEventType Type, FCharModsData CharModsData)               : Type(Type), CharModsData(CharModsData)               {}
		FEvent(EEventType Type, FMouseButtonData MouseButtonData)         : Type(Type), MouseButtonData(MouseButtonData)         {}
		FEvent(EEventType Type, FCursorPositionData CursorPositionData)   : Type(Type), CursorPositionData(CursorPositionData)   {}
		FEvent(EEventType Type, FCursorEnterData CursorEnterData)         : Type(Type), CursorEnterData(CursorEnterData)         {}
		FEvent(EEventType Type, FScrollData ScrollData)                   : Type(Type), ScrollData(ScrollData)                   {}
		FEvent(EEventType Type, FDropData DropData)                       : Type(Type), DropData(DropData)                       {}

		~FEvent() {};

	// Accessors:

		T3D_INLINE const EEventCategory& GetCategory() const { return Category; }

		T3D_INLINE const EEventType&     GetType()     const { return Type; }

	// Public Variables:

		union
		{
			struct { FFrameBufferSizeData FrameBufferSizeData; };
			struct { FKeyData             KeyData;             };
			struct { FCharData            CharData;            };
			struct { FCharModsData        CharModsData;        };
			struct { FMouseButtonData     MouseButtonData;     };
			struct { FCursorPositionData  CursorPositionData;  };
			struct { FCursorEnterData     CursorEnterData;     };
			struct { FScrollData          ScrollData;          };
			struct { FDropData            DropData;            };
		};

	private:

	// Variables:

		EEventCategory Category;

		EEventType     Type;
	};
}
#pragma warning( pop )