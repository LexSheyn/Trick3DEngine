#pragma once

// Disable warnings from Vulkan SDK:
#pragma warning( push ) // Vulkan SDK - Begin
#pragma warning( disable : 26812 ) // Uncoped Enum

#include "FSwapChainSupportDetails.h"
#include "FQueueFamilyIndices.h"

#include "../../Window/FWindow.h"

namespace t3d
{
	class FDevice
	{
	public:

	// Constructors and Destructor:

		 FDevice (FWindow& Window);
		~FDevice ();

		T3D_NO_COPY(FDevice);
		T3D_NO_MOVE(FDevice);

	// Functions:

		uint32          T3D_CALL FindMemoryType             (uint32 TypeFilter, VkMemoryPropertyFlags Properties);
		VkFormat        T3D_CALL FindSupportedFormat        (const std::vector<VkFormat>& Candidates, VkImageTiling Tiling, VkFormatFeatureFlags Features);
		void            T3D_CALL CreateBuffer               (VkDeviceSize Size, VkBufferUsageFlags Usage, VkMemoryPropertyFlags Properties, VkBuffer& Buffer, VkDeviceMemory& BufferMemory);
		VkCommandBuffer T3D_CALL BeginSingleTimeCommands    ();
		void            T3D_CALL EndSingleTimeCommands      (VkCommandBuffer CommandBuffer);
		void            T3D_CALL CopyBuffer                 (VkBuffer SourceBuffer, VkBuffer DestinationBuffer, VkDeviceSize Size);
		void            T3D_CALL CopyBufferToImage          (VkBuffer Buffer, VkImage Image, uint32 Width, uint32 Height, uint32 LayerCount);
		void            T3D_CALL CreateImageWithInfo        (const VkImageCreateInfo& ImageInfo, VkMemoryPropertyFlags Properties, VkImage& Image, VkDeviceMemory& ImageMemory);

	// Accessors:

		VkDevice      T3D_CALL Device              ();
		VkCommandPool T3D_CALL GetCommandPool      ();
		VkSurfaceKHR  T3D_CALL GetSurface          ();
		VkQueue       T3D_CALL GetGraphicsQueue    ();
		VkQueue       T3D_CALL GetPresentQueue     ();

		FSwapchainSupportDetails T3D_CALL GetSwapchainSupportDetails    ();
		FQueueFamilyIndices      T3D_CALL FindPhysicalQueueFamilies     ();

	// Public Variables:

		VkPhysicalDeviceProperties Properties;

		#ifdef NDEBUG
			const bool8 ValidationLayerEnabled = false;
		#else
			const bool8 ValidationLayerEnabled = true;
		#endif

	private:

	// Private Functions:

		void T3D_CALL CreateInstance         ();
		void T3D_CALL SetupDebugMessenger    ();

		static VKAPI_ATTR VkBool32 VKAPI_CALL DebugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT MessageSeverity, VkDebugUtilsMessageTypeFlagsEXT MessageType, const VkDebugUtilsMessengerCallbackDataEXT* PtrCallbackData, void* PtrUserData);

		static VkResult CreateDebugUtilsMessengerEXT(VkInstance Instance, const VkDebugUtilsMessengerCreateInfoEXT* PtrCreateInfo, const VkAllocationCallbacks* PtrAllocator, VkDebugUtilsMessengerEXT* PtrDebugMessenger);

		static void DestroyDebugUtilsMessengerEXT(VkInstance Instance, VkDebugUtilsMessengerEXT DebugMessenger, const VkAllocationCallbacks* PtrAllocator);

		void T3D_CALL CreateSurface          ();
		void T3D_CALL PickPhysicalDevice     ();
		void T3D_CALL CreateLogicalDevice    ();
		void T3D_CALL CreateCommandPool      ();

		bool8 IsDeviceSuitable(VkPhysicalDevice Device);

		std::vector<const char8*> GetRequiredExtensions();

		bool8 CheckValidationLayerSupport();

		FQueueFamilyIndices FindQueueFamilies(VkPhysicalDevice Device);

		void PopulateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& CreateInfo);

		void CheckGlfwRequiredExtensions();

		bool8 CheckDeviceExtensionSupport(VkPhysicalDevice Device);

		FSwapchainSupportDetails QuerySwapchainSupport(VkPhysicalDevice Device);

	// Variables:

		FWindow& Window;

		VkInstance Instance;

		VkDevice LogicalDevice;

		VkSurfaceKHR Surface;

		VkPhysicalDevice PhysicalDevice;
		
		VkDebugUtilsMessengerEXT DebugMessenger;

		VkCommandPool CommandPool;
		
		VkQueue GraphicsQueue;
		VkQueue PresentQueue;

		const std::vector<const char8*> ValidationLayers = { "VK_LAYER_KHRONOS_validation" };
		const std::vector<const char8*> DeviceExtensions = { VK_KHR_SWAPCHAIN_EXTENSION_NAME };
	};
}

#pragma warning( pop ) // Vulkan SDK - End