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
	TEvent<FMousePositionData>   SEventSystemEx::EventMouseMove;
	TEvent<FMouseEnterData>      SEventSystemEx::EventMouseEnter;
	TEvent<FMouseScrollData>     SEventSystemEx::EventMouseScroll;
	TEvent<FMouseDropPathData>   SEventSystemEx::EventMouseDropPath;
}