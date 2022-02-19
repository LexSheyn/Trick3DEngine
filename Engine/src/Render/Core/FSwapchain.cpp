#include "../../PrecompiledHeaders/t3dpch.h"
#include "FSwapchain.h"

// Disable warnings from Vulkan SDK:
#pragma warning( push ) // Vulkan SDK - Begin
#pragma warning( disable : 26812 ) // Uncoped Enum

namespace t3d
{
// Constructors and Destructor:

	FSwapchain::FSwapchain(FDevice& Device, VkExtent2D WindowExtent)
		: Device(Device), WindowExtent(WindowExtent)
	{
		this->Init();

		LOG_TRACE("Created.");
	}

	FSwapchain::FSwapchain(FDevice& Device, VkExtent2D WindowExtent, FSwapchain* PreviousSwapchain)
		: Device(Device), WindowExtent(WindowExtent), OldSwapchain(PreviousSwapchain)
	{
		this->Init();

	// Clean up old swapchain since it is no longer needed.

	//	if (OldSwapchain)
	//	{
	//		delete OldSwapchain;
	//	}

		LOG_TRACE("Created.");
	}

	FSwapchain::~FSwapchain()
	{
		for (auto ImageView : SwapchainImageViews)
		{
			vkDestroyImageView(Device.Device(), ImageView, nullptr);
		}
		SwapchainImageViews.clear();

		if (Swapchain != nullptr)
		{
			vkDestroySwapchainKHR(Device.Device(), Swapchain, nullptr);

			Swapchain = nullptr;
		}

		for (size_t i = 0u; i < DepthImages.size(); i++)
		{
			vkDestroyImageView(Device.Device(), DepthImageViews[i], nullptr);

			vkDestroyImage(Device.Device(), DepthImages[i], nullptr);
			
			vkFreeMemory(Device.Device(), DepthImageMemorys[i], nullptr);
		}

		for (auto FrameBuffer : SwapchainFramebuffers)
		{
			vkDestroyFramebuffer(Device.Device(), FrameBuffer, nullptr);
		}

		vkDestroyRenderPass(Device.Device(), RenderPass, nullptr);

	// Cleanup synctonisation objects:

		for (size_t i = 0u; i < MAX_FRAMES_IN_FLIGHT; i++)
		{
			vkDestroySemaphore(Device.Device(), RenderFinishedSemaphores[i], nullptr);
			
			vkDestroySemaphore(Device.Device(), ImageAvailableSemaphores[i], nullptr);

			vkDestroyFence(Device.Device(), InFlightFences[i], nullptr);
		}

		LOG_TRACE("Deleted.");
	}


// Functions:

	VkFormat FSwapchain::FindDepthFormat()
	{
		return Device.FindSupportedFormat({ VK_FORMAT_D32_SFLOAT, VK_FORMAT_D32_SFLOAT_S8_UINT, VK_FORMAT_D24_UNORM_S8_UINT }, VK_IMAGE_TILING_OPTIMAL, VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT);
	}

	VkResult FSwapchain::AcquireNextImage(uint32* ImageIndex)
	{
		vkWaitForFences(Device.Device(), 1, &InFlightFences[CurrentFrame], VK_TRUE, UINT64_MAX);

		VkResult Result = vkAcquireNextImageKHR(Device.Device(), Swapchain, UINT64_MAX, ImageAvailableSemaphores[CurrentFrame], VK_NULL_HANDLE, ImageIndex);

		return Result;
	}

	VkResult FSwapchain::SubmitCommandBuffers(const VkCommandBuffer* CommandBuffers, uint32* ImageIndex)
	{
		if (ImagesInFlight[*ImageIndex] != VK_NULL_HANDLE)
		{
			vkWaitForFences(Device.Device(), 1, &ImagesInFlight[*ImageIndex], VK_TRUE, UINT64_MAX);
		}

		ImagesInFlight[*ImageIndex] = InFlightFences[CurrentFrame];

		VkSemaphore WaitSemaphores[] = { ImageAvailableSemaphores[CurrentFrame] };

		VkPipelineStageFlags WaitStages[] = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };

		VkSemaphore SignalSemaphores[] = { RenderFinishedSemaphores[CurrentFrame] };

		VkSubmitInfo SubmitInfo{};

		SubmitInfo.sType                = VK_STRUCTURE_TYPE_SUBMIT_INFO;
		SubmitInfo.waitSemaphoreCount   = 1;
		SubmitInfo.pWaitSemaphores      = WaitSemaphores;
		SubmitInfo.pWaitDstStageMask    = WaitStages;
		SubmitInfo.commandBufferCount   = 1;
		SubmitInfo.pCommandBuffers      = CommandBuffers;
		SubmitInfo.signalSemaphoreCount = 1;
		SubmitInfo.pSignalSemaphores    = SignalSemaphores;

		vkResetFences(Device.Device(), 1, &InFlightFences[CurrentFrame]);

		if (vkQueueSubmit(Device.GetGraphicsQueue(), 1, &SubmitInfo, InFlightFences[CurrentFrame]) != VK_SUCCESS)
		{
			LOG_ERROR("Failed to submit draw command buffer!");
			throw;
		}

		VkSwapchainKHR Swapchains[] = { Swapchain };

		VkPresentInfoKHR PresentInfo{};

		PresentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
		PresentInfo.waitSemaphoreCount = 1;
		PresentInfo.pWaitSemaphores = SignalSemaphores;
		PresentInfo.swapchainCount = 1;
		PresentInfo.pSwapchains = Swapchains;
		PresentInfo.pImageIndices = ImageIndex;

		VkResult Result = vkQueuePresentKHR(Device.GetPresentQueue(), &PresentInfo);

		CurrentFrame = (CurrentFrame + 1u) % MAX_FRAMES_IN_FLIGHT;

		return Result;
	}


// Private Functions:

	void FSwapchain::Init()
	{
		this->CreateSwapchain();

		this->CreateImageViews();

		this->CreateRenderPass();

		this->CreateDepthResources();

		this->CreateFramebuffers();

		this->CreateSyncObjects();
	}

	void FSwapchain::CreateSwapchain()
	{
		FSwapchainSupportDetails SwapchainSupport = Device.GetSwapchainSupportDetails();

		VkSurfaceFormatKHR SurfaceFormat = this->ChooseSwapSurfaceFormat(SwapchainSupport.Formats);
		
		VkPresentModeKHR PresentMode = this->ChooseSwapPresentMode(SwapchainSupport.PresentModes);
		
		VkExtent2D Extent = this->ChooseSwapExtent(SwapchainSupport.Capabilities);

		uint32 ImageCount = SwapchainSupport.Capabilities.minImageCount + 1u;

		if (SwapchainSupport.Capabilities.maxImageCount > 0u && ImageCount > SwapchainSupport.Capabilities.maxImageCount)
		{
			ImageCount = SwapchainSupport.Capabilities.maxImageCount;
		}

		VkSwapchainCreateInfoKHR CreateInfo{};

		CreateInfo.sType            = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
		CreateInfo.surface          = Device.GetSurface();
		CreateInfo.minImageCount    = ImageCount;
		CreateInfo.imageFormat      = SurfaceFormat.format;
		CreateInfo.imageColorSpace  = SurfaceFormat.colorSpace;
		CreateInfo.imageExtent      = Extent;
		CreateInfo.imageArrayLayers = 1;
		CreateInfo.imageUsage       = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

		FQueueFamilyIndices Indices = Device.FindPhysicalQueueFamilies();

		uint32 QueueFamilyIndices[] = { static_cast<uint32>(Indices.GraphicsFamily), static_cast<uint32>(Indices.PresentFamily) };

		if (Indices.GraphicsFamily != Indices.PresentFamily)
		{
			CreateInfo.imageSharingMode      = VK_SHARING_MODE_CONCURRENT;
			CreateInfo.queueFamilyIndexCount = 2;
			CreateInfo.pQueueFamilyIndices   = QueueFamilyIndices;
		}
		else
		{
			CreateInfo.imageSharingMode      = VK_SHARING_MODE_EXCLUSIVE;
			CreateInfo.queueFamilyIndexCount = 0;       // Optional.
			CreateInfo.pQueueFamilyIndices   = nullptr; // Optional.
		}

		CreateInfo.preTransform   = SwapchainSupport.Capabilities.currentTransform;
		CreateInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
		CreateInfo.presentMode    = PresentMode;
		CreateInfo.clipped        = VK_TRUE;
		CreateInfo.oldSwapchain   = OldSwapchain == nullptr ? VK_NULL_HANDLE : OldSwapchain->Swapchain;

		if (vkCreateSwapchainKHR(Device.Device(), &CreateInfo, nullptr, &Swapchain) != VK_SUCCESS)
		{
			LOG_ERROR("Failed to create swapchain!");
			throw;
		}

	// We only specified a minimum number of images in the swapchain, sp the implementation is
	// allowed to create a swapchain with more. That's why we will first query the final number of
	// images with vkGetSwapchainImagesKHR(...), then resize the container and finally call it again to
	// retrieve the handles.

		vkGetSwapchainImagesKHR(Device.Device(), Swapchain, &ImageCount, nullptr);

		SwapchainImages.resize(ImageCount);

		vkGetSwapchainImagesKHR(Device.Device(), Swapchain, &ImageCount, SwapchainImages.data());

		SwapchainImageFormat = SurfaceFormat.format;
		
		SwapchainExtent = Extent;
	}

	void FSwapchain::CreateImageViews()
	{
		SwapchainImageViews.resize(SwapchainImages.size());

		for (size_t i = 0u; i < SwapchainImages.size(); i++)
		{
			VkImageViewCreateInfo ImageViewInfo{};

			ImageViewInfo.sType    = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
			ImageViewInfo.image    = SwapchainImages[i];
			ImageViewInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
			ImageViewInfo.format   = SwapchainImageFormat;

			ImageViewInfo.subresourceRange.aspectMask     = VK_IMAGE_ASPECT_COLOR_BIT;
			ImageViewInfo.subresourceRange.baseMipLevel   = 0;
			ImageViewInfo.subresourceRange.levelCount     = 1;
			ImageViewInfo.subresourceRange.baseArrayLayer = 0;
			ImageViewInfo.subresourceRange.layerCount     = 1;

			if (vkCreateImageView(Device.Device(), &ImageViewInfo, nullptr, &SwapchainImageViews[i]) != VK_SUCCESS)
			{
				LOG_ERROR("Failed to create texture image view!");
				throw;
			}
		}
	}

	void FSwapchain::CreateDepthResources()
	{
		SwapchainDepthFormat = this->FindDepthFormat();

		VkExtent2D SwapchainExtent = this->GetSwapchainExtent();

		DepthImages.resize(this->GetImageCount());

		DepthImageMemorys.resize(this->GetImageCount());

		DepthImageViews.resize(this->GetImageCount());

		for (size_t i = 0u; i < DepthImages.size(); i++)
		{
			VkImageCreateInfo ImageInfo{};

			ImageInfo.sType         = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
			ImageInfo.imageType     = VK_IMAGE_TYPE_2D;
			ImageInfo.extent.width  = SwapchainExtent.width;
			ImageInfo.extent.height = SwapchainExtent.height;
			ImageInfo.extent.depth  = 1;
			ImageInfo.mipLevels     = 1;
			ImageInfo.arrayLayers   = 1;
			ImageInfo.format        = SwapchainDepthFormat;
			ImageInfo.tiling        = VK_IMAGE_TILING_OPTIMAL;
			ImageInfo.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
			ImageInfo.usage         = VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT;
			ImageInfo.samples       = VK_SAMPLE_COUNT_1_BIT;
			ImageInfo.sharingMode   = VK_SHARING_MODE_EXCLUSIVE;
			ImageInfo.flags         = 0;

			Device.CreateImageWithInfo(ImageInfo, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, DepthImages[i], DepthImageMemorys[i]);

			VkImageViewCreateInfo ImageViewInfo{};

			ImageViewInfo.sType    = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
			ImageViewInfo.image    = DepthImages[i];
			ImageViewInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
			ImageViewInfo.format   = SwapchainDepthFormat;

			ImageViewInfo.subresourceRange.aspectMask     = VK_IMAGE_ASPECT_DEPTH_BIT;
			ImageViewInfo.subresourceRange.baseMipLevel   = 0;
			ImageViewInfo.subresourceRange.levelCount     = 1;
			ImageViewInfo.subresourceRange.baseArrayLayer = 0;
			ImageViewInfo.subresourceRange.layerCount     = 1;

			if (vkCreateImageView(Device.Device(), &ImageViewInfo, nullptr, &DepthImageViews[i]) != VK_SUCCESS)
			{
				LOG_ERROR("Failed to create texture image view!");
				throw;
			}
		}
	}

	void FSwapchain::CreateRenderPass()
	{
		VkAttachmentDescription DepthAttachment{};

		DepthAttachment.format         = this->FindDepthFormat();
		DepthAttachment.samples        = VK_SAMPLE_COUNT_1_BIT;
		DepthAttachment.loadOp         = VK_ATTACHMENT_LOAD_OP_CLEAR;
		DepthAttachment.storeOp        = VK_ATTACHMENT_STORE_OP_DONT_CARE;
		DepthAttachment.stencilLoadOp  = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
		DepthAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
		DepthAttachment.initialLayout  = VK_IMAGE_LAYOUT_UNDEFINED;
		DepthAttachment.finalLayout    = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

		VkAttachmentReference DepthAttachmentReference{};

		DepthAttachmentReference.attachment = 1;
		DepthAttachmentReference.layout     = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

		VkAttachmentDescription ColorAttachment{};

		ColorAttachment.format         = this->GetSwapchainImageFormat();
		ColorAttachment.samples        = VK_SAMPLE_COUNT_1_BIT;
		ColorAttachment.loadOp         = VK_ATTACHMENT_LOAD_OP_CLEAR;
		ColorAttachment.storeOp        = VK_ATTACHMENT_STORE_OP_STORE;
		ColorAttachment.stencilLoadOp  = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
		ColorAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
		ColorAttachment.initialLayout  = VK_IMAGE_LAYOUT_UNDEFINED;
		ColorAttachment.finalLayout    = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

		VkAttachmentReference ColorAttachmentReference{};

		ColorAttachmentReference.attachment = 0;
		ColorAttachmentReference.layout     = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

		VkSubpassDescription Subpass{};

		Subpass.pipelineBindPoint       = VK_PIPELINE_BIND_POINT_GRAPHICS;
		Subpass.colorAttachmentCount    = 1;
		Subpass.pColorAttachments       = &ColorAttachmentReference;
		Subpass.pDepthStencilAttachment = &DepthAttachmentReference;

		VkSubpassDependency Dependency{};

		Dependency.srcSubpass    = VK_SUBPASS_EXTERNAL;
		Dependency.srcAccessMask = 0;
		Dependency.srcStageMask  = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT | VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT;
		Dependency.dstSubpass    = 0;
		Dependency.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT | VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;
		Dependency.dstStageMask  = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT | VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT;
		
	//	std::array<VkAttachmentDescription, 2> Attachments = { ColorAttachment, DepthAttachment };
		TArray<VkAttachmentDescription, 2> Attachments{};// = { ColorAttachment, DepthAttachment };
		Attachments[0] = ColorAttachment;
		Attachments[1] = DepthAttachment;

		VkRenderPassCreateInfo RenderPassInfo{};

		RenderPassInfo.sType           = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
		RenderPassInfo.attachmentCount = static_cast<uint32>(Attachments.Size());
		RenderPassInfo.pAttachments    = Attachments.Data();
		RenderPassInfo.subpassCount    = 1;
		RenderPassInfo.pSubpasses      = &Subpass;
		RenderPassInfo.dependencyCount = 1;
		RenderPassInfo.pDependencies   = &Dependency;

		if (vkCreateRenderPass(Device.Device(), &RenderPassInfo, nullptr, &RenderPass) != VK_SUCCESS)
		{
			LOG_ERROR("Failed to create render pass!");
			throw;
		}
	}

	void FSwapchain::CreateFramebuffers()
	{
		SwapchainFramebuffers.resize(this->GetImageCount());

		for (size_t i = 0u; i < this->GetImageCount(); i++)
		{
		//	std::array<VkImageView, 2> Attachments = { SwapchainImageViews[i], DepthImageViews[i] };
			TArray<VkImageView, 2> Attachments{};

			Attachments[0] = SwapchainImageViews[i];
			Attachments[1] = DepthImageViews[i];

			VkExtent2D SwapchainExtent = this->GetSwapchainExtent();

			VkFramebufferCreateInfo FramebufferInfo{};

			FramebufferInfo.sType           = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
			FramebufferInfo.renderPass      = RenderPass;
			FramebufferInfo.attachmentCount = static_cast<uint32>(Attachments.Size());
			FramebufferInfo.pAttachments    = Attachments.Data();
			FramebufferInfo.width           = SwapchainExtent.width;
			FramebufferInfo.height          = SwapchainExtent.height;
			FramebufferInfo.layers          = 1;

			if (vkCreateFramebuffer(Device.Device(), &FramebufferInfo, nullptr, &SwapchainFramebuffers[i]) != VK_SUCCESS)
			{
				LOG_ERROR("Failed to create framebuffer!");
				throw;
			}
		}
	}

	void FSwapchain::CreateSyncObjects()
	{
		ImageAvailableSemaphores.resize(MAX_FRAMES_IN_FLIGHT);
		RenderFinishedSemaphores.resize(MAX_FRAMES_IN_FLIGHT);
		InFlightFences.resize(MAX_FRAMES_IN_FLIGHT);
		ImagesInFlight.resize(this->GetImageCount(), VK_NULL_HANDLE);

		VkSemaphoreCreateInfo SemaphoreInfo{};

		SemaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

		VkFenceCreateInfo FenceInfo{};

		FenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
		FenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

		for (size_t i = 0u; i < MAX_FRAMES_IN_FLIGHT; i++)
		{
			if (vkCreateSemaphore(Device.Device(), &SemaphoreInfo, nullptr, &ImageAvailableSemaphores[i]) != VK_SUCCESS)
			{
				LOG_ERROR("Failed to create semaphore for image available signal!");
				throw;
			}

			if (vkCreateSemaphore(Device.Device(), &SemaphoreInfo, nullptr, &RenderFinishedSemaphores[i]) != VK_SUCCESS)
			{
				LOG_ERROR("Failed to create semaphore for render finished signal!");
				throw;
			}

			if (vkCreateFence(Device.Device(), &FenceInfo, nullptr, &InFlightFences[i]) != VK_SUCCESS)
			{
				LOG_ERROR("Failed to create fence for a frame!");
				throw;
			}
		}
	}

	VkSurfaceFormatKHR FSwapchain::ChooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& AvailableFormats)
	{
		for (const auto& AvailableFormat : AvailableFormats)
		{
			if (AvailableFormat.format == VK_FORMAT_B8G8R8A8_SRGB && AvailableFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR)
			{
				return AvailableFormat;
			}
		}

		return AvailableFormats[0];
	}

	VkPresentModeKHR FSwapchain::ChooseSwapPresentMode(const std::vector<VkPresentModeKHR>& AvailablePresentModes)
	{
		for (const auto& AvailablePresentMode : AvailablePresentModes)
		{
			if (AvailablePresentMode == VK_PRESENT_MODE_MAILBOX_KHR)
			{
				LOG_TRACE("Present mode: Mailbox");

				return AvailablePresentMode;
			}
		}

		LOG_TRACE("Present mode: V-Sync");

		return VK_PRESENT_MODE_FIFO_KHR;
	}

	VkExtent2D FSwapchain::ChooseSwapExtent(const VkSurfaceCapabilitiesKHR& Capabilities)
	{
		if (Capabilities.currentExtent.width != UINT32_MAX)
		{
			return Capabilities.currentExtent;
		}
		else
		{
			VkExtent2D ActualExtent = WindowExtent;

			ActualExtent.width  = std::max(Capabilities.minImageExtent.width , std::min(Capabilities.maxImageExtent.width , ActualExtent.width));
			ActualExtent.height = std::max(Capabilities.minImageExtent.height, std::min(Capabilities.maxImageExtent.height, ActualExtent.height));
			
			return ActualExtent;
		}
	}

}

#pragma warning( pop ) // Vulkan SDK - End