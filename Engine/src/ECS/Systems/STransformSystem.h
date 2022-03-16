#pragma once

#include "../Components/CTransform.h"

namespace t3d
{
	// ( Z Y X ) Tait–Bryan angles convention.
	class STransformSystem
	{
	public:

	// Constructors and Destructor:

		 STransformSystem ();
		~STransformSystem ();

		T3D_NO_COPY(STransformSystem);
		T3D_NO_MOVE(STransformSystem);

	// Functions:

		const FMat4& T3D_CALL Matrix4x4(CTransform* Transform);

	private:

		// Z
		float32 Sin1;
		float32 Cos1;
		
		// Y
		float32 Sin2;
		float32 Cos2;
		
		// X
		float32 Sin3;
		float32 Cos3;

		FMat4 TransformationMatrix;
	};
}