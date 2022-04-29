#pragma once

#include "EventData.h"

namespace t3d
{
//	typedef void (*FEventCallbackFramebufferSize) (const FFramebufferSizeData&);
//	typedef void (*FEventCallbackKey)             (const FKeyData&);
//	typedef void (*FEventCallbackChar)            (const FCharData&);
//	typedef void (*FEventCallbackCharMods)        (const FCharModsData&);
//	typedef void (*FEventCallbackMouseButton)     (const FMouseButtonData&);
//	typedef void (*FEventCallbackMousePosition)   (const FCursorPositionData&);
//	typedef void (*FEventCallbackMouseEnter)      (const FCursorEnterData&);
//	typedef void (*FEventCallbackMouseScroll)     (const FScrollData&);
//	typedef void (*FEventCallbackMouseDropPath)   (const FDropData&);

	using FEventCallbackFramebufferSize = void (*) (const FFramebufferSizeData&);
	using FEventCallbackKey             = void (*) (const FKeyData&);
	using FEventCallbackChar            = void (*) (const FCharData&);
	using FEventCallbackCharMods        = void (*) (const FCharModsData&);
	using FEventCallbackMouseButton     = void (*) (const FMouseButtonData&);
	using FEventCallbackMousePosition   = void (*) (const FCursorPositionData&);
	using FEventCallbackMouseEnter      = void (*) (const FCursorEnterData&);
	using FEventCallbackMouseScroll     = void (*) (const FScrollData&);
	using FEventCallbackMouseDropPath   = void (*) (const FDropData&);
}