#pragma once

// Disable warnings from Vulkan SDK:
#pragma warning( push ) // Vulkan SDK - Begin
#pragma warning( disable : 26812 ) // Uncoped Enum

#include "../Core/FDevice.h"

namespace t3d
{
	class FDescriptorPool
	{
	public:

	// Constructors and Destruscor:

		FDescriptorPool(FDevice& Device, uint32 MaxSets, VkDescriptorPoolCreateFlags PoolFlags, const std::vector<VkDescriptorPoolSize>& PoolSizes);

		FDescriptorPool(const FDescriptorPool&) = delete;

		~FDescriptorPool();

	// Operators:

		FDescriptorPool& operator=(const FDescriptorPool&) = delete;

	// Functions:

		bool8 AllocateDescriptorSet(const VkDescriptorSetLayout SetLayout, VkDescriptorSet& Set) const;

		void  FreeDescriptorSets(std::vector<VkDescriptorSet>& Sets) const;

		void  ResetPool();

		class Constructor
		{
		public:

			Constructor(FDevice& Device) : Device(Device) {}

			Constructor& AddPoolSize(VkDescriptorType Type, uint32 Count)
			{
				PoolSizes.push_back({ Type, Count });

				return *this;
			}

			Constructor& SetPoolFlags(VkDescriptorPoolCreateFlags Flags)
			{
				PoolFlags = Flags;

				return *this;
			}

			Constructor& SetMaxSets(uint32 Count)
			{
				MaxSets = Count;

				return *this;
			}

			[[nodiscard]] T3D_INLINE FDescriptorPool* Create() const { return new FDescriptorPool(Device, MaxSets, PoolFlags, PoolSizes); }

		private:

			FDevice& Device;

			std::vector<VkDescriptorPoolSize> PoolSizes;

			uint32 MaxSets = 1000u;

			VkDescriptorPoolCreateFlags PoolFlags = 0u;
		};

	private:

	// Variables:

		FDevice& Device;

		VkDescriptorPool Pool;

		friend class FDescriptorWriter;
	};
}

#pragma warning( pop ) // Vulkan SDK - End