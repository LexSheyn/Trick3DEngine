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

	//	T3D_NO_COPY(FEntity);
	//	T3D_DEFAULT_MOVE(FEntity);

	// Accessors:

		const T3D_EntityID& GetID() const;

		std::vector<FComponentDescription>& GetComponentDescriptions();

	private:

	// Private Modifiers:

		void SetID(T3D_EntityID Value);

	// Variables:

		// It is actually index in the vector of Entities.
		T3D_EntityID ID;

		std::vector<FComponentDescription> ComponentDescriptions;

	// Friends:

		friend class SEntityComponentSystem;
	};
}