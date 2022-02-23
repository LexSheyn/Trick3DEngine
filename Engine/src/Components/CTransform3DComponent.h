#pragma once

#include "DComponent.h"

namespace t3d
{
	class CTransform3DComponent : public DComponent
	{
	public:

    // Functions:

		// Matrix corresponds to Translation * Ry * Rx * Rz * Scale transformation.
		// Rotation convertion uses Tait-Bryan angles with axis order Y(1), X(2), Z(3).
		glm::mat4 Mat4();

		glm::mat3 NormalMatrix();

		void Translate(const glm::vec3& Translation);

		void Upscale(const glm::vec3& Scale);

		void Rotate(const glm::vec3& Rotation);

	// Accessors:

		T3D_INLINE const glm::vec3& GetTranslation() const { return Translation; }

		T3D_INLINE const glm::vec3& GetScale()       const { return Scale; }

		T3D_INLINE const glm::vec3& GetRotation()    const { return Rotation; }

	// Modifiers:

		void SetTranslation(const glm::vec3& Translation);

		void SetScale(const glm::vec3& Scale);

		void SetRotation(const glm::vec3& Rotation);

	private:

    // Variables:

		// Position offset.
		glm::vec3 Translation {};

		glm::vec3 Scale       { 1.0f };

		glm::vec3 Rotation    {};
	};
}