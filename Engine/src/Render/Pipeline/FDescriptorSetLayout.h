#pragma once

// Disable warnings from Vulkan SDK:
#pragma warning( push ) // Vulkan SDK - Begin
#pragma warning( disable : 26812 ) // Uncoped Enum

#include "../Core/FDevice.h"

namespace t3d
{
	class FDescriptorSetLayout
	{
	public:

	// Constructors and Destructor:

		FDescriptorSetLayout(FDevice& Device, const std::unordered_map<uint32, VkDescriptorSetLayoutBinding>& Bindings);

		~FDescriptorSetLayout();

		T3D_NO_COPY(FDescriptorSetLayout);
		T3D_NO_MOVE(FDescriptorSetLayout);

	// Functions:

		class Constructor
		{
		public:

			Constructor(FDevice& Device) : Device(Device) {}

			Constructor& AddBinding(uint32 Binding, VkDescriptorType Type, VkShaderStageFlags ShaderStageFlags, uint32 Count = 1u)
			{
				if (Bindings.count(Binding) != 0u)
				{
					LOG_ERROR("Binding already in use!");
					throw;
				}

				VkDescriptorSetLayoutBinding LayoutBinding{};

				LayoutBinding.binding         = Binding;
				LayoutBinding.descriptorType  = Type;
				LayoutBinding.descriptorCount = Count;
				LayoutBinding.stageFlags      = ShaderStageFlags;

				Bindings[Binding] = LayoutBinding;

				return *this;
			}

			T3D_NO_DISCARD T3D_INLINE FDescriptorSetLayout* Create() const { return new FDescriptorSetLayout(Device, Bindings); }

		private:

			FDevice& Device;

			std::unordered_map<uint32, VkDescriptorSetLayoutBinding> Bindings;
		};

	// Accessors:

		VkDescriptorSetLayout GetDescriptorSetLayout() const;

	private:

	// Variables:

		FDevice& Device;

		VkDescriptorSetLayout DescriptorSetLayout;

		std::unordered_map<uint32, VkDescriptorSetLayoutBinding> Bindings;

		friend class FDescriptorWriter;
	};
}

#pragma warning( pop ) // Vulkan SDK - End