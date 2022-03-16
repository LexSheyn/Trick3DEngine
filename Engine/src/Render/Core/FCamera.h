#pragma once

namespace t3d
{
	class FCamera
	{
	public:

	// Constructors and Destructor:

		 FCamera ();
		~FCamera ();

	// Functions:

		void T3D_CALL SetOrthographicProjection    (float32 Left, float32 Right, float32 Top, float32 Bottom, float32 NearClippingPlane, float32 FarClippingPlane);
		void T3D_CALL SetPerspectiveProjection     (float32 FieldOfViewY, float32 AspectRatio, float32 NearClippingPlane, float32 FarClippingPlaner);
		void T3D_CALL SetViewDirection             (FVec3 Position, FVec3 Direction, FVec3 Up = FVec3( 0.0f, -1.0f, 0.0f ));
		void T3D_CALL SetViewTarget                (FVec3 Position, FVec3 Target, FVec3 Up = FVec3( 0.0f, -1.0f, 0.0f ));
		void T3D_CALL SetViewYXZ                   (FVec3 Position, FVec3 Rotation);

	// Accessors:

		const FMat4& GetProjection    () const;
		const FMat4& GetView          () const;

	private:

	// Variables:

		FMat4 ProjectionMatrix;
		FMat4 ViewMatrix;
	};
}