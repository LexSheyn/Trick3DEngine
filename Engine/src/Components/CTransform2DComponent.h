#pragma once

#include "DComponent.h"

namespace t3d
{
	class CTransform2DComponent : public DComponent
	{
	public:

		// Position offset.
		glm::vec2 Translation{};

		glm::vec2 Scale{ 1.0f, 1.0f };

		float32 Rotation{};

		glm::mat2 Mat2()
		{
			const float32 Sin = glm::sin(Rotation);
			const float32 Cos = glm::cos(Rotation);

			glm::mat2 RotationMatrix{ { Cos, Sin }, { -Sin, Cos } };

			glm::mat2 ScaleMatrix{ { Scale.x, 0.0f }, { 0.0f, Scale.y } };

			return RotationMatrix * ScaleMatrix;
		}
	};
}