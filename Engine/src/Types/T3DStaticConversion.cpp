#include "../PCH/t3dpch.h"
#include "T3DStaticConversion.h"

namespace t3d
{
// UInt64:

	uint64 UInt64(const ESound& Value)
	{
		return static_cast<uint64>(Value);
	}

	uint64 UInt64(const ESoundGroup& Value)
	{
		return static_cast<uint64>(Value);
	}

}