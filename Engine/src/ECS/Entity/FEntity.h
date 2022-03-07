#pragma once

#include "../Components/FComponentDescription.h"
#include "../../Templates/TAutoID.h"

namespace t3d
{
	class FEntity
	{
	public:

	// Constructors and Destructor:

		FEntity()
		{
			ComponentDescriptions.reserve(5);
		}

		~FEntity() {}

		T3D_NO_COPY(FEntity);
		T3D_DEFAULT_MOVE(FEntity);

	// Accessors:

		T3D_INLINE const T3D_EntityID& GetID() const { return ID; }

		T3D_INLINE std::vector<FComponentDescription>& GetComponentDescriptions() { return ComponentDescriptions; }

	private:

	// Public Variables:

		const T3D_EntityID ID = TAutoID<T3D_EntityID>::NewID();

		std::vector<FComponentDescription> ComponentDescriptions;
	};
}