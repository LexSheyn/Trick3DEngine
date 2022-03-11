#include "../../PrecompiledHeaders/t3dpch.h"
#include "FBone.h"

namespace t3d
{
// Constructors and Destructor:

	FBone::FBone(const std::string& Name, uint64 ID, const aiNodeAnim* Channel)
		: Name           (Name),
		  ID             (ID),
		  LocalTransform (1.0f),
		  NumPositions   (),
		  NumRotations   (),
		  NumScales      ()
	{
	// Key Positions:

		NumPositions = Channel->mNumPositionKeys;

		for (uint64 i = 0u; i < NumPositions; i++)
		{
			aiVector3D aiPosition = Channel->mPositionKeys[i].mValue;

			FKeyPosition KeyPosition{};

			KeyPosition.Position.x = aiPosition.x;
			KeyPosition.Position.y = aiPosition.y;
			KeyPosition.Position.z = aiPosition.z;

			KeyPosition.TimeStamp  = static_cast<float32>(Channel->mPositionKeys[i].mTime);

			Positions.push_back(KeyPosition);
		}

	// Key Rotations:

		NumRotations = Channel->mNumRotationKeys;

		for (uint64 i = 0u; i < NumRotations; i++)
		{
			aiQuaternion aiRotation = Channel->mRotationKeys[i].mValue;

			FKeyRotation KeyRotation{};

			KeyRotation.Rotation.x = aiRotation.x;
			KeyRotation.Rotation.y = aiRotation.y;
			KeyRotation.Rotation.z = aiRotation.z;
			KeyRotation.Rotation.w = aiRotation.w;

			KeyRotation.TimeStamp = static_cast<float32>(Channel->mRotationKeys[i].mTime);

			Rotations.push_back(KeyRotation);
		}

	// Key Scales:

		NumScales = Channel->mNumScalingKeys;

		for (uint64 i = 0u; i < NumScales; i++)
		{
			aiVector3D Scale = Channel->mScalingKeys[i].mValue;

			FKeyScale KeyScale{};

			KeyScale.Scale.x = Scale.x;
			KeyScale.Scale.y = Scale.y;
			KeyScale.Scale.z = Scale.z;

			KeyScale.TimeStamp = static_cast<float32>(Channel->mScalingKeys[i].mTime);

			Scales.push_back(KeyScale);
		}
	}

	FBone::~FBone()
	{
	}


// Functions:

	void FBone::Update(const float32& AnimationTime)
	{
		glm::mat4 Translation = this->InterpolatePosition(AnimationTime);
		glm::mat4 Rotation    = this->InterpolateRotation(AnimationTime);
		glm::mat4 Scale       = this->InterpolateScaling(AnimationTime);

		LocalTransform = Translation * Rotation * Scale;
	}

}