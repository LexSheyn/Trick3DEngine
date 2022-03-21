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

		LightSource = SEntityComponentSystem::CreateEntity();
		SEntityComponentSystem::AddComponent<CDirectionalLight>(LightSource);
		CDirectionalLight* LightComponent = SEntityComponentSystem::GetComponent<CDirectionalLight>(LightSource);
		LightComponent->Direction = FVec3(1.0f, -3.0, -2.0f);
	}

	FScene::~FScene()
	{
		delete MeshPtr;

		SEntityComponentSystem::RemoveEntity(LightSource);
	}


// Functions:

	void FScene::Update()
	{
	}

	void FScene::CreateTestEntity()
	{
		T3D_EntityID NewEntity = SEntityComponentSystem::CreateEntity();

		SEntityComponentSystem::AddComponent<CTransform>(NewEntity);
		SEntityComponentSystem::AddComponent<CCamera>(NewEntity);
		SEntityComponentSystem::AddComponent<CModel>(NewEntity);

	//	SEntityComponentSystem::GetComponent<CTransform>(NewEntity)->Translation = FVec3(0.0f, 0.0f, 5.0f);
		SEntityComponentSystem::GetComponent<CTransform>(NewEntity)->Translation = FVec3(static_cast<float32>(NewEntity) - 5.0f, 0.0f, static_cast<float32>(NewEntity) + 5.0f);
		SEntityComponentSystem::GetComponent<CTransform>(NewEntity)->Rotation    = FVec3(static_cast<float32>(NewEntity));
		SEntityComponentSystem::GetComponent<CTransform>(NewEntity)->Scale       = FVec3(0.3f, 0.3f, 0.3f);

		SEntityComponentSystem::GetComponent<CModel>(NewEntity)->Mesh = MeshPtr;

		EntityList.push_back(NewEntity);
	}

	void FScene::DeleteTestEntity()
	{
		for (auto& Entity : EntityList)
		{
			SEntityComponentSystem::RemoveEntity(Entity);
		}

		EntityList.clear();
	}

	void FScene::LoadTestMesh()
	{
		MeshPtr = MModelManager::LoadModel("D:/VULKAN_TUTORIAL_SHADERS/Models/paimon_ex.obj");
	}

}