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

		void SetOrthographicProjection    (float32 Left, float32 Right, float32 Top, float32 Bottom, float32 NearClippingPlane, float32 FarClippingPlane);
		void SetPerspectiveProjection     (float32 FieldOfViewY, float32 AspectRatio, float32 NearClippingPlane, float32 FarClippingPlaner);
		void SetViewDirection             (FVec3 Position, FVec3 Direction, FVec3 Up = FVec3( 0.0f, -1.0f, 0.0f ));
		void SetViewTarget                (FVec3 Position, FVec3 Target, FVec3 Up = FVec3( 0.0f, -1.0f, 0.0f ));
		void SetViewZYX                   (FVec3 Position, FVec3 Rotation);

	// Accessors:

		const FMat4& GetProjection    () const;
		const FMat4& GetView          () const;

	private:

	// Variables:

		FMat4 ProjectionMatrix;
		FMat4 ViewMatrix;

		float32 Sin1;
		float32 Cos1;

		float32 Sin2;
		float32 Cos2;
		
		float32 Sin3;
		float32 Cos3;

		FVec3 BasisX;
		FVec3 BasisY;
		FVec3 BasisZ;
	};
}