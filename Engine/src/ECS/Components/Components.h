#pragma once

#include "TComponent.h"

namespace t3d
{
	struct CName : public TComponent<struct CName>
	{
		std::string Name;
	};

	// Matrix multiplication order: Translation * Rotation * Scale.
	// The order is from right to left, unlike usual number multiplication.
	// So technically that means that Scale applied first, then Rotation and than Translation.
	struct CTransform : public TComponent<struct CTransform>
	{
		alignas(16) glm::vec3 Translation {};

		alignas(16) glm::vec3 Rotation    {};

		alignas(16) glm::vec3 Scale       {};
	};

	struct CHealth : public TComponent<struct CHealth>
	{
		float32 HpMax {};

		float32 Hp    {};
	};

	struct CEnergy : public TComponent<struct CEnergy>
	{
		float32 EpMax {};

		float32 Ep    {};
	};


// Skeletal Animation Test:

	struct CModel : public TComponent<struct CModel>
	{
		class FMesh* Mesh;
	};

//	class FBone
//	{
//	public:
//
//		FBone(uint64 Index, const std::string& Name, glm::mat4 LocalBindTransform)
//			: Index              (Index),
//			  Name               (Name),
//			  LocalBindTransform (LocalBindTransform)
//		{}
//
//		void AddChild(const FBone& Child)
//		{
//			Children.push_back(Child);
//		}
//
//	private:
//
//		uint64 Index;
//
//		std::string Name;
//
//		std::vector<FBone> Children;
//
//		glm::mat4 AnimatedTransform;
//
//		glm::mat4 LocalBindTransform;
//
//		glm::mat4 InverseBindTransform;
//	};

	struct CAnimatedModel : public TComponent<struct CAnimatedModel>
	{
		// Joint: JointHeirarchy.

		// Vertex Array Object (VAO): Mesh.
			// vec3  Position;
			// vec2  TexCoord;
			// vec3  Normal;
			// ivec3 JointIDs;
			// vec3  Weights;
	};

	struct FJointTransform
	{
		alignas(16) glm::vec3 Position;

		// Quaternion Rotation;
	};

	struct FKeyFrame
	{
		// JointTransform Transforms[];

		float32 TimeStamp;
	};

	struct CAnimation : public TComponent<struct CAnimation>
	{
		// FKeyFrame Frames[];
	};

	class FAnimator
	{
		CAnimation CurrentAnimation;

		float32 AnimationTime;
	};

	class FModelLoader
	{};

	class FAnimationLoader
	{};
}