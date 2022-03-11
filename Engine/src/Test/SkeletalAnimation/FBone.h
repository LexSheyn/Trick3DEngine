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
		// Reads keyframes from aiNodeAnim...
		FBone(const std::string& Name, uint64 ID, const aiNodeAnim* Channel);

		~FBone();

	// Functions:

		// Intarpolates between positions, rotations and scaling keys based on the current time of the animation
		// and prepares the local transformation matrix by combining all key transformations.
		void Update(const float32& AnimationTime);

	private:

	// Private Functions:

		glm::mat4 InterpolatePosition(float32 AnimationTime) { return glm::mat4(); }

		glm::mat4 InterpolateRotation(float32 AnimationTime) { return glm::mat4(); }

		glm::mat4 InterpolateScaling(float32 AnimationTime) { return glm::mat4(); }

	// Variables:

		std::vector<FKeyPosition> Positions;
		std::vector<FKeyRotation> Rotations;
		std::vector<FKeyScale>    Scales;

		uint64 NumPositions;
		uint64 NumRotations;
		uint64 NumScales;

		std::string Name;

		uint64 ID;

		glm::mat4 LocalTransform;
	};
}