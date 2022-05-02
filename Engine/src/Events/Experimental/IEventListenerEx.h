#pragma once

#include "SEventSystemEx.h"

namespace t3d
{
	class IEventListenerEx : public SEventSystemEx
	{
	protected:

		static constexpr TEvent<FFramebufferSizeData> &EventFramebufferSize    = SEventSystemEx::EventFramebufferSize;
		static constexpr TEvent<FKeyData>             &EventKey                = SEventSystemEx::EventKey;
		static constexpr TEvent<FKeyData>             &EventKeyPress           = SEventSystemEx::EventKeyPress;
		static constexpr TEvent<FKeyData>             &EventKeyRelease         = SEventSystemEx::EventKeyRelease;
		static constexpr TEvent<FKeyData>             &EventKeyRepeat          = SEventSystemEx::EventKeyRepeat;
		static constexpr TEvent<FCharData>            &EventChar               = SEventSystemEx::EventChar;
		static constexpr TEvent<FCharModsData>        &EventCharMods           = SEventSystemEx::EventCharMods;
		static constexpr TEvent<FMouseButtonData>     &EventMouseButton        = SEventSystemEx::EventMouseButton;
		static constexpr TEvent<FMouseButtonData>     &EventMouseButtonPress   = SEventSystemEx::EventMouseButtonPress;
		static constexpr TEvent<FMouseButtonData>     &EventMouseButtonRelease = SEventSystemEx::EventMouseButtonRelease;
		static constexpr TEvent<FCursorPositionData>  &EventMouseMove          = SEventSystemEx::EventMouseMove;
		static constexpr TEvent<FCursorEnterData>     &EventMouseEnter         = SEventSystemEx::EventMouseEnter;
		static constexpr TEvent<FScrollData>          &EventMouseScroll        = SEventSystemEx::EventMouseScroll;
		static constexpr TEvent<FDropPathData>        &EventMouseDropPath      = SEventSystemEx::EventMouseDropPath;
	};
}