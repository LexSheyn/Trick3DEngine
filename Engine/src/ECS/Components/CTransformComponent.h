#pragma once

#include "IComponent.h"

namespace t3d
{
	class CTransformComponent : public IComponent
	{
	public:

	// Constructor:

		CTransformComponent()
			: Translation({ 0.0f }),
			  Rotation   ({ 0.0f }),
			  Scale      ({ 1.0f })
		{}

	private:

	// Type:

		static constexpr EComponentType Type = EComponentType::Transform;

	// Variables:

		alignas(16) glm::vec3 Translation;

		alignas(16) glm::vec3 Rotation;

		alignas(16) glm::vec3 Scale;
	};
}