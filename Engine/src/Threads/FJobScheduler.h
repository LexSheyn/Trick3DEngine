#pragma once

#include "EThread.h"
#include "../Templates/TArray.h"

namespace t3d
{
	class FJobScheduler
	{
	public:

	// Constructors and Destructor:

		 FJobScheduler();
		~FJobScheduler();

	// Functions:

	//	template<typename T>
	//	void Schedule(EThread Thread, FObject Instance, bool8(*Callback) (const T&))
	//	{
	//
	//	}

	// Accessors:

		std::thread& GetThread(EThread Name);

	// Threads:

		TArray<std::thread, 4> Threads;
	};
}