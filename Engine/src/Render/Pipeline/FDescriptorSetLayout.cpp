#include "../../PCH/t3dpch.h"
#include "FDescriptorSetLayout.h"

// Disable warnings from Vulkan SDK:
#pragma warning( push ) // Vulkan SDK - Begin
#pragma warning( disable : 26812 ) // Uncoped Enum

namespace t3d
{
// Constructors and Destructor:

	FDescriptorSetLayout::FDescriptorSetLayout(FDevice& Device, const std::unordered_map<uint32, VkDescriptorSetLayoutBinding>& Bindings)
		: Device(Device),
		  Bindings(Bindings)
	{
		std::vector<VkDescriptorSetLayoutBinding> DescriptorSetLayoutBindings{};

		for (auto& Binding : this->Bindings)
		{
			DescriptorSetLayoutBindings.push_back(Binding.second);
		}

		VkDescriptorSetLayoutCreateInfo DescriptorSetLayoutInfo{};

		DescriptorSetLayoutInfo.sType        = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
		DescriptorSetLayoutInfo.bindingCount = static_cast<uint32>(DescriptorSetLayoutBindings.size());
		DescriptorSetLayoutInfo.pBindings    = DescriptorSetLayoutBindings.data();

		if (vkCreateDescriptorSetLayout(Device.Device(), &DescriptorSetLayoutInfo, nullptr, &DescriptorSetLayout) != VK_SUCCESS)
		{
			SEvent::Error.Invoke({ FTimeStamp(), T3D_FUNCTION, "Failed to create descriptor set layout!" });
			throw;
		}

		SEvent::Trace.Invoke({ FTimeStamp(), T3D_FUNCTION, "Created." });
	}

	FDescriptorSetLayout::~FDescriptorSetLayout()
	{
		vkDestroyDescriptorSetLayout(Device.Device(), DescriptorSetLayout, nullptr);

		SEvent::Trace.Invoke({ FTimeStamp(), T3D_FUNCTION, "Deleted." });
	}


// Accessors:

	VkDescriptorSetLayout FDescriptorSetLayout::GetDescriptorSetLayout() const
	{
		return DescriptorSetLayout;
	}

}

#pragma warning( pop ) // Vulkan SDK - End