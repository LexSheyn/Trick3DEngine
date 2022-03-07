#pragma once

#include "TComponent.h"

namespace t3d
{
	struct CName : public TComponent<struct CName>
	{
		std::string Name;
	};

	// Matrix multiplication order: Translation * Rotation * Scale.
	// The order is from right to left, unlike usual number multiplication.
	// So technically that means that Scale applied first, then Rotation and than Translation.
	struct CTransform : public TComponent<struct CTransform>
	{
		alignas(16) glm::vec3 Translation {};

		alignas(16) glm::vec3 Rotation    {};

		alignas(16) glm::vec3 Scale       {};
	};

	struct CHealth : public TComponent<struct CHealth>
	{
		float32 HpMax {};

		float32 Hp    {};
	};

	struct CEnergy : public TComponent<struct CEnergy>
	{
		float32 EpMax {};

		float32 Ep    {};
	};
}