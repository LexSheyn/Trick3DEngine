#include "../PCH/t3dpch.h"
#include "FJobScheduler.h"

namespace t3d
{
// Constructors and Destructor:

	FJobScheduler::FJobScheduler()
	{
	}

	FJobScheduler::~FJobScheduler()
	{
	}


// Accessors:

	std::thread& FJobScheduler::GetThread(EThread Name)
	{
		return Threads[Name];
	}

}