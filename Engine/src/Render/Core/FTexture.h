#pragma once

#include "FDevice.h"
#include "FDeviceBuffer.h"

namespace t3d
{
	struct FTexture2D
	{
		VkSampler      Sampler;
		VkImage        Image;
		VkImageLayout  ImageLayout;
		VkDeviceMemory ImageMemory;
		VkImageView    ImageView;
		VkExtent2D     ImageExtent;
		uint32         MipLevels;
	};

	void CreateImage(FDevice Device, FTexture2D Texture)
	{
		VkImageCreateInfo ImageInfo{};

		ImageInfo.sType                 = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
		ImageInfo.pNext                 = VK_NULL_HANDLE;
		ImageInfo.flags                 = 0;
		ImageInfo.imageType             = VK_IMAGE_TYPE_2D;
		ImageInfo.format                = VK_FORMAT_R8G8B8A8_SRGB;
		ImageInfo.extent.width          = Texture.ImageExtent.width;
		ImageInfo.extent.height         = Texture.ImageExtent.height;
		ImageInfo.extent.width          = 1;
		ImageInfo.mipLevels             = 1;
		ImageInfo.arrayLayers           = 1;
		ImageInfo.samples               = VK_SAMPLE_COUNT_1_BIT;
		ImageInfo.tiling                = VK_IMAGE_TILING_OPTIMAL;
		ImageInfo.usage                 = VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT;
		ImageInfo.sharingMode           = VK_SHARING_MODE_EXCLUSIVE;
		ImageInfo.queueFamilyIndexCount = {};
		ImageInfo.pQueueFamilyIndices   = {};
		ImageInfo.initialLayout         = VK_IMAGE_LAYOUT_UNDEFINED;

		if (vkCreateImage(Device.Device(), &ImageInfo, VK_NULL_HANDLE, &Texture.Image) != VK_SUCCESS)
		{
			SEvent::Error.Invoke({ FTimeStamp(), T3D_FUNCTION, "Failed to create image!" });
			throw;
		}

		VkMemoryRequirements MemoryRequirements;
		
		vkGetImageMemoryRequirements(VK_NULL_HANDLE, Texture.Image, &MemoryRequirements);

		VkMemoryAllocateInfo AllocateInfo{};

		AllocateInfo.sType           = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
		AllocateInfo.pNext           = VK_NULL_HANDLE;
		AllocateInfo.allocationSize  = MemoryRequirements.size;
		AllocateInfo.memoryTypeIndex = Device.FindMemoryType(MemoryRequirements.memoryTypeBits, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);

		if (vkAllocateMemory(Device.Device(), &AllocateInfo, VK_NULL_HANDLE, &Texture.ImageMemory) != VK_SUCCESS)
		{
			SEvent::Error.Invoke({ FTimeStamp(), T3D_FUNCTION, "Failed to allocate memory for image!" });
			throw;
		}

		vkBindImageMemory(Device.Device(), Texture.Image, Texture.ImageMemory, 0);
	}

	void CreateTexture(FDevice Device)
	{
		FImagePNG Image = MImageManager::LoadImage("");

		VkDeviceSize ImageSize = Image.Width * Image.Height * 4u;

		Image.Pixels; // CHECK.

		FDeviceBuffer StagingBuffer(Device, ImageSize, 1, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);

		StagingBuffer.Map();
		StagingBuffer.WriteToBuffer(Image.Pixels);
		StagingBuffer.Unmap();
	}

}