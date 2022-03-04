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

		FDevice(FWindow& Window);

		~FDevice();

		T3D_NO_COPY(FDevice);
		T3D_NO_MOVE(FDevice);

	// Functions:

		uint32          FindMemoryType(uint32 TypeFilter, VkMemoryPropertyFlags Properties);

		VkFormat        FindSupportedFormat(const std::vector<VkFormat>& Candidates, VkImageTiling Tiling, VkFormatFeatureFlags Features);

		void            CreateBuffer(VkDeviceSize Size, VkBufferUsageFlags Usage, VkMemoryPropertyFlags Properties, VkBuffer& Buffer, VkDeviceMemory& BufferMemory);

		VkCommandBuffer BeginSingleTimeCommands();

		void            EndSingleTimeCommands(VkCommandBuffer CommandBuffer);

		void            CopyBuffer(VkBuffer SourceBuffer, VkBuffer DestinationBuffer, VkDeviceSize Size);

		void            CopyBufferToImage(VkBuffer Buffer, VkImage Image, uint32 Width, uint32 Height, uint32 LayerCount);

		void            CreateImageWithInfo(const VkImageCreateInfo& ImageInfo, VkMemoryPropertyFlags Properties, VkImage& Image, VkDeviceMemory& ImageMemory);

	// Accessors:

		T3D_INLINE VkDevice      Device()           { return LogicalDevice; }

		T3D_INLINE VkCommandPool GetCommandPool()   { return CommandPool; }

		T3D_INLINE VkSurfaceKHR  GetSurface()       { return Surface; }

		T3D_INLINE VkQueue       GetGraphicsQueue() { return GraphicsQueue; }

		T3D_INLINE VkQueue       GetPresentQueue()  { return PresentQueue; }

		FSwapchainSupportDetails GetSwapchainSupportDetails();

		FQueueFamilyIndices      FindPhysicalQueueFamilies();

	// Public Variables:

		VkPhysicalDeviceProperties Properties;

		#ifdef NDEBUG
			const bool8 ValidationLayerEnabled = false;
		#else
			const bool8 ValidationLayerEnabled = true;
		#endif

	private:

	// Private Functions:

		void CreateInstance();

		void SetupDebugMessenger();

		static VKAPI_ATTR VkBool32 VKAPI_CALL DebugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT MessageSeverity, VkDebugUtilsMessageTypeFlagsEXT MessageType, const VkDebugUtilsMessengerCallbackDataEXT* PtrCallbackData, void* PtrUserData);

		static VkResult CreateDebugUtilsMessengerEXT(VkInstance Instance, const VkDebugUtilsMessengerCreateInfoEXT* PtrCreateInfo, const VkAllocationCallbacks* PtrAllocator, VkDebugUtilsMessengerEXT* PtrDebugMessenger);

		static void DestroyDebugUtilsMessengerEXT(VkInstance Instance, VkDebugUtilsMessengerEXT DebugMessenger, const VkAllocationCallbacks* PtrAllocator);

		void CreateSurface();

		void PickPhysicalDevice();

		void CreateLogicalDevice();

		void CreateCommandPool();

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