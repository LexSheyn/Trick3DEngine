#pragma once

#include "TEvent.h"
#include "../EventData.h"

namespace t3d
{
	class SEvent
	{
	public:

		 SEvent    () = delete;
		~SEvent    () = delete;

		static TEvent<FFramebufferSizeData> FramebufferSize;
		static TEvent<FKeyData>             Key;
		static TEvent<FKeyData>             KeyPress;
		static TEvent<FKeyData>             KeyRelease;
		static TEvent<FKeyData>             KeyRepeat;
		static TEvent<FCharData>            Char;
		static TEvent<FCharModsData>        CharMods;
		static TEvent<FMouseButtonData>     MouseButton;
		static TEvent<FMouseButtonData>     MouseButtonPress;
		static TEvent<FMouseButtonData>     MouseButtonRelease;
		static TEvent<FMousePositionData>   MouseMove;
		static TEvent<FMouseEnterData>      MouseEnter;
		static TEvent<FMouseScrollData>     MouseScroll;
		static TEvent<FMouseDropPathData>   MouseDropPath;
		static TEvent<FLogData>             Trace;
		static TEvent<FLogData>             Warning;
		static TEvent<FLogData>             Error;
		static TEvent<FApplicationData>     ApplicationClose;
		static TEvent<FWindowData>          WindowClose;
	};
}