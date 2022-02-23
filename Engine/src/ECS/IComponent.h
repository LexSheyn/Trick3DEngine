#pragma once

#include "TTypeIDGenerator.h"

namespace t3d
{
	class IComponent
	{
	public:

	// Constructors and Destructor:

		IComponent() {}

		virtual ~IComponent() {}

	// Interface Functions:

		virtual void ConstructData(uint8* Data)                  const = 0;

		virtual void MoveData(uint8* Source, uint8* Destination) const = 0;

		virtual void DestroyData(uint8* Data)                    const = 0;
		
	// Interface Accessors:

		virtual size_t GetSize() const = 0;
	};
}