#include "../PCH/t3dpch.h"
#include "IEventListener.h"

namespace t3d
{
// Accessors:

	const uint64& IEventListener::GetId() const
	{
		return Id;
	}


// Protected Constructors and Destructor:

	IEventListener::IEventListener()
	{
		static uint64 NewId = 0;

		Id = NewId++;
	}

	IEventListener::~IEventListener()
	{
	}


}