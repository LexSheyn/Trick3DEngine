#include "../../PrecompiledHeaders/t3dpch.h"
#include "FDevice.h"

// Disable warnings from Vulkan SDK:
#pragma warning( push ) // Vulkan SDK - Begin
#pragma warning( disable : 26812 ) // Uncoped Enum

namespace t3d
{
// Constructors and Destructor:

	FDevice::FDevice(FWindow& Window)
		: Window(Window)
	{
		this->CreateInstance();

		this->SetupDebugMessenger();

		this->CreateSurface();

		this->PickPhysicalDevice();

		this->CreateLogicalDevice();

		this->CreateCommandPool();

		LOG_TRACE("Created.");
	}

	FDevice::~FDevice()
	{
		vkDestroyCommandPool(LogicalDevice, CommandPool, nullptr);

		vkDestroyDevice(LogicalDevice, nullptr);

		if (ValidationLayerEnabled)
		{
			// The questioning part, why not just use this function, instead of creating static one?
			this->DestroyDebugUtilsMessengerEXT(Instance, DebugMessenger, nullptr);
		}

		vkDestroySurfaceKHR(Instance, Surface, nullptr);

		vkDestroyInstance(Instance, nullptr);
	}


// Functions:

	uint32 FDevice::FindMemoryType(uint32 TypeFilter, VkMemoryPropertyFlags Properties)
	{
		VkPhysicalDeviceMemoryProperties MemoryProperties;

		vkGetPhysicalDeviceMemoryProperties(PhysicalDevice, &MemoryProperties);

		for (uint32 i = 0u; i < MemoryProperties.memoryTypeCount; i++)
		{
			if (TypeFilter & (1 << i) && (MemoryProperties.memoryTypes[i].propertyFlags & Properties) == Properties)
			{
				return i;
			}
		}

		LOG_ERROR("Failed to find suitable memroy type!");
		throw;
	}

	VkFormat FDevice::FindSupportedFormat(const std::vector<VkFormat>& Candidates, VkImageTiling Tiling, VkFormatFeatureFlags Features)
	{
		for (VkFormat Format : Candidates)
		{
			VkFormatProperties Properties;

			vkGetPhysicalDeviceFormatProperties(PhysicalDevice, Format, &Properties);

			if (Tiling == VK_IMAGE_TILING_LINEAR && (Properties.linearTilingFeatures & Features) == Features)
			{
				return Format;
			}
			else if (Tiling == VK_IMAGE_TILING_OPTIMAL && (Properties.optimalTilingFeatures & Features) == Features)
			{
				return Format;
			}
		}

		LOG_ERROR("Failed to find supported format!");
		throw;
	}

	void FDevice::CreateBuffer(VkDeviceSize Size, VkBufferUsageFlags Usage, VkMemoryPropertyFlags Properties, VkBuffer& Buffer, VkDeviceMemory& BufferMemory)
	{
		VkBufferCreateInfo BufferInfo{};

		BufferInfo.sType       = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
		BufferInfo.size        = Size;
		BufferInfo.usage       = Usage;
		BufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

		if (vkCreateBuffer(LogicalDevice, &BufferInfo, nullptr, &Buffer) != VK_SUCCESS)
		{
			LOG_ERROR("Failed to create buffer!");
			throw;
		}

		VkMemoryRequirements MemoryRequirements;

		vkGetBufferMemoryRequirements(LogicalDevice, Buffer, &MemoryRequirements);

		VkMemoryAllocateInfo AllocateInfo{};

		AllocateInfo.sType           = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
		AllocateInfo.allocationSize  = MemoryRequirements.size;
		AllocateInfo.memoryTypeIndex = this->FindMemoryType(MemoryRequirements.memoryTypeBits, Properties);

		if (vkAllocateMemory(LogicalDevice, &AllocateInfo, nullptr, &BufferMemory) != VK_SUCCESS)
		{
			LOG_ERROR("Failed to allocate buffer memory!");
			throw;
		}

		vkBindBufferMemory(LogicalDevice, Buffer, BufferMemory, 0);
	}

	VkCommandBuffer FDevice::BeginSingleTimeCommands()
	{
		VkCommandBufferAllocateInfo AllocateInfo{};

		AllocateInfo.sType              = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
		AllocateInfo.level              = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
		AllocateInfo.commandPool        = CommandPool;
		AllocateInfo.commandBufferCount = 1;

		VkCommandBuffer CommandBuffer;

		vkAllocateCommandBuffers(LogicalDevice, &AllocateInfo, &CommandBuffer);

		VkCommandBufferBeginInfo BeginInfo{};

		BeginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
		BeginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

		vkBeginCommandBuffer(CommandBuffer, &BeginInfo);

		return CommandBuffer;
	}

	void FDevice::EndSingleTimeCommands(VkCommandBuffer CommandBuffer)
	{
		vkEndCommandBuffer(CommandBuffer);

		VkSubmitInfo SubmitInfo{};

		SubmitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
		SubmitInfo.commandBufferCount = 1;
		SubmitInfo.pCommandBuffers = &CommandBuffer;

		vkQueueSubmit(GraphicsQueue, 1, &SubmitInfo, VK_NULL_HANDLE);
		vkQueueWaitIdle(GraphicsQueue);

		vkFreeCommandBuffers(LogicalDevice, CommandPool, 1, &CommandBuffer);
	}

	void FDevice::CopyBuffer(VkBuffer SourceBuffer, VkBuffer DestinationBuffer, VkDeviceSize Size)
	{
		VkCommandBuffer CommandBuffer = this->BeginSingleTimeCommands();

		VkBufferCopy CopyRegion{};

		CopyRegion.srcOffset = 0; // Optional.
		CopyRegion.dstOffset = 0; // Optional.
		CopyRegion.size      = Size;
		
		vkCmdCopyBuffer(CommandBuffer, SourceBuffer, DestinationBuffer, 1, &CopyRegion);

		this->EndSingleTimeCommands(CommandBuffer);
	}

	void FDevice::CopyBufferToImage(VkBuffer Buffer, VkImage Image, uint32 Width, uint32 Height, uint32 LayerCount)
	{
		VkCommandBuffer CommandBuffer = this->BeginSingleTimeCommands();

		VkBufferImageCopy Region{};

		Region.bufferOffset      = 0;
		Region.bufferRowLength   = 0;
		Region.bufferImageHeight = 0;

		Region.imageSubresource.aspectMask     = VK_IMAGE_ASPECT_COLOR_BIT;
		Region.imageSubresource.mipLevel       = 0;
		Region.imageSubresource.baseArrayLayer = 0;
		Region.imageSubresource.layerCount     = LayerCount;

		Region.imageOffset = { 0, 0, 0 };
		Region.imageExtent = { Width, Height, 1 };

		vkCmdCopyBufferToImage(CommandBuffer, Buffer, Image, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 1, &Region);

		this->EndSingleTimeCommands(CommandBuffer);
	}

	void FDevice::CreateImageWithInfo(const VkImageCreateInfo& ImageInfo, VkMemoryPropertyFlags Properties, VkImage& Image, VkDeviceMemory& ImageMemory)
	{
		if (vkCreateImage(LogicalDevice, &ImageInfo, nullptr, &Image) != VK_SUCCESS)
		{
			LOG_ERROR("Failed to create image!");
			throw;
		}

		VkMemoryRequirements MemoryRequirements;

		vkGetImageMemoryRequirements(LogicalDevice, Image, &MemoryRequirements);

		VkMemoryAllocateInfo AllocateInfo{};

		AllocateInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
		AllocateInfo.allocationSize = MemoryRequirements.size;
		AllocateInfo.memoryTypeIndex = this->FindMemoryType(MemoryRequirements.memoryTypeBits, Properties);

		if (vkAllocateMemory(LogicalDevice, &AllocateInfo, nullptr, &ImageMemory) != VK_SUCCESS)
		{
			LOG_ERROR("Failed to allocate image memory!");
			throw;
		}

		if (vkBindImageMemory(LogicalDevice, Image, ImageMemory, 0) != VK_SUCCESS)
		{
			LOG_ERROR("Failed to bind image memory!");
			throw;
		}
	}


// Accessors:

	FSwapchainSupportDetails FDevice::GetSwapchainSupportDetails()
	{
		return this->QuerySwapchainSupport(PhysicalDevice);
	}

	FQueueFamilyIndices FDevice::FindPhysicalQueueFamilies()
	{
		return this->FindQueueFamilies(PhysicalDevice);
	}


// Private Functions:

	void FDevice::CreateInstance()
	{
		if (ValidationLayerEnabled && !this->CheckValidationLayerSupport())
		{
			LOG_ERROR("Validation layers requested, but not available!");
			throw;
		}

	// Application info:

		VkApplicationInfo ApplicationInfo{};

		ApplicationInfo.sType              = VK_STRUCTURE_TYPE_APPLICATION_INFO;
		ApplicationInfo.pApplicationName   = "TestApplication";
		ApplicationInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
		ApplicationInfo.pEngineName        = "Trick3D";
		ApplicationInfo.apiVersion         = VK_API_VERSION_1_0;

	// Instance info:

		VkInstanceCreateInfo CreateInfo{};

		std::vector<const char8*> Extensions = this->GetRequiredExtensions();

		CreateInfo.sType                   = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		CreateInfo.pApplicationInfo        = &ApplicationInfo;
		CreateInfo.enabledExtensionCount   = static_cast<uint32>(Extensions.size());
		CreateInfo.ppEnabledExtensionNames = Extensions.data();

		VkDebugUtilsMessengerCreateInfoEXT DebugMessengerInfo{};

		if (ValidationLayerEnabled)
		{
			this->PopulateDebugMessengerCreateInfo(DebugMessengerInfo);

			CreateInfo.enabledLayerCount   = static_cast<uint32>(ValidationLayers.size());
			CreateInfo.ppEnabledLayerNames = ValidationLayers.data();
			CreateInfo.pNext               = reinterpret_cast<VkDebugUtilsMessengerCreateInfoEXT*>(&DebugMessengerInfo);
		}
		else
		{
			CreateInfo.enabledLayerCount = 0;
			CreateInfo.pNext             = nullptr;
		}

		if (vkCreateInstance(&CreateInfo, nullptr, &Instance) != VK_SUCCESS)
		{
			LOG_ERROR("Failed to create instance!");
			throw;
		}

		this->CheckGlfwRequiredExtensions();
	}

	void FDevice::SetupDebugMessenger()
	{
		if (!ValidationLayerEnabled)
		{
			return;
		}

		VkDebugUtilsMessengerCreateInfoEXT CreateInfo{};

		this->PopulateDebugMessengerCreateInfo(CreateInfo);

		// Why not to use this function instead of creating static one?
		if (this->CreateDebugUtilsMessengerEXT(Instance, &CreateInfo, nullptr, &DebugMessenger) != VK_SUCCESS)
		{
			LOG_ERROR("Failed to set up debug messenger!");
			throw;
		}
	}

	VKAPI_ATTR VkBool32 VKAPI_CALL FDevice::DebugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT MessageSeverity, VkDebugUtilsMessageTypeFlagsEXT MessageType, const VkDebugUtilsMessengerCallbackDataEXT* PtrCallbackData, void* PtrUserData)
	{
		std::cout << "[ Vulkan validation layer ]::" << __FUNCTION__ << ": " << PtrCallbackData->pMessage << "\n" << std::endl;

		if (MessageSeverity >= VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT)
		{
			// Message that is important enought to show.
		}

		return VK_FALSE;
	}

	VkResult FDevice::CreateDebugUtilsMessengerEXT(VkInstance Instance, const VkDebugUtilsMessengerCreateInfoEXT* PtrCreateInfo, const VkAllocationCallbacks* PtrAllocator, VkDebugUtilsMessengerEXT* PtrDebugMessenger)
	{
		PFN_vkCreateDebugUtilsMessengerEXT DebugFunction = reinterpret_cast<PFN_vkCreateDebugUtilsMessengerEXT>(vkGetInstanceProcAddr(Instance, "vkCreateDebugUtilsMessengerEXT"));
		
		if (DebugFunction != nullptr)
		{
			return DebugFunction(Instance, PtrCreateInfo, PtrAllocator, PtrDebugMessenger);
		}
		else
		{
			return VK_ERROR_EXTENSION_NOT_PRESENT;
		}
	}

	void FDevice::DestroyDebugUtilsMessengerEXT(VkInstance Instance, VkDebugUtilsMessengerEXT DebugMessenger, const VkAllocationCallbacks* PtrAllocator)
	{
		PFN_vkDestroyDebugUtilsMessengerEXT DebugFunction = reinterpret_cast<PFN_vkDestroyDebugUtilsMessengerEXT>(vkGetInstanceProcAddr(Instance, "vkDestroyDebugUtilsMessengerEXT"));

		if (DebugFunction != nullptr)
		{
			DebugFunction(Instance, DebugMessenger, PtrAllocator);
		}
	}

	void FDevice::CreateSurface()
	{
		Window.CreateSurface(Instance, &Surface);
	}

	void FDevice::PickPhysicalDevice()
	{
		uint32 DeviceCount = 0u;

		vkEnumeratePhysicalDevices(Instance, &DeviceCount, nullptr);

		if (DeviceCount == 0u)
		{
			LOG_ERROR("Failed to find GPUs with Vulkan support!");
			throw;
		}

		LOG_TRACE("LogicalDevice count: " + std::to_string(DeviceCount));
		
		std::vector<VkPhysicalDevice> Devices(DeviceCount);

		vkEnumeratePhysicalDevices(Instance, &DeviceCount, Devices.data());

		for (const auto& LogicalDevice : Devices)
		{
			if (this->IsDeviceSuitable(LogicalDevice))
			{
				PhysicalDevice = LogicalDevice;

				break;
			}
		}

		if (PhysicalDevice == VK_NULL_HANDLE)
		{
			LOG_ERROR("Failed to find s suitable GPU!");
			throw;
		}

		vkGetPhysicalDeviceProperties(PhysicalDevice, &Properties);

		LOG_TRACE(std::string("Physical device: ") + Properties.deviceName);
	}

	void FDevice::CreateLogicalDevice()
	{
		FQueueFamilyIndices QueueFamilyIndices = this->FindQueueFamilies(PhysicalDevice);

		std::vector<VkDeviceQueueCreateInfo> QueueCreateInfos{};

		QueueCreateInfos.reserve(100); // How much needed???

		std::set<int32> UniqueQueueFamilies = { QueueFamilyIndices.GraphicsFamily, QueueFamilyIndices.PresentFamily };

		float32 QueuePriority = 1.0f;

		for (int32 QueueFamily : UniqueQueueFamilies)
		{
			VkDeviceQueueCreateInfo QueueCreateInfo{};

			QueueCreateInfo.sType            = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
			QueueCreateInfo.queueFamilyIndex = static_cast<uint32>(QueueFamily);
			QueueCreateInfo.queueCount       = 1;
			QueueCreateInfo.pQueuePriorities = &QueuePriority;
			
			QueueCreateInfos.push_back(QueueCreateInfo);
		}

		QueueCreateInfos.shrink_to_fit();

		VkPhysicalDeviceFeatures DeviceFeatures{};
		DeviceFeatures.samplerAnisotropy = VK_TRUE;

		VkDeviceCreateInfo CreateInfo{};

		CreateInfo.sType                   = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
		CreateInfo.queueCreateInfoCount    = static_cast<uint32>(QueueCreateInfos.size());
		CreateInfo.pQueueCreateInfos       = QueueCreateInfos.data();
		CreateInfo.pEnabledFeatures        = &DeviceFeatures;
		CreateInfo.enabledExtensionCount   = static_cast<uint32>(DeviceExtensions.size());
		CreateInfo.ppEnabledExtensionNames = DeviceExtensions.data();

		// Might not really be necessary anymore because device specific validation layers have been deprecated.
		if (ValidationLayerEnabled)
		{
			CreateInfo.enabledLayerCount   = static_cast<uint32>(ValidationLayers.size());
			CreateInfo.ppEnabledLayerNames = ValidationLayers.data();
		}
		else
		{
			CreateInfo.enabledLayerCount = 0;
		}

		if (vkCreateDevice(PhysicalDevice, &CreateInfo, nullptr, &LogicalDevice) != VK_SUCCESS)
		{
			LOG_ERROR("Failed to create logical device!");
			throw;
		}

		vkGetDeviceQueue(LogicalDevice, static_cast<uint32>(QueueFamilyIndices.GraphicsFamily), 0, &GraphicsQueue );
		vkGetDeviceQueue(LogicalDevice, static_cast<uint32>(QueueFamilyIndices.PresentFamily) , 0, &PresentQueue  );
	}

	void FDevice::CreateCommandPool()
	{
		FQueueFamilyIndices QueueFamilyIndices = this->FindPhysicalQueueFamilies();

		VkCommandPoolCreateInfo PoolInfo{};

		PoolInfo.sType            = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
		PoolInfo.queueFamilyIndex = static_cast<uint32>(QueueFamilyIndices.GraphicsFamily);
		PoolInfo.flags            = VK_COMMAND_POOL_CREATE_TRANSIENT_BIT | VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;

		if (vkCreateCommandPool(LogicalDevice, &PoolInfo, nullptr, &CommandPool) != VK_SUCCESS)
		{
			LOG_ERROR("Failed to create command pool!");
			throw;
		}
	}

	bool8 FDevice::IsDeviceSuitable(VkPhysicalDevice LogicalDevice)
	{
		FQueueFamilyIndices QueueFamilyIndices = this->FindQueueFamilies(LogicalDevice);

		bool8 HasExtensionsSupported = this->CheckDeviceExtensionSupport(LogicalDevice);

		bool8 IsSwapchainAdequate = false;

		if (HasExtensionsSupported)
		{
			FSwapchainSupportDetails SwapchainSupportDetails = this->QuerySwapchainSupport(LogicalDevice);
			
			IsSwapchainAdequate = !SwapchainSupportDetails.Formats.empty() && !SwapchainSupportDetails.PresentModes.empty();
		}

		VkPhysicalDeviceFeatures SupportedFeatures;

		vkGetPhysicalDeviceFeatures(LogicalDevice, &SupportedFeatures);

		return QueueFamilyIndices.IsComplete() && HasExtensionsSupported && IsSwapchainAdequate && SupportedFeatures.samplerAnisotropy;
	}

	std::vector<const char8*> FDevice::GetRequiredExtensions()
	{
		uint32 GlfwExtensionCount = 0u;

		const char8** GlfwExtensions;

		GlfwExtensions = glfwGetRequiredInstanceExtensions(&GlfwExtensionCount);

		std::vector<const char8*> Extensions(GlfwExtensions, GlfwExtensions + GlfwExtensionCount);

		if (ValidationLayerEnabled)
		{
			Extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
		}

		return Extensions;
	}

	bool8 FDevice::CheckValidationLayerSupport()
	{
		uint32 LayerCount = 0u;

		vkEnumerateInstanceLayerProperties(&LayerCount, nullptr);

		std::vector<VkLayerProperties> AvailableLayers(LayerCount);

		vkEnumerateInstanceLayerProperties(&LayerCount, AvailableLayers.data());

		for (const char8* LayerName : ValidationLayers)
		{
			bool8 HasLayerFound = false;

			for (const auto& LayerProperties : AvailableLayers)
			{
				if (std::strcmp(LayerName, LayerProperties.layerName) == 0)
				{
					HasLayerFound = true;

					break;
				}
			}

			if (!HasLayerFound)
			{
				return false;
			}
		}

		return true;
	}

	FQueueFamilyIndices FDevice::FindQueueFamilies(VkPhysicalDevice LogicalDevice)
	{
		FQueueFamilyIndices QueueFamilyIndices;

		uint32 QueueFamilyCount = 0u;

		vkGetPhysicalDeviceQueueFamilyProperties(LogicalDevice, &QueueFamilyCount, nullptr);

		std::vector<VkQueueFamilyProperties> QueueFamilies(QueueFamilyCount);

		vkGetPhysicalDeviceQueueFamilyProperties(LogicalDevice, &QueueFamilyCount, QueueFamilies.data());

		uint32 Index = 0u;

		for (const auto& QueueFamily : QueueFamilies)
		{
			if (QueueFamily.queueCount > 0u && QueueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT)
			{
				QueueFamilyIndices.GraphicsFamily = Index;
			}

			VkBool32 HasPresentSupport = false;

			vkGetPhysicalDeviceSurfaceSupportKHR(LogicalDevice, Index, Surface, &HasPresentSupport);

			if (QueueFamily.queueCount > 0u && HasPresentSupport)
			{
				QueueFamilyIndices.PresentFamily = Index;
			}

			if (QueueFamilyIndices.IsComplete())
			{
				break;
			}

			Index++;
		}

		return QueueFamilyIndices;
	}

	void FDevice::PopulateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& CreateInfo)
	{
		CreateInfo = {};

		CreateInfo.sType           = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
		CreateInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
	//	CreateInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
		CreateInfo.messageType     = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
		CreateInfo.pfnUserCallback = FDevice::DebugCallback;
		CreateInfo.pUserData       = nullptr; // Optional.
	}

	void FDevice::CheckGlfwRequiredExtensions()
	{
		uint32 ExtensionCount = 0u;

		vkEnumerateInstanceExtensionProperties(nullptr, &ExtensionCount, nullptr);
		
		std::vector<VkExtensionProperties> Extensions(ExtensionCount);

		vkEnumerateInstanceExtensionProperties(nullptr, &ExtensionCount, Extensions.data());

		LOG_TRACE("Available extensions:");

		std::unordered_set<std::string> AvailableExtensions;

		for (const auto& Extension : Extensions)
		{
			LOG_TRACE(std::string("\t") + Extension.extensionName);

			AvailableExtensions.insert(Extension.extensionName);
		}

		LOG_TRACE("Required extensions:");

		std::vector<const char8*> RequiredExtensions = this->GetRequiredExtensions();

		for (const auto& RequiredExtension : RequiredExtensions)
		{
			LOG_TRACE(std::string("\t") + RequiredExtension);

			if (AvailableExtensions.find(RequiredExtension) == AvailableExtensions.end())
			{
				LOG_ERROR("Missing required GLFW extension!");
				throw;
			}
		}
	}

	bool8 FDevice::CheckDeviceExtensionSupport(VkPhysicalDevice LogicalDevice)
	{
		uint32 ExtensionCount = 0u;

		vkEnumerateDeviceExtensionProperties(LogicalDevice, nullptr, &ExtensionCount, nullptr);

		std::vector<VkExtensionProperties> AvailableExtensions(ExtensionCount);

		vkEnumerateDeviceExtensionProperties(LogicalDevice, nullptr, &ExtensionCount, AvailableExtensions.data());

		std::set<std::string> RequiredExtensions(DeviceExtensions.begin(), DeviceExtensions.end());

		for (const auto& Extension : AvailableExtensions)
		{
			RequiredExtensions.erase(Extension.extensionName);
		}

		return RequiredExtensions.empty();
	}

	FSwapchainSupportDetails FDevice::QuerySwapchainSupport(VkPhysicalDevice LogicalDevice)
	{
		FSwapchainSupportDetails SupportDetails;

		vkGetPhysicalDeviceSurfaceCapabilitiesKHR(LogicalDevice, Surface, &SupportDetails.Capabilities);

		uint32 FormatCount = 0u;

		vkGetPhysicalDeviceSurfaceFormatsKHR(LogicalDevice, Surface, &FormatCount, nullptr);

		if (FormatCount != 0u)
		{
			SupportDetails.Formats.resize(FormatCount);

			vkGetPhysicalDeviceSurfaceFormatsKHR(LogicalDevice, Surface, &FormatCount, SupportDetails.Formats.data());
		}

		uint32 PresentModeCount;

		vkGetPhysicalDeviceSurfacePresentModesKHR(LogicalDevice, Surface, &PresentModeCount, nullptr);

		if (PresentModeCount != 0u)
		{
			SupportDetails.PresentModes.resize(PresentModeCount);
			
			vkGetPhysicalDeviceSurfacePresentModesKHR(LogicalDevice, Surface, &PresentModeCount, SupportDetails.PresentModes.data());
		}

		return SupportDetails;
	}

}

#pragma warning( pop ) // Vulkan SDK - End