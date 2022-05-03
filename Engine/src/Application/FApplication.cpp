#include "../PCH/t3dpch.h"
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
		  RenderSystem(Renderer)
	{
		MModelManager::SetDevice(Device);

		Updater.Register(0, &RenderSystem);
	}

	FApplication::~FApplication()
	{
		Updater.UnregisterAll();
	}


// Functions:

	void FApplication::Run()
	{
		do
		{
			Clock.Restart();

			this->Update();

			this->Render();

			std::this_thread::sleep_for(std::chrono::microseconds(16600)); // ~60 FPS // NEED TO BE MOVED SOMEWHERE ELSE!!!

			FDeltaTime::Set( Clock.GetElapsedTime().AsSeconds() );

		} while (Window.ShouldClose() == false);
	}

	void FApplication::Update()
	{
	// Events:

		Window.CatchEvents();
		SEventSystem::PollEvents();

	// Update Systems:

	//	Updater.Update(0);

	// Update SFX:

		FSound::Update();
	}

	void FApplication::FixedUpdate()
	{
	}

	void FApplication::LateUpdate()
	{
	}

	void FApplication::Render()
	{
		Renderer.BeginFrame();
		Renderer.BeginSwapchainRenderPass();

		RenderSystem.Render(SceneManager.GetActiveScene());

		Renderer.EndSwapchainRenderPass();
		Renderer.EndFrame();
	}

}
