#pragma once

#pragma warning( push )
#pragma warning( disable : 26495 ) // Uninitialized variables.

#include "../Types/T3DTypes.h"
#include "../Memory/T3DMemory.h"
#include "../Time/FTimeStamp.h"

namespace t3d
{
// Window:

	struct FFramebufferSizeData { int32 Width; int32 Height; };


// Keyboard:

	struct FKeyData      { int32 Key; int32 ScanCode; int32 Action; int32 Mods; };

	// Character represented in UTF-32 bit format.
	// To retrieve ASCII 8 bit character use static_cast<char8>.
	struct FCharData     { uint32 Codepoint; };

	// Character represented in UTF-32 bit format.
	// To retrieve ASCII 8 bit character use static_cast<char8>.
	struct FCharModsData { uint32 Codepoint; int32 Mods; };


// Mouse:

	struct FMouseButtonData    { int32 Button; int32 Action; int32 Mods; float32 X; float32 Y; };

	struct FMousePositionData  { float32 X; float32 Y; };
							   
	struct FMouseEnterData     { int32 Entered; };

	struct FMouseScrollData    { float32 OffsetX; float32 OffsetY; };

	struct FMouseDropPathData  { int32 PathCount; const char8* Paths; };

// Logger:

	class FLogData
	{
	public:

		FLogData(FTimeStamp TimeStamp, const char8* FunctionName, const char8* Message)
		{
			MemoryCopy(this->TimeStamp   ,   9, reinterpret_cast<void*>(TimeStamp.Get()));
			MemoryCopy(this->FunctionName, 128, reinterpret_cast<void*>(const_cast<char8*>(FunctionName)));
			MemoryCopy(this->Message     , 128, reinterpret_cast<void*>(const_cast<char8*>(Message)));
		}

		char8* GetTimeStamp()
		{
			return TimeStamp;
		}

		char8* GetFunctionName()
		{
			return FunctionName;
		}

		char8* GetMessage()
		{
			return Message;
		}

	private:

		char8 TimeStamp    [9]; // HH:MM:SS, 9 chars: 8 for numbers + 1 for '\0' (null terminator).
		char8 FunctionName [128];
		char8 Message      [128];
	};

// Application:

	struct FApplicationData { int8 Dummy; };
	struct FWindowData      { int8 Dummy; };

}
#pragma warning( pop )