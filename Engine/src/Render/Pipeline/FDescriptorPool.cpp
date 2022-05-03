#include "../../PCH/t3dpch.h"
#include "FDescriptorPool.h"

// Disable warnings from Vulkan SDK:
#pragma warning( push ) // Vulkan SDK - Begin
#pragma warning( disable : 26812 ) // Uncoped Enum

namespace t3d
{
// Constructors and Descrutor:

	FDescriptorPool::FDescriptorPool(FDevice& Device, uint32 MaxSets, VkDescriptorPoolCreateFlags PoolFlags, const std::vector<VkDescriptorPoolSize>& PoolSizes)
		: Device(Device),
		  Pool(VK_NULL_HANDLE)
	{
		VkDescriptorPoolCreateInfo PoolInfo{};

		PoolInfo.sType         = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
		PoolInfo.flags         = PoolFlags;
		PoolInfo.maxSets       = MaxSets;
		PoolInfo.poolSizeCount = static_cast<uint32>(PoolSizes.size());
		PoolInfo.pPoolSizes    = PoolSizes.data();

		if (vkCreateDescriptorPool(Device.Device(), &PoolInfo, nullptr, &Pool) != VK_SUCCESS)
		{
			LOG_ERROR("Failed to create descriptor pool!");
			throw;
		}

		SEvent::Trace.Invoke({ T3D_FUNCTION, "Created." });
	}

	FDescriptorPool::~FDescriptorPool()
	{
		vkDestroyDescriptorPool(Device.Device(), Pool, nullptr);

		SEvent::Trace.Invoke({ T3D_FUNCTION, "Deleted." });
	}


// Functions:

	bool8 FDescriptorPool::AllocateDescriptorSet(const VkDescriptorSetLayout SetLayout, VkDescriptorSet& Set) const
	{
		VkDescriptorSetAllocateInfo AllocateInfo{};

		AllocateInfo.sType              = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
		AllocateInfo.descriptorPool     = Pool;
		AllocateInfo.descriptorSetCount = 1;
		AllocateInfo.pSetLayouts        = &SetLayout;

	// Might want to create a "DescriptorPoolManager" class that handles this case, and builds
	// a new pool whenever an old pool fills up. But this is beyond current scope.

		if (vkAllocateDescriptorSets(Device.Device(), &AllocateInfo, &Set) != VK_SUCCESS)
		{
			return false;
		}

		return true;
	}

	void FDescriptorPool::FreeDescriptorSets(std::vector<VkDescriptorSet>& Sets) const
	{
		if (vkFreeDescriptorSets(Device.Device(), Pool, static_cast<uint32>(Sets.size()), Sets.data()) != VK_SUCCESS)
		{
			LOG_ERROR("Failed to free descriptor sets!");
		}
	}

	void FDescriptorPool::ResetPool()
	{
		if (vkResetDescriptorPool(Device.Device(), Pool, 0) != VK_SUCCESS)
		{
			LOG_ERROR("Failed to reset rescriptor pool!");
		}
	}

}

#pragma warning( pop ) // Vulkan SDK - End