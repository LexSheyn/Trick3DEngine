#pragma once

#include "ECSTypes.h"

namespace t3d
{
	class FEntity
	{
	public:

	// Constructors and Destructor:

		explicit FEntity(T3D_EntityID ID) : ID(ID) {}
		
		~FEntity() {}

	// Accessors:

		T3D_INLINE const T3D_EntityID& GetID() const { return ID; }

		template<class C>
		C* GetComponent() const
		{
			auto ComponentIterator = Components.find(C::ID);

			if (ComponentIterator != Components.end())
			{
				return ComponentIterator->second;
			}

			LOG_WARNING("Componen not found!");

			return nullptr;
		}

	private:

	// Variables:

		T3D_EntityID ID;
		
		std::unordered_map<T3D_ComponentID, struct IComponent*> Components;
	};
}