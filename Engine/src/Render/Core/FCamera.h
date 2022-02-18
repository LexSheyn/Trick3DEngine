#pragma once

namespace t3d
{
	class FCamera
	{
	public:

	// Constructors and Destructor:

	//	FCamera();

	// Functions:

		void SetOrthographicProjection(float32 Left, float32 Right, float32 Top, float32 Bottom, float32 NearClippingPlane, float32 FarClippingPlane);

		void SetPerspectiveProjection(float32 FieldOfViewY, float32 AspectRatio, float32 NearClippingPlane, float32 FarClippingPlaner);

		void SetViewDirection(glm::vec3 Position, glm::vec3 Direction, glm::vec3 Up = glm::vec3( 0.0f, -1.0f, 0.0f ));

		void SetViewTarget(glm::vec3 Position, glm::vec3 Target, glm::vec3 Up = glm::vec3( 0.0f, -1.0f, 0.0f ));

		void SetViewYXZ(glm::vec3 Position, glm::vec3 Rotation);

	// Accessors:

		T3D_INLINE const glm::mat4& GetProjection() const { return ProjectionMatrix; }

		T3D_INLINE const glm::mat4& GetView()       const { return ViewMatrix; }

	private:

	// Variables:

		glm::mat4 ProjectionMatrix{ 1.0f };

		glm::mat4 ViewMatrix{ 1.0f };
	};
}