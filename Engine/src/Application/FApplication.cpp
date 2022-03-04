#include "../PrecompiledHeaders/t3dpch.h"
#include "FApplication.h"

// Disable warnings from Vulkan SDK:
#pragma warning( push ) // Vulkan SDK - Begin
#pragma warning( disable : 26812 ) // Uncoped Enum

#include "../Components/CMovementComponent.h"

#include "../Templates/TScopedPointer.h"

#include "../Test/TestComponent.h"

namespace test
{
// Constructors and Destructor:

	FApplication::FApplication()
		: Width(800),
		  Height(600),
		  Window(Width, Height, "Trick 3D Engine"),
		  Device(Window),
		  Renderer(Window, Device)
	{
		DescriptorPool = t3d::FDescriptorPool::Constructor(Device)
			             .SetMaxSets(t3d::FSwapchain::MAX_FRAMES_IN_FLIGHT)
			             .AddPoolSize(VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, t3d::FSwapchain::MAX_FRAMES_IN_FLIGHT)
			             .Create();

		this->LoadGameObjects();

		t3d::FEventSystem::Subscribe(t3d::EEventType::KeyPressed, &A);

		t3d::FEventSystem::Subscribe(t3d::EEventType::KeyPressed , &B);
		t3d::FEventSystem::Subscribe(t3d::EEventType::KeyReleased, &B);

		t3d::TScopedPointer<Test> P;

		P = t3d::MakeScoped<Test>();
	}

	FApplication::~FApplication()
	{
		for (auto& Mesh : Meshes)
		{
			delete Mesh.second;
		}

		delete DescriptorPool;
	}


// Functions:

	void FApplication::InitRenderer()
	{
		std::vector<t3d::FDeviceBuffer*> UniformDataBuffers(t3d::FSwapchain::MAX_FRAMES_IN_FLIGHT);

		for (uint64 i = 0u; i < UniformDataBuffers.size(); i++)
		{
			UniformDataBuffers[i] = new t3d::FDeviceBuffer(Device,
				                                           sizeof(t3d::FUniformBufferData),
				                                           1,
				                                           VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT,
				                                           VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT); //| VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);

			UniformDataBuffers[i]->Map();
		}

		t3d::FDescriptorSetLayout* GlobalDescriptorSetLayout = t3d::FDescriptorSetLayout::Constructor(Device)
			                                                   .AddBinding(0, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, VK_SHADER_STAGE_ALL_GRAPHICS)
			                                                   .Create();

		std::vector<VkDescriptorSet> GlobalDescriptorSets(t3d::FSwapchain::MAX_FRAMES_IN_FLIGHT); // Cleaned up automatically, but it is not be the case in the future!

		for (uint64 i = 0u; i < GlobalDescriptorSets.size(); i++)
		{
			VkDescriptorBufferInfo BufferInfo = UniformDataBuffers[i]->DescriptorInfo();

			t3d::FDescriptorWriter(*GlobalDescriptorSetLayout, *DescriptorPool).WriteBuffer(0, &BufferInfo).Build(GlobalDescriptorSets[i]);
		}
	}

	void FApplication::Run()
	{
		std::vector<t3d::FDeviceBuffer*> UniformDataBuffers(t3d::FSwapchain::MAX_FRAMES_IN_FLIGHT);

		for (uint64 i = 0u; i < UniformDataBuffers.size(); i++)
		{
			UniformDataBuffers[i] = new t3d::FDeviceBuffer(Device,
				                                           sizeof(t3d::FUniformBufferData),
				                                           1,
				                                           VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT,
				                                           VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT); //| VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);

			UniformDataBuffers[i]->Map();
		}

		t3d::FDescriptorSetLayout* GlobalDescriptorSetLayout = t3d::FDescriptorSetLayout::Constructor(Device)
			                                                   .AddBinding(0, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, VK_SHADER_STAGE_ALL_GRAPHICS)
			                                                   .Create();

		std::vector<VkDescriptorSet> GlobalDescriptorSets(t3d::FSwapchain::MAX_FRAMES_IN_FLIGHT); // Cleaned up automatically, but it is not be the case in the future!

		for (uint64 i = 0u; i < GlobalDescriptorSets.size(); i++)
		{
			VkDescriptorBufferInfo BufferInfo = UniformDataBuffers[i]->DescriptorInfo();

			t3d::FDescriptorWriter(*GlobalDescriptorSetLayout, *DescriptorPool).WriteBuffer(0, &BufferInfo).Build(GlobalDescriptorSets[i]);
		}

		t3d::FMeshRenderSystem MeshRenderSystem(Device, Renderer.GetSwapchainRenderPass(), GlobalDescriptorSetLayout->GetDescriptorSetLayout());

		t3d::FPointLightRenderSystem PointLightRenderSystem(Device, Renderer.GetSwapchainRenderPass(), GlobalDescriptorSetLayout->GetDescriptorSetLayout());

		t3d::FCamera Camera;

		t3d::OGameObject ViewerObject;

		ViewerObject.GetTransform().SetTranslation({ 0.0f, 0.0f, -3.5f });

		t3d::CMovementComponent CameraController;

		std::chrono::high_resolution_clock::time_point CurrentTime = std::chrono::high_resolution_clock::now();

		while (!Window.ShouldClose())
		{
			Window.Update();

			t3d::FEventSystem::ProcessEvents();

			std::chrono::high_resolution_clock::time_point NewTime = std::chrono::high_resolution_clock::now();

			float32 FrameTime = std::chrono::duration<float32, std::chrono::seconds::period>(NewTime - CurrentTime).count();

			CurrentTime = NewTime;

			CameraController.MoveInPlaneXZ(Window, ViewerObject, FrameTime);

			Camera.SetViewYXZ(ViewerObject.GetTransform().GetTranslation(), ViewerObject.GetTransform().GetRotation());

			float32 AspectRatio = Renderer.GetAspectRation();

			Camera.SetPerspectiveProjection(glm::radians(50.0f), AspectRatio, 0.1f, 100.0f);

			if (VkCommandBuffer CommandBuffer = Renderer.BeginFrame())
			{
				uint32 FrameIndex = static_cast<uint32>(Renderer.GetFrameIndex());

				t3d::FFrameInfo FrameInfo{ FrameIndex, FrameTime, CommandBuffer, Camera, GlobalDescriptorSets[FrameIndex], GameObjects };

			// Update:

				t3d::FUniformBufferData UniformBufferData{};

				UniformBufferData.ProjectionMatrix = Camera.GetProjection();
				UniformBufferData.ViewMatrix       = Camera.GetView();

				PointLightRenderSystem.Update(FrameInfo, UniformBufferData);

				UniformDataBuffers[FrameIndex]->WriteToBuffer(&UniformBufferData);
				UniformDataBuffers[FrameIndex]->Flush();

			// Render:

				Renderer.BeginSwapchainRenderPass(CommandBuffer);

				MeshRenderSystem.Render(FrameInfo);
				PointLightRenderSystem.Render(FrameInfo);

				Renderer.EndSwapchainRenderPass(CommandBuffer);

				Renderer.EndFrame();
			}

			std::this_thread::sleep_for(std::chrono::microseconds(16600)); // ~60 FPS
		}

		vkDeviceWaitIdle(Device.Device());

		for (auto& UniformBuffer : UniformDataBuffers)
		{
			delete UniformBuffer;
		}

		delete GlobalDescriptorSetLayout;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		// ID generation depends on the first instance creation order,
		// but belongs to the type itself, not to instance.
		t3d::TestComponent qwe;
		t3d::TestComponent*  KLI = &qwe;
		t3d::TestComponent1* KLA = nullptr;
		t3d::TestComponent2* KLU = nullptr;

		t3d::LOG_TRACE("ID: " + std::to_string(t3d::TestComponent::ID));
		t3d::LOG_TRACE("ID_1: " + std::to_string(t3d::TestComponent1::ID));
		t3d::LOG_TRACE("ID_2: " + std::to_string(t3d::TestComponent2::ID));

		void* q = nullptr;

		std::vector<uint8> ComponentStorage;

		t3d::LOG_TRACE("Component storage size first: " + std::to_string(ComponentStorage.size()));

		ComponentStorage.reserve(48'000);

		t3d::LOG_TRACE("Component storage size after reserve: " + std::to_string(ComponentStorage.size()));

	//	t3d::ECSComponentCreate<t3d::TestComponent>(ComponentStorage, ENTITY_NULL_HANDLE, KLI);
		t3d::TestComponent::CreateFunction(ComponentStorage, ENTITY_NULL_HANDLE, KLI);

		t3d::LOG_TRACE("Component storage size after adding component: " + std::to_string(ComponentStorage.size()));

	//	t3d::ECSComponentFree<t3d::TestComponent>(KLI); // DOES NOT WORK???
		t3d::TestComponent::FreeFunction(KLI); // DOES NOT WORK???

		t3d::LOG_TRACE("Component storage size after destructing component: " + std::to_string(ComponentStorage.size()));

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	}

	void FApplication::Update()
	{
	}

	void FApplication::Render()
	{
	}


// Private Functions:

	void FApplication::LoadGameObjects()
	{
	// TEST

		Meshes.emplace("FlatVase"  , new t3d::FMesh(Device, "D:/VULKAN_TUTORIAL_SHADERS/Models/flat_vase.obj"));
		Meshes.emplace("SmoothVase", new t3d::FMesh(Device, "D:/VULKAN_TUTORIAL_SHADERS/Models/smooth_vase.obj"));
		Meshes.emplace("Floor"     , new t3d::FMesh(Device, "D:/VULKAN_TUTORIAL_SHADERS/Models/quad.obj"));

	// Flat vase:

		t3d::OGameObject FlatVase;

		FlatVase.Mesh = Meshes.at("FlatVase");
		FlatVase.GetTransform().SetTranslation({ -0.5f, 0.5f, 0.0f });
		FlatVase.GetTransform().SetScale({ 3.0f, 1.5f, 3.0f });

		GameObjects.emplace(FlatVase.GetID(), std::move(FlatVase));

	// Smooth vase:

		t3d::OGameObject SmoothVase;

		SmoothVase.Mesh = Meshes.at("SmoothVase");
		SmoothVase.GetTransform().SetTranslation({ 0.5f, 0.5f, 0.0f });
		SmoothVase.GetTransform().SetScale({ 3.0f, 1.5f, 3.0f });

		GameObjects.emplace(SmoothVase.GetID(), std::move(SmoothVase));

	// Quad:

		t3d::OGameObject Floor;
	
		Floor.Mesh = Meshes.at("Floor");
		Floor.GetTransform().SetTranslation({ 0.0f, 0.5f, 0.0f });
		Floor.GetTransform().SetScale({ 3.0f, 1.0f, 3.0f });
	
		GameObjects.emplace(Floor.GetID(), std::move(Floor));

	// Point light:
		
		std::vector<glm::vec3> LightColors
		{
			{ 1.0f, 0.1f, 0.1f },
			{ 0.1f, 0.1f, 1.0f },
			{ 0.1f, 1.0f, 0.1f },
			{ 1.0f, 1.0f, 0.1f },
			{ 0.1f, 1.0f, 1.0f },
			{ 1.0f, 1.0f, 1.0f }
		};
		
		for (uint64 i = 0u; i < LightColors.size(); i++)
		{
			t3d::OGameObject PointLight;
			
			PointLight.GetTransform().SetScale({ 0.05f, 0.0f, 0.0f });

			PointLight.LightIntensity = 0.5f;

			PointLight.Light = 1;

			PointLight.Color = LightColors[i];

			glm::mat4 RotationMatrix = glm::rotate(glm::mat4(1.0f), (i * glm::two_pi<float32>()) / LightColors.size(), { 0.0f, -1.0f, 0.0f });

			PointLight.GetTransform().SetTranslation( glm::vec3(RotationMatrix * glm::vec4(-1.0f, -1.0f, -1.0f, 1.0f)) );

			GameObjects.emplace(PointLight.GetID(), std::move(PointLight));
		}

		// Using point light again invalid...

//	// Paimon:
//
//		std::shared_ptr<t3d::FMesh> PaimonMesh = t3d::FMesh::CreateFromFile(Device, "D:/VULKAN_TUTORIAL_SHADERS/Models/paimon_ex.obj");
//
//		t3d::OGameObject Paimon = t3d::OGameObject::Create();
//
//		Paimon.Mesh = PaimonMesh;
//		Paimon.Transform.Translation = { 0.0f, -0.54f, 0.5f };
//		Paimon.Transform.Scale       = glm::vec3(0.2f);
//
//		GameObjects.emplace(Paimon.GetID(), std::move(Paimon));
	}

}

#pragma warning( pop ) // Vulkan SDK - End