#pragma once

#include "TEvent.h"
#include "../EventData.h"

namespace t3d
{
	class SEventSystemEx
	{
	protected:

		static TEvent<FFramebufferSizeData> EventFramebufferSize;
		static TEvent<FKeyData>             EventKey;
		static TEvent<FKeyData>             EventKeyPress;
		static TEvent<FKeyData>             EventKeyRelease;
		static TEvent<FKeyData>             EventKeyRepeat;
		static TEvent<FCharData>            EventChar;
		static TEvent<FCharModsData>        EventCharMods;
		static TEvent<FMouseButtonData>     EventMouseButton;
		static TEvent<FMouseButtonData>     EventMouseButtonPress;
		static TEvent<FMouseButtonData>     EventMouseButtonRelease;
		static TEvent<FCursorPositionData>  EventMouseMove;
		static TEvent<FCursorEnterData>     EventMouseEnter;
		static TEvent<FScrollData>          EventMouseScroll;
		static TEvent<FDropPathData>        EventMouseDropPath;
	};
}