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

	// IComponent Interface:

		virtual bool8 Initialize(void* Data) override final
		{
			// To do: Implement FMemoryPool class that allows to allocate cpmtiguous memory arrays.
			// Also override 'new' operator to allocate memory from that arrays.
		}

	// Public ID:

		static constexpr T3D_ComponentID ID = TAutoID<CTransformComponent>::GetNew();

	private:

	// Variables:

		alignas(16) glm::vec3 Translation;

		alignas(16) glm::vec3 Rotation;

		alignas(16) glm::vec3 Scale;
	};
}