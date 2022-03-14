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
		FSound::Initialize(0.4f);
		FSound::LoadFile(ESound::KeyPress  , "D:/Royalty FREE Music/ZapSplat/SFX/zapsplat_multimedia_button_click_001_78078.mp3");
		FSound::LoadFile(ESound::KeyRelease, "D:/Royalty FREE Music/ZapSplat/SFX/zapsplat_multimedia_button_click_002_78079.mp3");

		SEventSystem::Subscribe(EEventType::KeyPressed , FSound::GetInstance());
		SEventSystem::Subscribe(EEventType::KeyReleased, FSound::GetInstance());
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
			this->Update();

			this->Render();

			std::this_thread::sleep_for(std::chrono::microseconds(16600)); // ~60 FPS // NEED TO BE MOVED SOMEWHERE ELSE!!!
		}
	}

	void FApplication::Update()
	{
		Window.Update();

		SEventSystem::ProcessEvents();

		FSound::Update();

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
