#pragma once

#include "../Components/FComponentDescription.h"

namespace t3d
{
	class FEntity
	{
	public:

	// Constructors and Destructor:

		FEntity(T3D_EntityID Value);

		~FEntity();

		T3D_NO_COPY(FEntity);
		T3D_DEFAULT_MOVE(FEntity);

	// Accessors:

		/// <returns> Index in the vector of Entities </returns>
		const T3D_EntityID& GetID() const;

		std::vector<FComponentDescription>& GetComponentDescriptions();

	private:

	// Variables:

		// It is actually an index in the vector of Entities.
		T3D_EntityID ID;

		std::vector<FComponentDescription> ComponentDescriptions;
	};
}