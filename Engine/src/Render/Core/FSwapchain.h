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

		 FSwapchain (FDevice& Device, VkExtent2D WindowExtent);
		 FSwapchain (FDevice& Device, VkExtent2D WindowExtent, FSwapchain* PreviousSwapchain);
		~FSwapchain ();

		T3D_NO_COPY(FSwapchain);
		T3D_NO_MOVE(FSwapchain);

	// Functions:

		VkFormat FindDepthFormat         ();
		VkResult AcquireNextImage        (uint32* ImageIndex);
		VkResult SubmitCommandBuffers    (const VkCommandBuffer* CommandBuffers, uint32* ImageIndex);
		bool8    HasEqualSwapFormats     (const FSwapchain& Swapchain) const;

	// Accessors:

		VkFramebuffer GetFramebuffer             (uint32 Index);
		VkRenderPass  GetRenderPass              ();
		VkImageView   GetImageView               (uint32 Index);
		uint64        GetImageCount              ();
		VkFormat      GetSwapchainImageFormat    ();
		VkExtent2D    GetSwapchainExtent         ();
		uint32        GetWidth                   ();
		uint32        GetHeight                  ();
		float32       GetExtentAspectRatio       ();

	// Public Constants:

		static constexpr uint64 MaxFramesInFlight = 2;

	private:

	// Private Functions:

		void Init                    ();
		void CreateSwapchain         ();
		void CreateImageViews        ();
		void CreateDepthResources    ();
		void CreateRenderPass        ();
		void CreateFramebuffers      ();
		void CreateSyncObjects       ();

		VkSurfaceFormatKHR ChooseSwapSurfaceFormat    (const std::vector<VkSurfaceFormatKHR>& AvailableFormats);
		VkPresentModeKHR   ChooseSwapPresentMode      (const std::vector<VkPresentModeKHR>& AvailablePresentModes);
		VkExtent2D         ChooseSwapExtent           (const VkSurfaceCapabilitiesKHR& Capabilities);

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
		FSwapchain* OldSwapchain;

		std::vector<VkSemaphore> ImageAvailableSemaphores;
		std::vector<VkSemaphore> RenderFinishedSemaphores;
		std::vector<VkFence> InFlightFences;
		std::vector<VkFence> ImagesInFlight;
		uint64 CurrentFrame;
	};
}

#pragma warning( pop ) // Vulkan SDK - End