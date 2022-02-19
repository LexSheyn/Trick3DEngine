#pragma once

#include "../Render/Systems/FMeshRenderSystem.h"
#include "../Render/Systems/FPointLightRenderSystem.h"
#include "../Render/Core/FRenderer.h"

//#include "../Events/FEventSystem.h"

namespace test
{
	class Test : public t3d::IEventListener
	{
	public:

		 Test() {}
		~Test() {}

		void OnEvent(const t3d::FEvent* const Event) override
		{
		//	if (Event->GetType() == t3d::EEventType::KeyPressed)
		//	{
		//		t3d::LOG_TRACE("[" + std::to_string(this->GetID()) + "]: " + std::to_string(Event->KeyData.Key) + " Pressed");
		//	}
		//	else if (Event->GetType() == t3d::EEventType::KeyReleased)
		//	{
		//		t3d::LOG_TRACE("[" + std::to_string(this->GetID()) + "]: " + std::to_string(Event->KeyData.Key) + " Released");
		//	}
		}
	};

	class FApplication
	{
	public:

	// Constructors and Destructor:

		FApplication();

		FApplication(const FApplication&) = delete;

		~FApplication();

	// Operators:

		FApplication& operator=(const FApplication&) = delete;

	// Functions:

		void Run();

	private:

	// Private Functions:

		void LoadGameObjects();

	// Variables:

		int32 Width;
		int32 Height;

		t3d::FWindow   Window;
		t3d::FDevice   Device;
		t3d::FRenderer Renderer;

		// Note: Order of declaration matters!
		t3d::FDescriptorPool* DescriptorPool;

		std::unordered_map<uint32, t3d::OGameObject> GameObjects;

		std::map<std::string, t3d::FMesh*> Meshes;

		Test A;
		Test B;
	};
}