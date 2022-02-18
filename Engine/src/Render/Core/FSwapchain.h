#pragma once

// Disable warnings from Vulkan SDK:
#pragma warning( push ) // Vulkan SDK - Begin
#pragma warning( disable : 26812 ) // Uncoped Enum

#include "FDevice.h"

namespace t3d
{
	class FSwapchain
	{
	public:

	// Constructors and Destructor:

		FSwapchain(FDevice& Device, VkExtent2D WindowExtent);

		FSwapchain(FDevice& Device, VkExtent2D WindowExtent, std::shared_ptr<FSwapchain> PreviousSwapchain);

		FSwapchain(const FSwapchain&) = delete;

		~FSwapchain();

	// Operators:

		FSwapchain& operator=(const FSwapchain&) = delete;

	// Functions:

		VkFormat FindDepthFormat();

		VkResult AcquireNextImage(uint32* ImageIndex);

		VkResult SubmitCommandBuffers(const VkCommandBuffer* CommandBuffers, uint32* ImageIndex);

		T3D_INLINE bool8 CompareSwapFormats(const FSwapchain& Swapchain) const { return Swapchain.SwapchainImageFormat == SwapchainImageFormat && Swapchain.SwapchainDepthFormat == SwapchainDepthFormat; }

	// Accessors:

		T3D_INLINE VkFramebuffer GetFramebuffer(uint32 Index) { return SwapchainFramebuffers[Index]; }

		T3D_INLINE VkRenderPass  GetRenderPass()              { return RenderPass; }

		T3D_INLINE VkImageView   GetImageView(uint32 Index)   { return SwapchainImageViews[Index]; }

		T3D_INLINE size_t        GetImageCount()              { return SwapchainImages.size(); }

		T3D_INLINE VkFormat      GetSwapchainImageFormat()    { return SwapchainImageFormat; }

		T3D_INLINE VkExtent2D    GetSwapchainExtent()         { return SwapchainExtent; }

		T3D_INLINE uint32        GetWidth()                   { return SwapchainExtent.width; }

		T3D_INLINE uint32        GetHeight()                  { return SwapchainExtent.height; }

		T3D_INLINE float32       GetExtentAspectRatio()       { return static_cast<float32>(SwapchainExtent.width) / static_cast<float32>(SwapchainExtent.height); }

	// Public Constants:

		static constexpr size_t MAX_FRAMES_IN_FLIGHT = 2;

	private:

	// Private Functions:

		void Init();

		void CreateSwapchain();

		void CreateImageViews();

		void CreateDepthResources();

		void CreateRenderPass();

		void CreateFramebuffers();

		void CreateSyncObjects();

		VkSurfaceFormatKHR ChooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& AvailableFormats);

		VkPresentModeKHR   ChooseSwapPresentMode(const std::vector<VkPresentModeKHR>& AvailablePresentModes);

		VkExtent2D         ChooseSwapExtent(const VkSurfaceCapabilitiesKHR& Capabilities);

	// Variables:

		VkFormat   SwapchainImageFormat;
		VkFormat   SwapchainDepthFormat;
		VkExtent2D SwapchainExtent;

		std::vector<VkFramebuffer> SwapchainFramebuffers;
		VkRenderPass RenderPass;

		std::vector<VkImage>        DepthImages;
		std::vector<VkDeviceMemory> DepthImageMemorys;
		std::vector<VkImageView>    DepthImageViews;
		std::vector<VkImage>        SwapchainImages;
		std::vector<VkImageView>    SwapchainImageViews;

		FDevice& Device;

		VkExtent2D WindowExtent;

		VkSwapchainKHR Swapchain;
		std::shared_ptr<FSwapchain> OldSwapchain;

		std::vector<VkSemaphore> ImageAvailableSemaphores;
		std::vector<VkSemaphore> RenderFinishedSemaphores;
		std::vector<VkFence> InFlightFences;
		std::vector<VkFence> ImagesInFlight;
		size_t CurrentFrame;
	};
}

#pragma warning( pop ) // Vulkan SDK - End