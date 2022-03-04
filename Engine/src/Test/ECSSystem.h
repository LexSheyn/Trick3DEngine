#pragma once

#include "ECSComponent.h"

namespace t3d
{
	class BaseECSSystem
	{
	public:

		BaseECSSystem(const std::vector<uint64>& ComponentTypes) : ComponentTypes(ComponentTypes) {}

		virtual void UpdateComponents(float32 DeltaTime, BaseECSComponent** Components) {}

		const std::vector<uint64>& GetComponentTypes() const { return ComponentTypes; }

	private:

		std::vector<uint64> ComponentTypes;
	};
}