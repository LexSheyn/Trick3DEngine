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
		  MeshRenderSystem(Device, Renderer)
	{
	}

	FApplication::~FApplication()
	{
	}


// Functions:

	void FApplication::Run()
	{
		while (!Window.ShouldClose())
		{
			this->Update();

			this->Render();

			std::this_thread::sleep_for(std::chrono::microseconds(16600)); // ~60 FPS // NEED TO BE MOVED SOMEWHERE ELSE!!!
		}
	}

	void FApplication::Update()
	{
		Window.Update();

		SEventSystem::ProcessEvents();

		// Other stuff here.
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
