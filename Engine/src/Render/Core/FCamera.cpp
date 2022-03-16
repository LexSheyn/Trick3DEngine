#include "../../PrecompiledHeaders/t3dpch.h"
#include "FCamera.h"

namespace t3d
{
// Constructors and Destructor:

	FCamera::FCamera()
		: ProjectionMatrix (1.0f),
		  ViewMatrix       (1.0f)
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
		if (glm::abs(AspectRatio - std::numeric_limits<float32>::epsilon()) < 0.0f)
		{
			LOG_ERROR("Aspect ratio need to be more than epsilon");
			throw;
		}

		const float32 TanHalfFovy = glm::tan(FieldOfViewY / 2.0f); // std::tan ???

		ProjectionMatrix = FMat4{ 0.0f };
		
		ProjectionMatrix[0][0] = 1.0f / (AspectRatio * TanHalfFovy);
		ProjectionMatrix[1][1] = 1.0f / (TanHalfFovy);
		ProjectionMatrix[2][2] = FarClippingPlane / (FarClippingPlane - NearClippingPlane);
		ProjectionMatrix[2][3] = 1.0f;
		ProjectionMatrix[3][2] = -(FarClippingPlane * NearClippingPlane) / (FarClippingPlane - NearClippingPlane);
	}

	void FCamera::SetViewDirection(FVec3 Position, FVec3 Direction, FVec3 Up)
	{
		const FVec3 W{ glm::normalize(Direction) };
		const FVec3 U{ glm::normalize(glm::cross(W, Up)) };
		const FVec3 V{ glm::cross(W, U) };

		ViewMatrix = FMat4{ 1.f };

		ViewMatrix[0][0] = U.x;
		ViewMatrix[1][0] = U.y;
		ViewMatrix[2][0] = U.z;

		ViewMatrix[0][1] = V.x;
		ViewMatrix[1][1] = V.y;
		ViewMatrix[2][1] = V.z;

		ViewMatrix[0][2] = W.x;
		ViewMatrix[1][2] = W.y;
		ViewMatrix[2][2] = W.z;

		ViewMatrix[3][0] = -glm::dot(U, Position);
		ViewMatrix[3][1] = -glm::dot(V, Position);
		ViewMatrix[3][2] = -glm::dot(W, Position);
	}

	void FCamera::SetViewTarget(FVec3 Position, FVec3 Target, FVec3 Up)
	{
		this->SetViewDirection(Position, Target - Position, Up);
	}

	void FCamera::SetViewYXZ(FVec3 Position, FVec3 Rotation)
	{
		const float32 CosY = glm::cos(Rotation.y);
		const float32 SinY = glm::sin(Rotation.y);

		const float32 CosX = glm::cos(Rotation.x);
		const float32 SinX = glm::sin(Rotation.x);

		const float32 CosZ = glm::cos(Rotation.z);
		const float32 SinZ = glm::sin(Rotation.z);
		
		const FVec3 U{ (CosY * CosZ + SinY * SinX * SinZ), (CosX * SinZ), (CosY * SinX * SinZ - CosZ * SinY) };
		const FVec3 V{ (CosZ * SinY * SinX - CosY * SinZ), (CosX * CosZ), (CosY * CosZ * SinX + SinY * SinZ) };
		const FVec3 W{ (CosX * SinY), (-SinX), (CosY * CosX) };
		
		ViewMatrix = FMat4{ 1.f };

		ViewMatrix[0][0] = U.x;
		ViewMatrix[1][0] = U.y;
		ViewMatrix[2][0] = U.z;		
		
		ViewMatrix[0][1] = V.x;
		ViewMatrix[1][1] = V.y;
		ViewMatrix[2][1] = V.z;		
		
		ViewMatrix[0][2] = W.x;
		ViewMatrix[1][2] = W.y;
		ViewMatrix[2][2] = W.z;		
		
		ViewMatrix[3][0] = -glm::dot(U, Position);
		ViewMatrix[3][1] = -glm::dot(V, Position);
		ViewMatrix[3][2] = -glm::dot(W, Position);
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