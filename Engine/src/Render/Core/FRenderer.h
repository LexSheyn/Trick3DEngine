#pragma once

#include "FSwapchain.h"

namespace t3d
{
	class FRenderer
	{
	public:

	// Constructors and Destructor:

		FRenderer  (FWindow& Window, FDevice& Device);
		~FRenderer ();

		T3D_NO_COPY(FRenderer);
		T3D_NO_MOVE(FRenderer);

	// Functions:

		VkCommandBuffer BeginFrame                  ();
		void            EndFrame                    ();
		void            BeginSwapchainRenderPass    (VkCommandBuffer CommandBuffer);
		void            EndSwapchainRenderPass      (VkCommandBuffer CommandBuffer);

	// Accessors:
		
		const bool8&          IsFrameInProgress          () const;
		      VkCommandBuffer GetCurrentCommandBuffer    () const;
		      VkRenderPass    GetSwapchainRenderPass     () const;
		      float32         GetAspectRation            () const;
		const uint64&         GetFrameIndex              () const;

	private:

	// Private Functions:

		void CreateSwapchain         ();
		void RecreateSwapchain       ();
		void CreateCommandBuffers    ();
		void FreeCommandBuffers      ();

	// Variables:

		FWindow&    Window;

		FDevice&    Device;

		FSwapchain* Swapchain;

		std::vector<VkCommandBuffer> CommandBuffers;

		uint32 CurrentImageIndex;

		uint64 CurrentFrameIndex;

		bool8  IsFrameStarted;
	};
}