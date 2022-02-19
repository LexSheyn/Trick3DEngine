#include "../../PrecompiledHeaders/t3dpch.h"
#include "FRenderer.h"

// Disable warnings from Vulkan SDK:
#pragma warning( push ) // Vulkan SDK - Begin
#pragma warning( disable : 26812 ) // Uncoped Enum

namespace t3d
{
// Constructors and Destructor:

	FRenderer::FRenderer(FWindow& Window, FDevice& Device)
		: Window(Window),
		  Device(Device),
		  CurrentImageIndex(0u),
		  CurrentFrameIndex(0u),
		  IsFrameStarted(false)
	{
		this->CreateSwapchain();

		this->CreateCommandBuffers();

		LOG_TRACE("Created.");
	}

	FRenderer::~FRenderer()
	{
		this->FreeCommandBuffers();

		if (Swapchain)
		{
			delete Swapchain;
		}
	}


// Functions:

	VkCommandBuffer FRenderer::BeginFrame()
	{
		if (IsFrameStarted)
		{
			LOG_ERROR("Cannot call this function while already in progress!");
			throw;
		}

		VkResult Result = Swapchain->AcquireNextImage(&CurrentImageIndex);

		if (Result == VK_ERROR_OUT_OF_DATE_KHR)
		{
			this->RecreateSwapchain();

			return nullptr;
		}

		if (Result != VK_SUCCESS && Result != VK_SUBOPTIMAL_KHR)
		{
			LOG_ERROR("Failed to acquire next swapchain image!");
			throw;
		}

		IsFrameStarted = true;

		VkCommandBuffer CommandBuffer = this->GetCurrentCommandBuffer();

		VkCommandBufferBeginInfo BeginInfo{};

		BeginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

		if (vkBeginCommandBuffer(CommandBuffer, &BeginInfo) != VK_SUCCESS)
		{
			LOG_ERROR("Failed to begin recording command buffer!");
			throw;
		}

		return CommandBuffer;
	}

	void FRenderer::EndFrame()
	{
		if (!IsFrameStarted)
		{
			LOG_ERROR("Cannot call this function while frame is not in progress!");
			throw;
		}

		VkCommandBuffer CommandBuffer = this->GetCurrentCommandBuffer();

		if (vkEndCommandBuffer(CommandBuffer) != VK_SUCCESS)
		{
			LOG_ERROR("Failed to record command buffer!");
			throw;
		}

		VkResult Result = Swapchain->SubmitCommandBuffers(&CommandBuffer, &CurrentImageIndex);

		if (Result == VK_ERROR_OUT_OF_DATE_KHR || Result == VK_SUBOPTIMAL_KHR || Window.WasResized())
		{
			Window.ResetResizedFlag();

			this->RecreateSwapchain();
		}

		IsFrameStarted = false;

		CurrentFrameIndex = (CurrentFrameIndex + 1u) % FSwapchain::MAX_FRAMES_IN_FLIGHT;
	}

	void FRenderer::BeginSwapchainRenderPass(VkCommandBuffer CommandBuffer)
	{
		if (!IsFrameStarted)
		{
			LOG_ERROR("Cannot call this function while frame is not in progress!");
			throw;
		}

		if (CommandBuffer != this->GetCurrentCommandBuffer())
		{
			LOG_ERROR("Cannot begin render pass on command buffer from a different frame!");
			throw;
		}

	//	std::array<VkClearValue, 2> ClearValues{};
		TArray<VkClearValue, 2> ClearValues{};

		ClearValues[0].color        = { 0.01f, 0.01f, 0.01f, 1.0f };
		ClearValues[1].depthStencil = { 1.0f, 0u };

		VkRenderPassBeginInfo RenderPassBeginInfo{};

		RenderPassBeginInfo.sType       = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
		RenderPassBeginInfo.renderPass  = Swapchain->GetRenderPass();
		RenderPassBeginInfo.framebuffer = Swapchain->GetFramebuffer(CurrentImageIndex);

		RenderPassBeginInfo.renderArea.offset = { 0, 0 };
		RenderPassBeginInfo.renderArea.extent = Swapchain->GetSwapchainExtent();

		RenderPassBeginInfo.clearValueCount = static_cast<uint32>(ClearValues.Size());
		RenderPassBeginInfo.pClearValues    = ClearValues.Data();

		vkCmdBeginRenderPass(CommandBuffer, &RenderPassBeginInfo, VK_SUBPASS_CONTENTS_INLINE);

		VkViewport Viewport{};

		Viewport.x        = 0.0f;
		Viewport.y        = 0.0f;
		Viewport.width    = static_cast<float32>(Swapchain->GetSwapchainExtent().width);
		Viewport.height   = static_cast<float32>(Swapchain->GetSwapchainExtent().height);
		Viewport.minDepth = 0.0f;
		Viewport.maxDepth = 1.0f;
	
		VkRect2D Scissor{};

		Scissor.offset = { 0, 0 };
		Scissor.extent = Swapchain->GetSwapchainExtent();

		vkCmdSetViewport(CommandBuffer, 0, 1, &Viewport);
		vkCmdSetScissor(CommandBuffer, 0, 1, &Scissor);
	}

	void FRenderer::EndSwapchainRenderPass(VkCommandBuffer CommandBuffer)
	{
		if (!IsFrameStarted)
		{
			LOG_ERROR("Cannot call this function whilw frame is not in progress!");
			throw;
		}

		if (CommandBuffer != this->GetCurrentCommandBuffer())
		{
			LOG_ERROR("Cannot end render pass on command buffer from a different frame!");
			throw;
		}

		vkCmdEndRenderPass(CommandBuffer);
	}


// Private Functions:

	void FRenderer::CreateSwapchain()
	{
		VkExtent2D Extent = Window.GetExtent();

		while (Extent.width == 0 || Extent.height == 0)
		{
			Extent = Window.GetExtent();

			glfwWaitEvents();
		}

		vkDeviceWaitIdle(Device.Device());

		LOG_TRACE("Creating swapchain.");

		Swapchain = new FSwapchain(Device, Extent);
	}

	void FRenderer::RecreateSwapchain()
	{
		VkExtent2D Extent = Window.GetExtent();

		while (Extent.width == 0 || Extent.height == 0)
		{
			Extent = Window.GetExtent();

			glfwWaitEvents();
		}

		vkDeviceWaitIdle(Device.Device());

		FSwapchain* OldSwapchain = Swapchain;

		LOG_TRACE("Recreation swapchain.");

		Swapchain = new FSwapchain(Device, Extent, OldSwapchain);

		if (!OldSwapchain->HasEqualSwapFormats(*Swapchain))
		{
			LOG_ERROR("Swapchain image or depth format has changed!");
			throw;
		}

		LOG_TRACE("Deleting old swapchain.");

		delete OldSwapchain;
	}

	void FRenderer::CreateCommandBuffers()
	{
		CommandBuffers.resize(FSwapchain::MAX_FRAMES_IN_FLIGHT);

		VkCommandBufferAllocateInfo AllocateInfo{};

		AllocateInfo.sType              = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
		AllocateInfo.level              = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
		AllocateInfo.commandPool        = Device.GetCommandPool();
		AllocateInfo.commandBufferCount = static_cast<uint32>(CommandBuffers.size());

		if (vkAllocateCommandBuffers(Device.Device(), &AllocateInfo, CommandBuffers.data()) != VK_SUCCESS)
		{
			LOG_ERROR("Failed to allocate command buffers!");
			throw;
		}
	}

	void FRenderer::FreeCommandBuffers()
	{
		vkFreeCommandBuffers(Device.Device(), Device.GetCommandPool(), static_cast<uint32>(CommandBuffers.size()), CommandBuffers.data());
		
		CommandBuffers.clear();
	}

}

#pragma warning( pop ) // Vulkan SDK - End