#pragma once

#include "FSwapchain.h"

namespace t3d
{
	class FRenderer
	{
	public:

	// Constructors and Destructor:

		 FRenderer (FWindow& Window, FDevice& Device);
		~FRenderer ();

		T3D_NO_COPY(FRenderer);
		T3D_NO_MOVE(FRenderer);

	// Functions:

		void BeginFrame                  ();
		void EndFrame                    ();
		void BeginSwapchainRenderPass    ();
		void EndSwapchainRenderPass      ();

	// Accessors:
		
		const bool8&          IsFrameInProgress          () const;
		      VkCommandBuffer GetCurrentCommandBuffer    () const;
		      VkRenderPass    GetSwapchainRenderPass     () const;
		      float32         GetAspectRatio             () const;
		const uint64&         GetFrameIndex              () const;
		      FDevice&        GetDevice                  () const;

		std::vector<VkViewport>& GetViewports    ();
		std::vector<VkRect2D  >& GetScissors     ();

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

		std::vector<VkViewport> Viewports;
		std::vector<VkRect2D  > Scissors;
	};
}