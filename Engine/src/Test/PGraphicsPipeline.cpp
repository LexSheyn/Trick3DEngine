#include "../PrecompiledHeaders/t3dpch.h"
#include "PGraphicsPipeline.h"

namespace t3d
{
// Constructors and Destructor:

	PGraphicsPipeline::PGraphicsPipeline(FRenderer& Renderer)
		: IPipeline(Renderer)
	{
	}

	PGraphicsPipeline::~PGraphicsPipeline()
	{
		vkDeviceWaitIdle(Renderer.GetDevice().Device());

		// To do...
	}


// IPipeline Public Interface:

	void PGraphicsPipeline::Bind(VkCommandBuffer CommandBuffer)
	{
	}


// IPipeline Private Interface:

	void PGraphicsPipeline::CreateUniformBuffers()
	{
	}

	void PGraphicsPipeline::CreateDescriptors()
	{
	}

	void PGraphicsPipeline::CreatePipelineLayout()
	{
	}

	void PGraphicsPipeline::Configure()
	{
	}

	void PGraphicsPipeline::Create()
	{
	}


}