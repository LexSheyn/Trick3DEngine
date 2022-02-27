#pragma once

#include "IComponent.h"
#include "../../Templates/TAutoID.h"

namespace t3d
{
	class CTransformComponent : public IComponent
	{
	public:

	// Constructor:

	//	CTransformComponent()
	//		: Translation({ 0.0f }),
	//		  Rotation   ({ 0.0f }),
	//		  Scale      ({ 1.0f })
	//	{}

	// Public ID:

		static constexpr T3D_ComponentID ID = TAutoID<CTransformComponent>::GetNew();

	private:

	// Variables:

		alignas(16) glm::vec3 Translation;

		alignas(16) glm::vec3 Rotation;

		alignas(16) glm::vec3 Scale;
	};
}