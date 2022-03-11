#pragma once

#include "../Components/FComponentDescription.h"
#include "../../Templates/TAutoID.h"

namespace t3d
{
	class FEntity
	{
	public:

	// Constructors and Destructor:

		FEntity();

		~FEntity();

		T3D_NO_COPY(FEntity);
		T3D_DEFAULT_MOVE(FEntity);

	// Accessors:

		const T3D_EntityID& GetID()    const;

		const uint64&       GetIndex() const;

		std::vector<FComponentDescription>& GetComponentDescriptions();

	// Modifiers:

		void SetIndex(uint64 Value);

	private:

	// Variables:

		const T3D_EntityID ID = TAutoID<T3D_EntityID>::NewID();

		// Index in the Entities vector.
		uint64 Index;

		std::vector<FComponentDescription> ComponentDescriptions;
	};
}