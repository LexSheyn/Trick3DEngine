#pragma once

#include "FEvent.h"

namespace t3d
{
	class IEventListener
	{
	public:

	// Constructors and Destructor:

		         IEventListener();
		virtual ~IEventListener();

	// Interface:

		virtual void OnEvent (const FEvent* const Event) = 0;

	// Accessors:

		const uint32& GetID () const;

	private:

	// Variables:

		uint32 ID;
	};
}