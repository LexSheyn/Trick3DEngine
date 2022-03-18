#include "../PrecompiledHeaders/t3dpch.h"
#include "MSceneManager.h"

namespace t3d
{
// Constructors and Destructor:

	MSceneManager::MSceneManager()
		: ActiveScene(EScene::MainMenu)
	{
		SEventSystem::Subscribe(EEventType::WindowResized, this);
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
	}

}