#include "../../PCH/t3dpch.h"
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

		Viewports.emplace_back(VkViewport{});
		Scissors.emplace_back(VkRect2D{});

		SEvent::Trace.Invoke({ FTimeStamp(), T3D_FUNCTION, "Created." });
	}

	FRenderer::~FRenderer()
	{
		vkDeviceWaitIdle(Device.Device());

		this->FreeCommandBuffers();

		if (Swapchain)
		{
			delete Swapchain;
		}

		SEvent::Trace.Invoke({ FTimeStamp(), T3D_FUNCTION, "Deleted." });
	}


// Functions:

	void FRenderer::BeginFrame()
	{
		if (IsFrameStarted)
		{
			SEvent::Error.Invoke({ FTimeStamp(), T3D_FUNCTION, "Cannot call this function while frame already in progress!" });
			throw;
		}

		VkResult Result = Swapchain->AcquireNextImage(&CurrentImageIndex);

		if (Result == VK_ERROR_OUT_OF_DATE_KHR)
		{
			this->RecreateSwapchain();
		}

		if (Result != VK_SUCCESS && Result != VK_SUBOPTIMAL_KHR)
		{
			SEvent::Error.Invoke({ FTimeStamp(), T3D_FUNCTION, "Failed to acquire next swapchain image!" });
			throw;
		}

		IsFrameStarted = true;

		VkCommandBufferBeginInfo BeginInfo{};

		BeginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

		if (vkBeginCommandBuffer(this->GetCurrentCommandBuffer(), &BeginInfo) != VK_SUCCESS)
		{
			SEvent::Error.Invoke({ FTimeStamp(), T3D_FUNCTION, "Failed to begin recording command buffer!" });
			throw;
		}
	}

	void FRenderer::EndFrame()
	{
		if (!IsFrameStarted)
		{
			SEvent::Error.Invoke({ FTimeStamp(), T3D_FUNCTION, "Cannot call this function while frame is not in progress!" });
			throw;
		}

		VkCommandBuffer CommandBuffer = this->GetCurrentCommandBuffer();

		if (vkEndCommandBuffer(CommandBuffer) != VK_SUCCESS)
		{
			SEvent::Error.Invoke({ FTimeStamp(), T3D_FUNCTION, "Failed to record command buffer!" });
			throw;
		}

		VkResult Result = Swapchain->SubmitCommandBuffers(&CommandBuffer, &CurrentImageIndex);

		if (Result == VK_ERROR_OUT_OF_DATE_KHR || Result == VK_SUBOPTIMAL_KHR || Window.WasResized())
		{
			Window.ResetResizedFlag();

			this->RecreateSwapchain();
		}

		IsFrameStarted = false;

		CurrentFrameIndex = (CurrentFrameIndex + 1u) % FSwapchain::MaxFramesInFlight;
	}

	void FRenderer::BeginSwapchainRenderPass()
	{
		if (!IsFrameStarted)
		{
			SEvent::Error.Invoke({ FTimeStamp(), T3D_FUNCTION, "Cannot call this function while frame is not in progress!" });
			throw;
		}

		VkCommandBuffer CommandBuffer = this->GetCurrentCommandBuffer();

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

		Viewports.front().x        = 0.0f;
		Viewports.front().y        = 0.0f;
		Viewports.front().width    = static_cast<float32>(Swapchain->GetSwapchainExtent().width);
		Viewports.front().height   = static_cast<float32>(Swapchain->GetSwapchainExtent().height);
		Viewports.front().minDepth = 0.0f;
		Viewports.front().maxDepth = 1.0f;

		Scissors.front().offset = { 0, 0 };
		Scissors.front().extent = Swapchain->GetSwapchainExtent();

		vkCmdSetViewport(CommandBuffer, 0, 1, &Viewports.front());
		vkCmdSetScissor (CommandBuffer, 0, 1, &Scissors.front());
	}

	void FRenderer::EndSwapchainRenderPass()
	{
		if (!IsFrameStarted)
		{
			SEvent::Error.Invoke({ FTimeStamp(), T3D_FUNCTION, "Cannot call this function while frame is not in progress!" });
			throw;
		}

		vkCmdEndRenderPass(this->GetCurrentCommandBuffer());
	}


// Accessprs:

	const bool8& FRenderer::IsFrameInProgress() const
	{
		return IsFrameStarted;
	}

	VkCommandBuffer FRenderer::GetCurrentCommandBuffer() const
	{
		if (!IsFrameStarted)
		{
			SEvent::Error.Invoke({ FTimeStamp(), T3D_FUNCTION, "Cannot get command buffer while frame not in progress!" });
			throw;
		}

		return CommandBuffers[CurrentFrameIndex];
	}

	VkRenderPass FRenderer::GetSwapchainRenderPass() const
	{
		return Swapchain->GetRenderPass();
	}

	float32 FRenderer::GetAspectRatio() const
	{
		return Swapchain->GetExtentAspectRatio();
	}

	const uint64& FRenderer::GetFrameIndex() const
	{
		if (!IsFrameStarted)
		{
			SEvent::Error.Invoke({ FTimeStamp(), T3D_FUNCTION, "Cannot get frame index while frame not in progress!" });
			throw;
		}

		return CurrentFrameIndex;
	}

	FDevice& FRenderer::GetDevice() const
	{
		return Device;
	}

	std::vector<VkViewport>& FRenderer::GetViewports()
	{
		return Viewports;
	}

	std::vector<VkRect2D>& FRenderer::GetScissors()
	{
		return Scissors;
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

		SEvent::Trace.Invoke({ FTimeStamp(), T3D_FUNCTION, "Creating swapchain." });

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

		SEvent::Trace.Invoke({ FTimeStamp(), T3D_FUNCTION, "Recreating swapchain." });

		Swapchain = new FSwapchain(Device, Extent, OldSwapchain);

		if (!OldSwapchain->HasEqualSwapFormats(*Swapchain))
		{
			SEvent::Error.Invoke({ FTimeStamp(), T3D_FUNCTION, "Swapchain image or depth format has changed!" });
			throw;
		}

		SEvent::Trace.Invoke({ FTimeStamp(), T3D_FUNCTION, "Deleting old swapchain." });

		delete OldSwapchain;
	}

	void FRenderer::CreateCommandBuffers()
	{
		CommandBuffers.resize(FSwapchain::MaxFramesInFlight);

		VkCommandBufferAllocateInfo AllocateInfo{};

		AllocateInfo.sType              = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
		AllocateInfo.level              = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
		AllocateInfo.commandPool        = Device.GetCommandPool();
		AllocateInfo.commandBufferCount = static_cast<uint32>(CommandBuffers.size());

		if (vkAllocateCommandBuffers(Device.Device(), &AllocateInfo, CommandBuffers.data()) != VK_SUCCESS)
		{
			SEvent::Error.Invoke({ FTimeStamp(), T3D_FUNCTION, "Failed to allocate command buffers!" });
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