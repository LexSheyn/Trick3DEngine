#pragma once

#pragma warning( push )
#pragma warning( disable : 26495 ) // Uninitialized variables.

#include "../Types/T3DTypes.h"

namespace t3d
{
// Window:

	struct FFrameBufferSizeData { int32 Width; int32 Height; };


// Keyboard:

	struct FKeyData      { int32 Key; int32 ScanCode; int32 Action; int32 Mods; };

	// Character represented in UTF-32 bit format.
	// To retrieve ASCII 8 bit character use static_cast<char8>.
	struct FCharData     { uint32 Codepoint; };

	// Character represented in UTF-32 bit format.
	// To retrieve ASCII 8 bit character use static_cast<char8>.
	struct FCharModsData { uint32 Codepoint; int32  Mods; };


// Mouse

	struct FMouseButtonData    { int32 Button; int32 Action; int32 Mods; };

	struct FCursorPositionData { float64 X; float64 Y; };

	struct FCursorEnterData    { int32 Entered; };

	struct FScrollData         { float64 OffsetX; float64 OffsetY; };

	struct FDropData           { int32 PathCount; const char8* Paths; };

}
#pragma warning( pop )