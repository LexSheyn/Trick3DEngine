#pragma once

#include "../Components/FComponentDescription.h"

namespace t3d
{
	class FEntity
	{
	public:

	// Constructors and Destructor:

		 FEntity (T3D_EntityID Value);
		~FEntity ();

		T3D_NO_COPY(FEntity);
		T3D_DEFAULT_MOVE(FEntity);

	// Accessors:

		/// <returns> Index in the vector of Entities </returns>
		const T3D_EntityID&                 GetID                       () const;
		std::vector<FComponentDescription>& GetComponentDescriptions    ();

		const T3D_EntityID&        GetParent      () const;
		std::vector<T3D_EntityID>& GetChildren    ();

	// Modifiers:

		void SetParent(T3D_EntityID EntityID);

	private:

	// Variables:

		// It is actually an index in the vector of Entities.
		T3D_EntityID ID;

		std::vector<FComponentDescription> ComponentDescriptions;

		T3D_EntityID              Parent;
		std::vector<T3D_EntityID> Children;
	};
}