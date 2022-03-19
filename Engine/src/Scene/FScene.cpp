#include "../PrecompiledHeaders/t3dpch.h"
#include "FScene.h"

namespace t3d
{
// Constructors and Destructor:

	FScene::FScene()
	{
		TestCamera.SetPerspectiveProjection(glm::radians(50.0f), 800.0f/600.0f, 0.1f, 100.0f);
		TestCamera.SetViewTarget(FVec3(0.0f, 0.0f, -5.0f), FVec3(0.0f));

		MeshPtr = nullptr;
	}

	FScene::~FScene()
	{
		delete MeshPtr;
	}


// Functions:

	void FScene::Update()
	{
	}

	void FScene::CreateTestEntity()
	{
		T3D_EntityID NewEntity = ECS.CreateEntity();		

		ECS.AddComponent<CTransform>(NewEntity);
		ECS.AddComponent<CCamera>(NewEntity);
		ECS.AddComponent<CModel>(NewEntity);

	//	ECS.GetComponent<CTransform>(NewEntity)->Translation = FVec3(0.0f, 0.0f, 5.0f);
		ECS.GetComponent<CTransform>(NewEntity)->Translation = FVec3(static_cast<float32>(NewEntity), -static_cast<float32>(NewEntity), static_cast<float32>(NewEntity));
		ECS.GetComponent<CTransform>(NewEntity)->Scale       = FVec3(0.3f, 0.3f, 0.3f);

		ECS.GetComponent<CModel>(NewEntity)->Mesh = MeshPtr;

		EntityList.push_back(NewEntity);
	}

	void FScene::DeleteTestEntity()
	{
		for (auto& Entity : EntityList)
		{
			ECS.RemoveEntity(Entity);
		}

		EntityList.clear();
	}

	void FScene::LoadTestMesh()
	{
		MeshPtr = MModelManager::LoadModel("D:/VULKAN_TUTORIAL_SHADERS/Models/paimon_ex.obj");
	}

}