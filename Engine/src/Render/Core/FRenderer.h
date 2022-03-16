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

		void T3D_CALL BeginFrame                  ();
		void T3D_CALL EndFrame                    ();
		void T3D_CALL BeginSwapchainRenderPass    ();
		void T3D_CALL EndSwapchainRenderPass      ();

	// Accessors:
		
		const bool8&          T3D_CALL IsFrameInProgress          () const;
		      VkCommandBuffer T3D_CALL GetCurrentCommandBuffer    () const;
		      VkRenderPass    T3D_CALL GetSwapchainRenderPass     () const;
		      float32         T3D_CALL GetAspectRatio             () const;
		const uint64&         T3D_CALL GetFrameIndex              () const;

	private:

	// Private Functions:

		void T3D_CALL CreateSwapchain         ();
		void T3D_CALL RecreateSwapchain       ();
		void T3D_CALL CreateCommandBuffers    ();
		void T3D_CALL FreeCommandBuffers      ();

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