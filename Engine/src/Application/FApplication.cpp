#include "../PrecompiledHeaders/t3dpch.h"
#include "FApplication.h"

namespace t3d
{
// Constructors and Destructor:

	FApplication::FApplication()
		: Width(800),
		  Height(600),
		  Window(Width, Height, "Trick 3D Engine"),
		  Device(Window),
		  Renderer(Window, Device),
		  MeshRenderSystem(Renderer)
	{
	}

	FApplication::~FApplication()
	{
		FSound::Shutdown();
	}


// Functions:

	void FApplication::Run()
	{
		while (!Window.ShouldClose())
		{
			Clock.Restart();

			this->Update();

			this->Render();

			std::this_thread::sleep_for(std::chrono::microseconds(16600)); // ~60 FPS // NEED TO BE MOVED SOMEWHERE ELSE!!!

			FDeltaTime::Set( Clock.GetElapsedTime().AsSeconds() );
		}
	}

	void FApplication::Update()
	{
	// Dedicated window update, window events coming from it:

		Window.Update();

	// Events:

		SEventSystem::ProcessEvents();

	// Update Systems:

		FUpdater::Update(0);
		FUpdater::Update(1);

	// Update SFX:

		FSound::Update();
	}

	void FApplication::Render()
	{
		Renderer.BeginFrame();

		Renderer.BeginSwapchainRenderPass();

		MeshRenderSystem.Render(SceneManager.GetActiveScene());

		Renderer.EndSwapchainRenderPass();

		Renderer.EndFrame();
	}

}
