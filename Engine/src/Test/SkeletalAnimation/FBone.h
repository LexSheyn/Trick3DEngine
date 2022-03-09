#pragma once

#include "FBoneInfo.h"
#include "FKeyPosition.h"
#include "FKeyRotation.h"
#include "FKeyScale.h"

namespace t3d
{
	class FBone
	{
	public:

	// Constructors and Destructor:

		FBone() {}

		~FBone() {}

	private:

	// Variables:

		std::vector<FKeyPosition> Positions;
		std::vector<FKeyRotation> Rotations;
		std::vector<FKeyScale>    Scales;

		uint64 NumPositions;
		uint64 NumRotations;
		uint64 NumScales;

		glm::mat4 LocalTransform;

		std::string Name;

		uint64 ID;
	};
}