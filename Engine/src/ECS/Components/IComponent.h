#pragma once

#include "EComponentType.h"
#include "../Entity/ECSTypes.h"

namespace t3d
{
	class IComponent
	{
	public:

	// Constructors and Destructor:

		IComponent(EComponentType Type) :Type(Type) {}

		virtual ~IComponent() {}

	// Accessors

		T3D_INLINE const EComponentType& GetType() const { return Type; }

	private:

		EComponentType Type;
	};
}