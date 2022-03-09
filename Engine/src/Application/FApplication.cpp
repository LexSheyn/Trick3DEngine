#include "../PrecompiledHeaders/t3dpch.h"
#include "FApplication.h"

// Disable warnings from Vulkan SDK:
#pragma warning( push ) // Vulkan SDK - Begin
#pragma warning( disable : 26812 ) // Uncoped Enum

#include "../Components/CMovementComponent.h"

#include "../ECS/Core/SEntityComponentSystem.h"

namespace t3d
{
// Constructors and Destructor:

	FApplication::FApplication()
		: Width(800),
		  Height(600),
		  Window(Width, Height, "Trick 3D Engine"),
		  Device(Window),
		  Renderer(Window, Device)
	{
		DescriptorPool = FDescriptorPool::Constructor(Device)
			             .SetMaxSets(FSwapchain::MAX_FRAMES_IN_FLIGHT)
			             .AddPoolSize(VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, FSwapchain::MAX_FRAMES_IN_FLIGHT)
			             .Create();

		this->LoadGameObjects();
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
		std::vector<FDeviceBuffer*> UniformDataBuffers(FSwapchain::MAX_FRAMES_IN_FLIGHT);

		for (uint64 i = 0u; i < UniformDataBuffers.size(); i++)
		{
			UniformDataBuffers[i] = new FDeviceBuffer(Device,
				                                           sizeof(FUniformBufferData),
				                                           1,
				                                           VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT,
				                                           VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT); //| VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);

			UniformDataBuffers[i]->Map();
		}

		FDescriptorSetLayout* GlobalDescriptorSetLayout = FDescriptorSetLayout::Constructor(Device)
			                                                   .AddBinding(0, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, VK_SHADER_STAGE_ALL_GRAPHICS)
			                                                   .Create();

		std::vector<VkDescriptorSet> GlobalDescriptorSets(FSwapchain::MAX_FRAMES_IN_FLIGHT); // Cleaned up automatically, but it is not be the case in the future!

		for (uint64 i = 0u; i < GlobalDescriptorSets.size(); i++)
		{
			VkDescriptorBufferInfo BufferInfo = UniformDataBuffers[i]->DescriptorInfo();

			FDescriptorWriter(*GlobalDescriptorSetLayout, *DescriptorPool).WriteBuffer(0, &BufferInfo).Build(GlobalDescriptorSets[i]);
		}
	}

	void FApplication::Run()
	{
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 			   ECS
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		FEntity* Entity_1 = SEntityComponentSystem::CreateEntity();

		SEntityComponentSystem::AddComponent<CName>(Entity_1);
		SEntityComponentSystem::AddComponent<CTransform>(Entity_1);
		SEntityComponentSystem::AddComponent<CHealth>(Entity_1);
		SEntityComponentSystem::AddComponent<CEnergy>(Entity_1);

		LOG_TRACE(SEntityComponentSystem::GetComponent<CName>(Entity_1)->Name);

		SEntityComponentSystem::GetComponent<CName>(Entity_1)->Name = "Changed Name";

		LOG_TRACE(SEntityComponentSystem::GetComponent<CName>(Entity_1)->Name);

		SEntityComponentSystem::RemoveEntity(Entity_1);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		std::vector<FDeviceBuffer*> UniformDataBuffers(FSwapchain::MAX_FRAMES_IN_FLIGHT);

		for (uint64 i = 0u; i < UniformDataBuffers.size(); i++)
		{
			UniformDataBuffers[i] = new FDeviceBuffer(Device,
				                                           sizeof(FUniformBufferData),
				                                           1,
				                                           VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT,
				                                           VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT); //| VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);

			UniformDataBuffers[i]->Map();
		}

		FDescriptorSetLayout* GlobalDescriptorSetLayout = FDescriptorSetLayout::Constructor(Device)
			                                                   .AddBinding(0, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, VK_SHADER_STAGE_ALL_GRAPHICS)
			                                                   .Create();

		std::vector<VkDescriptorSet> GlobalDescriptorSets(FSwapchain::MAX_FRAMES_IN_FLIGHT); // Cleaned up automatically, but it is not be the case in the future!

		for (uint64 i = 0u; i < GlobalDescriptorSets.size(); i++)
		{
			VkDescriptorBufferInfo BufferInfo = UniformDataBuffers[i]->DescriptorInfo();

			FDescriptorWriter(*GlobalDescriptorSetLayout, *DescriptorPool).WriteBuffer(0, &BufferInfo).Build(GlobalDescriptorSets[i]);
		}

		FMeshRenderSystem MeshRenderSystem(Device, Renderer.GetSwapchainRenderPass(), GlobalDescriptorSetLayout->GetDescriptorSetLayout());

		FPointLightRenderSystem PointLightRenderSystem(Device, Renderer.GetSwapchainRenderPass(), GlobalDescriptorSetLayout->GetDescriptorSetLayout());

		FCamera Camera;

		OGameObject ViewerObject;

		ViewerObject.GetTransform().SetTranslation({ 0.0f, 0.0f, -3.5f });

		CMovementComponent CameraController;

		std::chrono::steady_clock::time_point CurrentTime = std::chrono::steady_clock::now();

		while (!Window.ShouldClose())
		{
			Window.Update();

			SEventSystem::ProcessEvents();

			std::chrono::steady_clock::time_point NewTime = std::chrono::steady_clock::now();

			float32 FrameTime = std::chrono::duration<float32, std::chrono::seconds::period>(NewTime - CurrentTime).count();

			CurrentTime = NewTime;

			CameraController.MoveInPlaneXZ(Window, ViewerObject, FrameTime);

			Camera.SetViewYXZ(ViewerObject.GetTransform().GetTranslation(), ViewerObject.GetTransform().GetRotation());

			float32 AspectRatio = Renderer.GetAspectRation();

			Camera.SetPerspectiveProjection(glm::radians(50.0f), AspectRatio, 0.1f, 100.0f);

			if (VkCommandBuffer CommandBuffer = Renderer.BeginFrame())
			{
				uint32 FrameIndex = static_cast<uint32>(Renderer.GetFrameIndex());

				FFrameInfo FrameInfo{ FrameIndex, FrameTime, CommandBuffer, Camera, GlobalDescriptorSets[FrameIndex], GameObjects };

			// Update:

				FUniformBufferData UniformBufferData{};

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

		Meshes.emplace("FlatVase"  , new FMesh(Device, "D:/VULKAN_TUTORIAL_SHADERS/Models/flat_vase.obj"));
		Meshes.emplace("SmoothVase", new FMesh(Device, "D:/VULKAN_TUTORIAL_SHADERS/Models/smooth_vase.obj"));
		Meshes.emplace("Floor"     , new FMesh(Device, "D:/VULKAN_TUTORIAL_SHADERS/Models/quad.obj"));

	// Flat vase:

		OGameObject FlatVase;

		FlatVase.Mesh = Meshes.at("FlatVase");
		FlatVase.GetTransform().SetTranslation({ -0.5f, 0.5f, 0.0f });
		FlatVase.GetTransform().SetScale({ 3.0f, 1.5f, 3.0f });

		GameObjects.emplace(FlatVase.GetID(), std::move(FlatVase));

	// Smooth vase:

		OGameObject SmoothVase;

		SmoothVase.Mesh = Meshes.at("SmoothVase");
		SmoothVase.GetTransform().SetTranslation({ 0.5f, 0.5f, 0.0f });
		SmoothVase.GetTransform().SetScale({ 3.0f, 1.5f, 3.0f });

		GameObjects.emplace(SmoothVase.GetID(), std::move(SmoothVase));

	// Quad:

		OGameObject Floor;
	
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
			OGameObject PointLight;
			
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
//		std::shared_ptr<FMesh> PaimonMesh = FMesh::CreateFromFile(Device, "D:/VULKAN_TUTORIAL_SHADERS/Models/paimon_ex.obj");
//
//		OGameObject Paimon = OGameObject::Create();
//
//		Paimon.Mesh = PaimonMesh;
//		Paimon.Transform.Translation = { 0.0f, -0.54f, 0.5f };
//		Paimon.Transform.Scale       = glm::vec3(0.2f);
//
//		GameObjects.emplace(Paimon.GetID(), std::move(Paimon));
	}

}

#pragma warning( pop ) // Vulkan SDK - End