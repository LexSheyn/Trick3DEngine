#pragma once

#pragma warning( push )
#pragma warning( disable : 26495 ) // Uninitialized variables.

#include "EColorFormat.h"

namespace t3d
{
	struct FImagePNG
	{
		int32 Width;
		int32 Height;

		int32 Channels;

		uint8* Pixels;

		EColorFormat ColorFormat = EColorFormat::RGBA;
	};
}
#pragma warning( pop )