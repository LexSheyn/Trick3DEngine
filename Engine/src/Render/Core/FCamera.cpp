#include "../../PrecompiledHeaders/t3dpch.h"
#include "FCamera.h"

namespace t3d
{
// Constructors and Destructor:

	FCamera::FCamera()
		: ProjectionMatrix (1.0f),
		  ViewMatrix       (1.0f),

		  Sin1 (0.0f),
		  Cos1 (0.0f),

		  Sin2 (0.0f),
		  Cos2 (0.0f),

		  Sin3 (0.0f),
		  Cos3 (0.0f),

		  BasisX (0.0f),
		  BasisY (0.0f),
		  BasisZ (0.0f)
	{
	}

	FCamera::~FCamera()
	{
	}


// Functions:

	void FCamera::SetOrthographicProjection(float32 Left, float32 Right, float32 Top, float32 Bottom, float32 NearClippingPlane, float32 FarClippingPlane)
	{
		ProjectionMatrix = FMat4{ 1.0f };

		ProjectionMatrix[0][0] = 2.0f / (Right - Left);
		ProjectionMatrix[1][1] = 2.0f / (Bottom - Top);
		ProjectionMatrix[2][2] = 1.0f / (FarClippingPlane - NearClippingPlane);
		ProjectionMatrix[3][0] = -(Right + Left) / (Right - Left);
		ProjectionMatrix[3][1] = -(Bottom + Top) / (Bottom - Top);
		ProjectionMatrix[3][2] = -NearClippingPlane / (FarClippingPlane - NearClippingPlane);
	}

	void FCamera::SetPerspectiveProjection(float32 FieldOfViewY, float32 AspectRatio, float32 NearClippingPlane, float32 FarClippingPlane)
	{
		const float32 TanHalfFovY = glm::tan(FieldOfViewY / 2.0f);

		ProjectionMatrix = FMat4{ 0.0f };
		
		ProjectionMatrix[0][0] = 1.0f / (AspectRatio * TanHalfFovY);
		ProjectionMatrix[1][1] = 1.0f / (TanHalfFovY);
		ProjectionMatrix[2][2] = FarClippingPlane / (FarClippingPlane - NearClippingPlane);
		ProjectionMatrix[2][3] = 1.0f;
		ProjectionMatrix[3][2] = -(FarClippingPlane * NearClippingPlane) / (FarClippingPlane - NearClippingPlane);
	}

	void FCamera::SetViewDirection(FVec3 Position, FVec3 Direction, FVec3 Up)
	{
		BasisZ = glm::normalize(Direction);
		BasisX = glm::normalize(glm::cross(BasisZ, Up));
		BasisY = glm::cross(BasisZ, BasisX);

		ViewMatrix = FMat4{ 1.f };

		ViewMatrix[0][0] = BasisX.x;
		ViewMatrix[1][0] = BasisX.y;
		ViewMatrix[2][0] = BasisX.z;

		ViewMatrix[0][1] = BasisY.x;
		ViewMatrix[1][1] = BasisY.y;
		ViewMatrix[2][1] = BasisY.z;

		ViewMatrix[0][2] = BasisZ.x;
		ViewMatrix[1][2] = BasisZ.y;
		ViewMatrix[2][2] = BasisZ.z;

		ViewMatrix[3][0] = -glm::dot(BasisX, Position);
		ViewMatrix[3][1] = -glm::dot(BasisY, Position);
		ViewMatrix[3][2] = -glm::dot(BasisZ, Position);
	}

	void FCamera::SetViewTarget(FVec3 Position, FVec3 Target, FVec3 Up)
	{
		this->SetViewDirection(Position, Target - Position, Up);
	}

	void FCamera::SetViewZYX(FVec3 Position, FVec3 Rotation)
	{
		Sin1 = glm::sin(Rotation.z);
		Cos1 = glm::cos(Rotation.z);

		Sin2 = glm::sin(Rotation.y);
		Cos2 = glm::cos(Rotation.y);
		
		Sin3 = glm::sin(Rotation.x);
		Cos3 = glm::cos(Rotation.x);
		
		BasisX = { (Cos1 * Cos2), (Cos2 * Sin1), (-Sin2) };
		BasisY = { ( (Cos1 * Sin2 * Sin3) - (Cos3 * Sin1) ), ( (Cos1 * Cos3) + (Sin1 * Sin2 * Sin3) ), (Cos2 * Sin3) };
		BasisZ = { ( (Sin1 * Sin3) + (Cos1 * Cos3 * Sin2) ), ( (Cos3 * Sin1 * Sin2) - (Cos1 * Sin3) ), (Cos2 * Cos3) };
		
		ViewMatrix = FMat4{ 1.f };

		ViewMatrix[0][0] = BasisX.x;
		ViewMatrix[1][0] = BasisX.y;
		ViewMatrix[2][0] = BasisX.z;		
		
		ViewMatrix[0][1] = BasisY.x;
		ViewMatrix[1][1] = BasisY.y;
		ViewMatrix[2][1] = BasisY.z;		
		
		ViewMatrix[0][2] = BasisZ.x;
		ViewMatrix[1][2] = BasisZ.y;
		ViewMatrix[2][2] = BasisZ.z;		
		
		ViewMatrix[3][0] = -glm::dot(BasisX, Position);
		ViewMatrix[3][1] = -glm::dot(BasisY, Position);
		ViewMatrix[3][2] = -glm::dot(BasisZ, Position);
	}


// Accessors:

	const FMat4& FCamera::GetProjection() const
	{
		return ProjectionMatrix;
	}

	const FMat4& FCamera::GetView() const
	{
		return ViewMatrix;
	}

}