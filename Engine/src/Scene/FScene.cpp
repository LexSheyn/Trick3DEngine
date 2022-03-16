#include "../PrecompiledHeaders/t3dpch.h"
#include "FScene.h"

namespace t3d
{
// Constructors and Destructor:

	FScene::FScene()
	{
		TestEntity = T3D_ENTITY_INVALID_ID;

		this->CreateTestEntity();

		TestCamera.SetPerspectiveProjection(50.0f, 800.0f/600.0f, -10.0f, 100.0f);
		TestCamera.SetViewYXZ(FVec3(0.0f, 0.0f, 5.0f), FVec3());
	}

	FScene::~FScene()
	{
		this->DeleteTestEntity();
	}


// Functions:

	void FScene::Update()
	{
	}

	void FScene::CreateTestEntity()
	{
		TestEntity = ECS.CreateEntity();

		ECS.AddComponent<CTransform>(TestEntity);
		ECS.AddComponent<CCamera>(TestEntity);
		ECS.AddComponent<CModel>(TestEntity);

		ECS.GetComponent<CTransform>(TestEntity)->Translation = FVec3(0.0f, 0.0f, 0.0f);
		ECS.GetComponent<CTransform>(TestEntity)->Scale = FVec3(0.1f, 0.1f, 0.1f);
	}

	void FScene::DeleteTestEntity()
	{
		ECS.RemoveEntity(TestEntity);
	}

}