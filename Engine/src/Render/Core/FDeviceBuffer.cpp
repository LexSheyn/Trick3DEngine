#include "../../PCH/t3dpch.h"
#include "FDeviceBuffer.h"

// Disable warnings from Vulkan SDK:
#pragma warning( push ) // Vulkan SDK - Begin
#pragma warning( disable : 26812 ) // Uncoped Enum

namespace t3d
{
// Constructors and Destructor:

	FDeviceBuffer::FDeviceBuffer(FDevice& Device, VkDeviceSize InstanceSize, uint32 InstanceCount, VkBufferUsageFlags UsageFlags, VkMemoryPropertyFlags MemoryPropertyFlags, VkDeviceSize MinOffsetAlignment)
		: Device(Device),
		  MappedMemory(nullptr),
		  Memory(VK_NULL_HANDLE),
		  Buffer(VK_NULL_HANDLE),
		  
		  InstanceSize(InstanceSize),
		  InstanceCount(InstanceCount),
		  UsageFlags(UsageFlags),
		  MemoryPropertyFlags(MemoryPropertyFlags)
	{
		AlignmentSize = this->GetAlignment(InstanceSize, MinOffsetAlignment);

		BufferSize = AlignmentSize * InstanceCount;

		Device.CreateBuffer(BufferSize, UsageFlags, MemoryPropertyFlags, Buffer, Memory);

		if (Buffer && Memory)
		{
			SEvent::Trace.Invoke({ FTimeStamp(), T3D_FUNCTION, "Created." });
		}

	#if _DEBUG
		if (!Buffer)
		{
			SEvent::Error.Invoke({ FTimeStamp(), T3D_FUNCTION, "Failed to create buffer!" });
			throw;
		}

		if (!Memory)
		{
			SEvent::Error.Invoke({ FTimeStamp(), T3D_FUNCTION, "Failed to allocate memory for buffer!" });
			throw;
		}
	#endif
	}

	FDeviceBuffer::~FDeviceBuffer()
	{
		vkDeviceWaitIdle(Device.Device());

		this->Unmap();

		vkDestroyBuffer(Device.Device(), Buffer, nullptr);

		vkFreeMemory(Device.Device(), Memory, nullptr);

		SEvent::Trace.Invoke({ FTimeStamp(), T3D_FUNCTION, "Deleted." });
	}


// Functions:

	VkResult FDeviceBuffer::Map(VkDeviceSize Size, VkDeviceSize Offset)
	{
		return vkMapMemory(Device.Device(), Memory, Offset, Size, 0, &MappedMemory);
	}

	void FDeviceBuffer::Unmap()
	{
		if (MappedMemory)
		{
			vkUnmapMemory(Device.Device(), Memory);

			MappedMemory = nullptr;
		}
	}

	void FDeviceBuffer::WriteToBuffer(void* Data, VkDeviceSize Size, VkDeviceSize Offset)
	{
		if (!MappedMemory)
		{
			SEvent::Error.Invoke({ FTimeStamp(), T3D_FUNCTION, "Cannot copy to unmapped buffer!" });
			throw;
		}

		if (Size == VK_WHOLE_SIZE)
		{
			MemoryCopy(MappedMemory, BufferSize, Data);
		}
		else
		{
			uint8* MemoryOffset = reinterpret_cast<uint8*>(MappedMemory);

			MemoryOffset += Offset;

			MemoryCopy(MemoryOffset, Size, Data);
		}
	}

	VkResult FDeviceBuffer::Flush(VkDeviceSize Size, VkDeviceSize Offset)
	{
		VkMappedMemoryRange MappedRange{};

		MappedRange.sType  = VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE;
		MappedRange.memory = Memory;
		MappedRange.offset = Offset;
		MappedRange.size   = Size;

		return vkFlushMappedMemoryRanges(Device.Device(), 1, &MappedRange);
	}

	VkResult FDeviceBuffer::Invalidate(VkDeviceSize Size, VkDeviceSize Offset)
	{
		VkMappedMemoryRange MappedRange{};

		MappedRange.sType  = VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE;
		MappedRange.memory = Memory;
		MappedRange.offset = Offset;
		MappedRange.size   = Size;

		return vkInvalidateMappedMemoryRanges(Device.Device(), 1, &MappedRange);
	}

	VkDescriptorBufferInfo FDeviceBuffer::DescriptorInfo(VkDeviceSize Size, VkDeviceSize Offset)
	{
		VkDescriptorBufferInfo DescriptorBufferInfo{};

		DescriptorBufferInfo.buffer = Buffer;
		DescriptorBufferInfo.offset = Offset;
		DescriptorBufferInfo.range  = Size;

		return DescriptorBufferInfo;
	}

	void FDeviceBuffer::WriteToIndex(void* Data, uint32 Index)
	{
		this->WriteToBuffer(Data, InstanceSize, Index * AlignmentSize);
	}

	VkResult FDeviceBuffer::FlushIndex(uint32 Index)
	{
		return this->Flush(AlignmentSize, Index * AlignmentSize);
	}

	VkResult FDeviceBuffer::InvalidateIndex(uint32 Index)
	{
		return this->Invalidate(AlignmentSize, Index * AlignmentSize);
	}

	VkDescriptorBufferInfo FDeviceBuffer::DescriptorInfoForIndex(uint32 Index)
	{
		return this->DescriptorInfo(AlignmentSize, Index * AlignmentSize);
	}


// Accessors:

	VkBuffer FDeviceBuffer::GetBuffer() const
	{
		return Buffer;
	}

	void* FDeviceBuffer::GetMappedMemory() const
	{
		return MappedMemory;
	}

	const VkDeviceSize& FDeviceBuffer::GetBufferSize() const
	{
		return BufferSize;
	}

	const uint32& FDeviceBuffer::GetInstanceCount() const
	{
		return InstanceCount;
	}

	const VkDeviceSize& FDeviceBuffer::GetInstanceSize() const
	{
		return InstanceSize;
	}

	const VkDeviceSize& FDeviceBuffer::GetAlignmentSize() const
	{
		return AlignmentSize;
	}

	const VkBufferUsageFlags& FDeviceBuffer::GetUsageFlags() const
	{
		return UsageFlags;
	}

	const VkMemoryPropertyFlags& FDeviceBuffer::GetMemoryPropertyFlags() const
	{
		return MemoryPropertyFlags;
	}


// Private Accessors:

	VkDeviceSize FDeviceBuffer::GetAlignment(VkDeviceSize InstanceSize, VkDeviceSize MinOffsetAlignment)
	{
		if (MinOffsetAlignment > 0u)
		{
			return (InstanceSize + MinOffsetAlignment - 1u) & ~(MinOffsetAlignment - 1u);
		}

		return InstanceSize;
	}

}

#pragma warning( push ) // Vulkan SDK - End