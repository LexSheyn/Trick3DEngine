#include "../PCH/t3dpch.h"
#include "MSceneManager.h"

namespace t3d
{
// Constructors and Destructor:

	MSceneManager::MSceneManager()
		: ActiveScene(EScene::MainMenu)
	{

		SEvent::FramebufferSize.Subscribe(this, OnFramebufferSize);
		SEvent::KeyPress.Subscribe(this, OnKeyPress);
	}

	MSceneManager::~MSceneManager()
	{
		SEvent::FramebufferSize.Unsubscribe(OnFramebufferSize);
		SEvent::KeyPress.Unsubscribe(OnKeyPress);
	}


// Functions:

	void MSceneManager::SetActive(EScene Name)
	{
		ActiveScene = Name;
	}

	void MSceneManager::Update()
	{
		Scenes[ActiveScene].Update();
	}


// Accessors:

	FScene& MSceneManager::GetActiveScene()
	{
		return Scenes[ActiveScene];
	}


// Private Functions:

	void MSceneManager::LoadScene(EScene Name)
	{
		// To do
	}

	void MSceneManager::UnloadScene(EScene Name)
	{
		// To do
	}

	void MSceneManager::LoadFromFile(EScene Name)
	{
		// To do
	}

	void MSceneManager::SaveToFile(EScene Name)
	{
		// To do
	}


// Event Callbacks:

	bool8 MSceneManager::OnFramebufferSize(FObject Instance, const FFramebufferSizeData& Data)
	{
		MSceneManager* Manager = Instance.Get<MSceneManager>();

		float32 AspectRatio = static_cast<float32>(Data.Width) / static_cast<float32>(Data.Height);

		Manager->Scenes[Manager->ActiveScene].TestCamera.SetPerspectiveProjection(glm::radians(50.0f), AspectRatio, 0.1f, 100.0f);
	
		return true;
	}

	bool8 MSceneManager::OnKeyPress(FObject Instance, const FKeyData& Data)
	{
		MSceneManager* Manager = Instance.Get<MSceneManager>();

		if (Data.Key == FKey::C)
		{
			Manager->Scenes[Manager->ActiveScene].CreateTestEntity();
		}
		else if (Data.Key == FKey::L)
		{
			Manager->Scenes[Manager->ActiveScene].LoadTestMesh();
		}
		else if (Data.Key == FKey::D)
		{
			Manager->Scenes[Manager->ActiveScene].DeleteTestEntity();
		}

		return true;
	}

}