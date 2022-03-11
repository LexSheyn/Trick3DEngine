#include "../PrecompiledHeaders/t3dpch.h"
#include "IEventListener.h"

namespace t3d
{
// Constructors and Destructor:

	IEventListener::IEventListener()
	{
		static int32 ID = 0u;

		this->ID = ID++;
	}

	IEventListener::~IEventListener()
	{
	}


// Accessors:

	const uint32& IEventListener::GetID() const
	{
		return ID;
	}

}