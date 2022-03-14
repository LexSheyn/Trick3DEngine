#pragma once

// Disable warnings from Vulkan SDK:
#pragma warning( push ) // Vulkan SDK - Begin
#pragma warning( disable : 26812 ) // Uncoped Enum

#include "FDevice.h"

namespace t3d
{
	class FDeviceBuffer
	{
	public:

	// Constructors and Destructor:

		FDeviceBuffer  (FDevice& Device, VkDeviceSize InstanceSize, uint32 InstanceCount, VkBufferUsageFlags UsageFlags, VkMemoryPropertyFlags MemoryPropertyFlags, VkDeviceSize MinOffsetAlignment = 1u);
		~FDeviceBuffer ();

		T3D_NO_COPY(FDeviceBuffer);
		T3D_NO_MOVE(FDeviceBuffer);

	// Functions:

		/// <summary>
		/// Map a memory range of this buffer. If successful, mapped memory points to the specified buffer range.
		/// </summary>
		/// <param name="Size">: (Optional) Size of the memory range to map. Pass VK_WHOLE_SIZE to map the complete buffer range. </param>
		/// <param name="Offset">: (Optional) Byte offset from beginning. </param>
		/// <returns> VkResult of the buffer mapping call. </returns>
		VkResult Map(VkDeviceSize Size = VK_WHOLE_SIZE, VkDeviceSize Offset = 0u);

		/// <summary>
		/// Unmap a mapped memory range.
		/// </summary>
		void     Unmap();

		/// <summary>
		/// Copies the specified data to the mapped buffer. Default value writes whole buffer range.
		/// </summary>
		/// <param name="Data">: Pointer to the data to copy. </param>
		/// <param name="Size">: (Optional) Size of the data to copy. Pass VK_WHOLE_SIZE to flush the complete buffer. </param>
		/// <param name="Offset">: (Optional) Byte offset from beginning of mapped region. </param>
		void     WriteToBuffer(void* Data, VkDeviceSize Size = VK_WHOLE_SIZE, VkDeviceSize Offset = 0u);

		/// <summary>
		/// Flush a memory range of the buffer to make it visible to the device.
		/// <para> Only required for non-coherent memory. </para>
		/// </summary>
		/// <param name="Size">: (Optional) Size of the memory range to flush. Pass VK_WHOLE_SIZE to flush the complete buffer range. </param>
		/// <param name="Offset">: (Optional) Byte offset from beginning. </param>
		/// <returns> VkResult of the flush call. </returns>
		VkResult Flush(VkDeviceSize Size = VK_WHOLE_SIZE, VkDeviceSize Offset = 0u);

		/// <summary>
		/// Invalidate a memory range of the buffer to make it visible to the host.
		/// <para> Only required for non-coherent memory. </para>
		/// </summary>
		/// <param name="Size">: (Optional) Size of the memory range to invalidate. Pass VK_WHOLE_SIZE to invalidate the complete buffer range. </param>
		/// <param name="Offset">: (Optional) Byte offset from beginning. </param>
		/// <returns> VkResult of the invalidate call. </returns>
		VkResult Invalidate(VkDeviceSize Size = VK_WHOLE_SIZE, VkDeviceSize Offset = 0u);

		/// <summary>
		/// Create a buffer info descriptor.
		/// </summary>
		/// <param name="">: (Optional) Size of the memory range of the descriptor. </param>
		/// <param name="Offset">: (Optional) Byte offset from beginning. </param>
		/// <returns> VkDescriptorBufferInfo of specified offset and range. </returns>
		VkDescriptorBufferInfo DescriptorInfo(VkDeviceSize Size = VK_WHOLE_SIZE, VkDeviceSize Offset = 0u);

		/// <summary>
		/// Copies "InstanceSize" bytes of data to the mapped buffer at an offset of Index * AlignmentSize.
		/// </summary>
		/// <param name="Data">: Pointer to the data to copy. </param>
		/// <param name="Index">: Used in offset calculation. </param>
		void     WriteToIndex(void* Data, uint32 Index);

		/// <summary>
		/// Flush the memory range at index * alignmentSize of the buffer to make it visible to the device.
		/// </summary>
		/// <param name="Index">: Used in offset calculation. </param>
		/// <returns> VkResult of the flush call. </returns>
		VkResult FlushIndex(uint32 Index);

		/// <summary>
		/// Invalidate a memory range of the buffer to make it visible to the host.
		/// <para> Only required for non-coherent memory. </para>
		/// </summary>
		/// <param name="Index">: Specifies the region to invalidate: Index * AlignmentSize. </param>
		/// <returns> VkResult of the invalidate call. </returns>
		VkResult InvalidateIndex(uint32 Index);

		/// <summary>
		/// Create a buffer info descriptor.
		/// </summary>
		/// <param name="Index">: Specifies the region given by Index * AlignmentSize. </param>
		/// <returns> VkDescriptorBufferInfo for instance at index. </returns>
		VkDescriptorBufferInfo DescriptorInfoForIndex(uint32 Index);

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

		/// <summary>
		/// Returns the minimum instance size required to be compatible with devices minOffsetAlignment.
		/// </summary>
		/// <param name="InstanceSize">: The size of an instance. </param>
		/// <param name="MinOffsetAlignment">: The minimum required alignment in bytes for the offset member (for example MinUniformBufferOffsetAlignment). </param>
		/// <returns> VkResult of the buffer mapping call. </returns>
		static VkDeviceSize GetAlignment(VkDeviceSize InstanceSize, VkDeviceSize MinOffsetAlignment);

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