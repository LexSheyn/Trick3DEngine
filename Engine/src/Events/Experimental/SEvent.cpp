#include "../../PCH/t3dpch.h"
#include "SEvent.h"

namespace t3d
{
	TEvent<FFramebufferSizeData> SEvent::FramebufferSize;
	TEvent<FKeyData>             SEvent::Key;
	TEvent<FKeyData>             SEvent::KeyPress;
	TEvent<FKeyData>             SEvent::KeyRelease;
	TEvent<FKeyData>             SEvent::KeyRepeat;
	TEvent<FCharData>            SEvent::Char;
	TEvent<FCharModsData>        SEvent::CharMods;
	TEvent<FMouseButtonData>     SEvent::MouseButton;
	TEvent<FMouseButtonData>     SEvent::MouseButtonPress;
	TEvent<FMouseButtonData>     SEvent::MouseButtonRelease;
	TEvent<FMousePositionData>   SEvent::MouseMove;
	TEvent<FMouseEnterData>      SEvent::MouseEnter;
	TEvent<FMouseScrollData>     SEvent::MouseScroll;
	TEvent<FMouseDropPathData>   SEvent::MouseDropPath;
	TEvent<FLogData>             SEvent::Trace;
	TEvent<FLogData>             SEvent::Warning;
	TEvent<FLogData>             SEvent::Error;
	TEvent<FApplicationData>     SEvent::ApplicationClose;
	TEvent<FWindowData>          SEvent::WindowClose;
}