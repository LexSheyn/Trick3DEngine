#pragma once

#include "../../Types/ECSTypes.h"

namespace t3d
{
	class IComponent
	{
	public:

		const T3D_EntityID& GetEntityID() const;

		void SetEntityID(T3D_EntityID ID);

	private:

		T3D_EntityID EntityID = T3D_ENTITY_INVALID_ID;
	};
}