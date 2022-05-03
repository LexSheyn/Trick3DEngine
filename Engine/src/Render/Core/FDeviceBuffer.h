#pragma once

// Disable warnings from Vulkan SDK:
#pragma warning( push ) // Vulkan SDK - Begin
#pragma warning( disable : 26812 ) // Uncoped Enum

#include "FDevice.h"
#include "../../Memory/T3DMemory.h"

namespace t3d
{
	class FDeviceBuffer
	{
	public:

	// Constructors and Destructor:

		 FDeviceBuffer (FDevice& Device, VkDeviceSize InstanceSize, uint32 InstanceCount, VkBufferUsageFlags UsageFlags, VkMemoryPropertyFlags MemoryPropertyFlags, VkDeviceSize MinOffsetAlignment = 1u);
		~FDeviceBuffer ();

		T3D_NO_COPY(FDeviceBuffer);
		T3D_NO_MOVE(FDeviceBuffer);

	// Functions:

		VkResult Map      (VkDeviceSize Size = VK_WHOLE_SIZE, VkDeviceSize Offset = 0u);
		void     Unmap    ();

		void                   WriteToBuffer     (void* Data, VkDeviceSize Size = VK_WHOLE_SIZE, VkDeviceSize Offset = 0u);
		VkResult               Flush             (VkDeviceSize Size = VK_WHOLE_SIZE, VkDeviceSize Offset = 0u);
		VkResult               Invalidate        (VkDeviceSize Size = VK_WHOLE_SIZE, VkDeviceSize Offset = 0u);
		VkDescriptorBufferInfo DescriptorInfo    (VkDeviceSize Size = VK_WHOLE_SIZE, VkDeviceSize Offset = 0u);

		void                   WriteToIndex              (void* Data, uint32 Index);
		VkResult               FlushIndex                (uint32 Index);
		VkResult               InvalidateIndex           (uint32 Index);
		VkDescriptorBufferInfo DescriptorInfoForIndex    (uint32 Index);

	// Accessors:

		VkBuffer GetBuffer          () const;
		void*    GetMappedMemory    () const;


		const VkDeviceSize&          GetBufferSize             () const;
		const uint32&                GetInstanceCount          () const;
		const VkDeviceSize&          GetInstanceSize           () const;
		const VkDeviceSize&          GetAlignmentSize          () const;
		const VkBufferUsageFlags&    GetUsageFlags             () const;
		const VkMemoryPropertyFlags& GetMemoryPropertyFlags    () const;

	private:

	// Private Accessors:

		static VkDeviceSize T3D_CALL GetAlignment(VkDeviceSize InstanceSize, VkDeviceSize MinOffsetAlignment);

	// Variables:

		FDevice& Device;

		void*          MappedMemory;
		VkDeviceMemory Memory;
		VkBuffer       Buffer;
		VkDeviceSize   BufferSize;

		
		VkDeviceSize InstanceSize;
		uint32       InstanceCount;

		VkBufferUsageFlags    UsageFlags;
		VkMemoryPropertyFlags MemoryPropertyFlags;

		VkDeviceSize AlignmentSize;
	};
}

#pragma warning( push ) // Vulkan SDK - End