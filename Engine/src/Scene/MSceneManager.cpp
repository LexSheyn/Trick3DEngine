#include "../PCH/t3dpch.h"
#include "MSceneManager.h"

namespace t3d
{
// Constructors and Destructor:

	MSceneManager::MSceneManager()
		: ActiveScene(EScene::MainMenu)
	{
		SEventSystem::Subscribe(EEventType::WindowResized, this);
		SEventSystem::Subscribe(EEventType::KeyPressed   , this);
	}

	MSceneManager::~MSceneManager()
	{
		SEventSystem::UnsubscribeFromAll(this);
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
		// To do...
	}

	void MSceneManager::UnloadScene(EScene Name)
	{
		// To do...
	}

	void MSceneManager::LoadFromFile(EScene Name)
	{
		// To do...
	}

	void MSceneManager::SaveToFile(EScene Name)
	{
		// To do...
	}


// IEventListener Interface:

	void MSceneManager::OnEvent(const FEvent* const Event)
	{
		if (Event->GetType() == EEventType::WindowResized)
		{
			float32 AspectRatio = static_cast<float32>(Event->FramebufferSizeData.Width) / static_cast<float32>(Event->FramebufferSizeData.Height);
		
			Scenes[ActiveScene].TestCamera.SetPerspectiveProjection(glm::radians(50.0f), AspectRatio, 0.1f, 100.0f);
		}
		else if (Event->GetType() == EEventType::KeyPressed && Event->KeyData.Key == FKey::C)
		{
			Scenes[ActiveScene].CreateTestEntity();
		}
		else if (Event->GetType() == EEventType::KeyPressed && Event->KeyData.Key == FKey::L)
		{
			Scenes[ActiveScene].LoadTestMesh();
		}
		else if (Event->GetType() == EEventType::KeyPressed && Event->KeyData.Key == FKey::D)
		{
			Scenes[ActiveScene].DeleteTestEntity();
		}
	}

}