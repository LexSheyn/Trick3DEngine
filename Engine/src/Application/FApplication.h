#pragma once

#include "../Render/Systems/FMeshRenderSystem.h"
#include "../Render/Systems/FPointLightRenderSystem.h"
#include "../Render/Core/FRenderer.h"

//#include "../Events/FEventSystem.h"

namespace t3d
{
	class Test : public IEventListener
	{
	public:

		 Test() { LOG_TRACE("CREATED " + std::to_string(this->GetID())); }
		~Test() { LOG_TRACE("DELETED " + std::to_string(this->GetID())); }

		void OnEvent(const FEvent* const Event) override
		{
		//	if (Event->GetType() == EEventType::KeyPressed)
		//	{
		//		LOG_TRACE("[" + std::to_string(this->GetID()) + "]: " + std::to_string(Event->KeyData.Key) + " Pressed");
		//	}
		//	else if (Event->GetType() == EEventType::KeyReleased)
		//	{
		//		LOG_TRACE("[" + std::to_string(this->GetID()) + "]: " + std::to_string(Event->KeyData.Key) + " Released");
		//	}
		}
	};

	class FApplication
	{
	public:

	// Constructors and Destructor:

		FApplication();

		~FApplication();

		T3D_NO_COPY(FApplication);
		T3D_NO_MOVE(FApplication);

	// Functions:

		void InitRenderer();

		void Run();

		void Update();

		void Render();

	private:

	// Private Functions:

		void LoadGameObjects();

	// Variables:

		int32 Width;
		int32 Height;

		FWindow   Window;
		FDevice   Device;
		FRenderer Renderer;

		// Note: Order of declaration matters!
		FDescriptorPool* DescriptorPool;

		std::unordered_map<uint32, OGameObject> GameObjects;

		std::map<std::string, FMesh*> Meshes;

		Test A;
		Test B;
	};
}