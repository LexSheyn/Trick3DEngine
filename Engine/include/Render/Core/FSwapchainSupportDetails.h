#pragma once

namespace t3d
{
	struct FSwapchainSupportDetails
	{
		VkSurfaceCapabilitiesKHR        Capabilities;
		std::vector<VkSurfaceFormatKHR> Formats;
		std::vector<VkPresentModeKHR>   PresentModes;
	};
}