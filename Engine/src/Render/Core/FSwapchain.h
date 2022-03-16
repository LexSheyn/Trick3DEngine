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

		VkFormat T3D_CALL FindDepthFormat         ();
		VkResult T3D_CALL AcquireNextImage        (uint32* ImageIndex);
		VkResult T3D_CALL SubmitCommandBuffers    (const VkCommandBuffer* CommandBuffers, uint32* ImageIndex);
		bool8    T3D_CALL HasEqualSwapFormats     (const FSwapchain& Swapchain) const;

	// Accessors:

		VkFramebuffer T3D_CALL GetFramebuffer             (uint32 Index);
		VkRenderPass  T3D_CALL GetRenderPass              ();
		VkImageView   T3D_CALL GetImageView               (uint32 Index);
		uint64        T3D_CALL GetImageCount              ();
		VkFormat      T3D_CALL GetSwapchainImageFormat    ();
		VkExtent2D    T3D_CALL GetSwapchainExtent         ();
		uint32        T3D_CALL GetWidth                   ();
		uint32        T3D_CALL GetHeight                  ();
		float32       T3D_CALL GetExtentAspectRatio       ();

	// Public Constants:

		static constexpr uint64 MAX_FRAMES_IN_FLIGHT = 2;

	private:

	// Private Functions:

		void T3D_CALL Init                    ();
		void T3D_CALL CreateSwapchain         ();
		void T3D_CALL CreateImageViews        ();
		void T3D_CALL CreateDepthResources    ();
		void T3D_CALL CreateRenderPass        ();
		void T3D_CALL CreateFramebuffers      ();
		void T3D_CALL CreateSyncObjects       ();

		VkSurfaceFormatKHR T3D_CALL ChooseSwapSurfaceFormat    (const std::vector<VkSurfaceFormatKHR>& AvailableFormats);
		VkPresentModeKHR   T3D_CALL ChooseSwapPresentMode      (const std::vector<VkPresentModeKHR>& AvailablePresentModes);
		VkExtent2D         T3D_CALL ChooseSwapExtent           (const VkSurfaceCapabilitiesKHR& Capabilities);

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