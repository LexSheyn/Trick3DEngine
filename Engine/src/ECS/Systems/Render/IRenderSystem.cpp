#include "../../../PrecompiledHeaders/t3dpch.h"
#include "IRenderSystem.h"

namespace t3d
{
// Constructors and Destructor:

	IRenderSystem::IRenderSystem(FRenderer& Renderer)
		: Renderer(Renderer)
	{
		this->Initialize();

		LOG_TRACE("Created.");
	}

	IRenderSystem::~IRenderSystem()
	{
		delete DescriptorPool;

		delete DescriptorSetLayout;

		delete Pipeline;

		vkDestroyPipelineLayout(Renderer.GetDevice().Device(), PipelineLayout, nullptr);

		LOG_TRACE("Deleted.");
	}


// Private Functions:

	void IRenderSystem::Initialize()
	{
		PipelineLayout = nullptr;

		Pipeline = nullptr;

		for (uint64 i = 0u; i < DescriptorSets.Size(); i++)
		{
			DescriptorSets[i] = nullptr;
		}

		DescriptorSetLayout = nullptr;

		DescriptorPool = nullptr;
	}

}