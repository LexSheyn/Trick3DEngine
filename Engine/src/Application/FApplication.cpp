#include "../PCH/t3dpch.h"
#include "FApplication.h"

namespace t3d
{
// Constructors and Destructor:

	FApplication::FApplication()
		:
		Width(800),
		Height(600),
		Window(Width, Height, "Trick 3D Engine"),
		Device(Window),
		Renderer(Window, Device),
		RenderSystem(Renderer)
	{
		MModelManager::SetDevice(Device);

		Updater.Subscribe(&RenderSystem);
		Updater.Subscribe(&SoundSystem);
	}

	FApplication::~FApplication()
	{
		Updater.UnsubscribeAll();
	}


// Functions:

	void FApplication::Run()
	{
		FixedUpdateThread.SetSleepDuration(20);
		FixedUpdateThread.Launch();

		do
		{
			Clock.Restart();

			FixedUpdateThread.ScheduleJob(TJob(this, FixedUpdate, {}));

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

		// TEST:
		if (glfwGetKey(Window.GetGLFWwindow(), FKey::Escape) == FKeyState::Pressed)
		{
			SEvent::ApplicationClose.Invoke({ 1 });
		}

		Updater.Update();

		Updater.LastUpdate();
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
