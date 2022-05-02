#include "../../PCH/t3dpch.h"
#include "SEventSystemEx.h"

namespace t3d
{
	TEvent<FFramebufferSizeData> SEventSystemEx::EventFramebufferSize;
	TEvent<FKeyData>             SEventSystemEx::EventKey;
	TEvent<FKeyData>             SEventSystemEx::EventKeyPress;
	TEvent<FKeyData>             SEventSystemEx::EventKeyRelease;
	TEvent<FKeyData>             SEventSystemEx::EventKeyRepeat;
	TEvent<FCharData>            SEventSystemEx::EventChar;
	TEvent<FCharModsData>        SEventSystemEx::EventCharMods;
	TEvent<FMouseButtonData>     SEventSystemEx::EventMouseButton;
	TEvent<FMouseButtonData>     SEventSystemEx::EventMouseButtonPress;
	TEvent<FMouseButtonData>     SEventSystemEx::EventMouseButtonRelease;
	TEvent<FCursorPositionData>  SEventSystemEx::EventMouseMove;
	TEvent<FCursorEnterData>     SEventSystemEx::EventMouseEnter;
	TEvent<FScrollData>          SEventSystemEx::EventMouseScroll;
	TEvent<FDropPathData>        SEventSystemEx::EventMouseDropPath;
}