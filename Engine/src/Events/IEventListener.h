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

	// Functions:

		virtual void T3D_CALL OnEvent(const FEvent* const Event) = 0;

	// Accessors:

		const uint32& T3D_CALL GetID() const;

	private:

	// Variables:

		uint32 ID;
	};
}