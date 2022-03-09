#pragma once

#include "FBone.h"

namespace t3d
{
	class FAnimatedModel
	{
	public:

	// Constructors and Destructor:

		FAnimatedModel() {}

		~FAnimatedModel() {}

	private:

	// Skin:

		// Mesh
		// Texture

	// Skeleton:

		FBone  RootBone;
		uint64 NumBones;

		// Animator???
	};
}