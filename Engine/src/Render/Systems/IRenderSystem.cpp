#include "../../PrecompiledHeaders/t3dpch.h"
#include "IRenderSystem.h"

namespace t3d
{
// Constructors and Destructor:

	IRenderSystem::IRenderSystem(FDevice& Device, FRenderer& Renderer)
		: Device(Device),
		  Renderer(Renderer)
	{
		this->Initialize();

		LOG_TRACE("Created.");
	}

	IRenderSystem::~IRenderSystem()
	{
		delete DescriptorPool;

		delete DescriptorSetLayout;

		for (uint64 i = 0u; i < UniformBuffers.Size(); i++)
		{
			delete UniformBuffers[i];
		}

		delete Pipeline;

		vkDestroyPipelineLayout(Device.Device(), PipelineLayout, nullptr);

		LOG_TRACE("Deleted.");
	}


// Private Functions:

	void IRenderSystem::Initialize()
	{
		PipelineLayout = nullptr;

		Pipeline = nullptr;

		for (uint64 i = 0u; i < UniformBuffers.Size(); i++)
		{
			UniformBuffers[i] = nullptr;
		}

		for (uint64 i = 0u; i < DescriptorSets.Size(); i++)
		{
			DescriptorSets[i] = nullptr;
		}

		DescriptorSetLayout = nullptr;

		DescriptorPool = nullptr;
	}

}