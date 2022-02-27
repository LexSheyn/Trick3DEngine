#pragma once

#include "FSwapchain.h"

namespace t3d
{
	class FRenderer
	{
	public:

	// Constructors and Destructor:

		FRenderer(FWindow& Window, FDevice& Device);

		FRenderer(const FRenderer&) = delete;

		~FRenderer();

	// Operators:

		FRenderer& operator=(const FRenderer&) = delete;

	// Functions:

		VkCommandBuffer BeginFrame();

		void            EndFrame();

		void            BeginSwapchainRenderPass(VkCommandBuffer CommandBuffer);

		void            EndSwapchainRenderPass(VkCommandBuffer CommandBuffer);

	// Accessors:
		
		T3D_INLINE const bool8&          IsFrameInProgress()       const { return IsFrameStarted; }

		T3D_INLINE       VkCommandBuffer GetCurrentCommandBuffer() const { if (!IsFrameStarted) { LOG_ERROR("Cannot get command buffer when frame not in progress!"); throw; } return CommandBuffers[CurrentFrameIndex]; }

		T3D_INLINE       VkRenderPass    GetSwapchainRenderPass()  const { return Swapchain->GetRenderPass(); }

		T3D_INLINE       float32         GetAspectRation()         const { return Swapchain->GetExtentAspectRatio(); }

		T3D_INLINE const uint64&         GetFrameIndex()           const { if (!IsFrameStarted) { LOG_ERROR("Cannot get frame index when frame not in progress!"); throw; } return CurrentFrameIndex; }

	private:

	// Private Functions:

		void CreateSwapchain();

		void RecreateSwapchain();

		void CreateCommandBuffers();

		void FreeCommandBuffers();

	// Variables:

		FWindow& Window;

		FDevice& Device;

		FSwapchain* Swapchain;

		std::vector<VkCommandBuffer> CommandBuffers;

		uint32 CurrentImageIndex;

		uint64 CurrentFrameIndex;

		bool8 IsFrameStarted;
	};
}