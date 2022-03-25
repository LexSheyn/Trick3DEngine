#include "../PrecompiledHeaders/t3dpch.h"
#include "IPipeline.h"

// Disable warnings from Vulkan SDK:
#pragma warning( push ) // Vulkan SDK - Begin
#pragma warning( disable : 26812 ) // Uncoped Enum

namespace t3d
{
// Constructors and Destructor:

	IPipeline::IPipeline(FRenderer& Renderer)
		: Renderer(Renderer),
		  PipelineLayout(VK_NULL_HANDLE),
		  VulkanPipeline(VK_NULL_HANDLE)
	{
		LOG_TRACE("Created.");
	}

	IPipeline::~IPipeline()
	{
		vkDeviceWaitIdle(Renderer.GetDevice().Device());

		vkDestroyPipelineLayout(Renderer.GetDevice().Device(), PipelineLayout, nullptr);

		vkDestroyPipeline(Renderer.GetDevice().Device(), VulkanPipeline, nullptr);

		LOG_TRACE("Deleted.");
	}

}

#pragma warning( pop ) // Vulkan SDK - End