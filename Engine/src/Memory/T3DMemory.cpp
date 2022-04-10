#include "../PCH/t3dpch.h"
#include "T3DMemory.h"

#pragma warning( push )
#pragma warning( disable : 4996 ) // Function unsafe.

namespace t3d
{
// Functions:

	void* MemoryCopy(void* Destination, uint64 DestinationSize, void* Source)
	{
		return std::memcpy(Destination, Source, DestinationSize);
	}


}

#pragma warning( pop )