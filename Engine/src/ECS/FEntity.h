#pragma once

#include "TComponent.h"
#include "FEntityComponentSystem.h"

namespace t3d
{
	class FEntity
	{
	public:

	// Constructor:

		explicit FEntity(FEntityComponentSystem& EntityComponentSystem)
			: //ID(EntityComponentSystem.GetNewID()).
			  EntityComponentSystem(EntityComponentSystem)
		{
		//	EntityComponentSystem.RegisterEntity(ID);
		}

	// Functions:

		template<class C, typename... Args>
		C* Add(Args&&... Arguments)
		{
		//	return EntityComponentSystem.AddComponent<C>(ID, std::forward<Args>(Arguments)...);
			return nullptr;
		}

		template<class C>
		C* Add(C&& Class)
		{
		//	return EntityComponentSystem.AddComponent<C>(ID, std::forward<C>(Class));
			return nullptr;
		}

		T3D_EntityID GetID() const
		{
			return ID;
		}

	private:

	// Variables:

		T3D_EntityID ID;

		FEntityComponentSystem EntityComponentSystem;			
	};
}