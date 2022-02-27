#pragma once

#include "../Types/T3DTypes.h"

namespace t3d
{
	class CRigidBody2DComponent
	{
	public:

		glm::vec2 Velocity{};

		float32 Mass{ 1.0f };
	};
}