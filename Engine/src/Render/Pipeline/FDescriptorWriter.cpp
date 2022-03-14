#include "../../PrecompiledHeaders/t3dpch.h"
#include "FDescriptorWriter.h"

namespace t3d
{
// Constructor:

	FDescriptorWriter::FDescriptorWriter(FDescriptorSetLayout& SetLayout, FDescriptorPool& Pool)
		: SetLayout(SetLayout),
		  Pool(Pool)
	{
		LOG_TRACE("Created.");
	}

	FDescriptorWriter::~FDescriptorWriter()
	{
		LOG_TRACE("Destroyed.");
	}

	FDescriptorWriter& FDescriptorWriter::WriteBuffer(uint32 Binding, VkDescriptorBufferInfo* BufferInfo)
	{
		if (SetLayout.Bindings.count(Binding) != 1u)
		{
			LOG_ERROR("Layout does not contain specified binding!");
			throw;
		}

		VkDescriptorSetLayoutBinding& BindingDescription = SetLayout.Bindings[Binding];

		if (BindingDescription.descriptorCount != 1u) // INCORRECT, NEEDS REWORK!
		{
			LOG_ERROR("Binding single descriptor info, but bunding expects multiple!");
			throw;
		}

		VkWriteDescriptorSet Write{};

		Write.sType           = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
		Write.dstBinding      = Binding;
		Write.descriptorCount = 1;
		Write.descriptorType  = BindingDescription.descriptorType;
		Write.pBufferInfo     = BufferInfo;

		Writes.push_back(Write);

		return *this;
	}

	FDescriptorWriter& FDescriptorWriter::WriteImage(uint32 Binding, VkDescriptorImageInfo* ImageInfo)
	{
		if (SetLayout.Bindings.count(Binding) != 1u)
		{
			LOG_ERROR("Layout does not contain specified binding!");
			throw;
		}

		VkDescriptorSetLayoutBinding& BindingDescription = SetLayout.Bindings[Binding];

		if (BindingDescription.descriptorCount != 1u) // INCORRECT, NEEDS REWORK!
		{
			LOG_ERROR("Binding single descriptor info, but binding expects multiple!");
			throw;
		}

		VkWriteDescriptorSet Write{};

		Write.sType           = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
		Write.dstBinding      = Binding;
		Write.descriptorCount = 1;
		Write.descriptorType  = BindingDescription.descriptorType;
		Write.pImageInfo     = ImageInfo;

		Writes.push_back(Write);

		return *this;
	}

	bool8 FDescriptorWriter::Build(VkDescriptorSet& Set)
	{
		bool8 Success = Pool.AllocateDescriptorSet(SetLayout.GetDescriptorSetLayout(), Set);

		if (!Success)
		{
			return false;
		}

		this->Overwrite(Set);

		return true;
	}

	void FDescriptorWriter::Overwrite(VkDescriptorSet& Set)
	{
		for (auto& Write : Writes)
		{
			Write.dstSet = Set;
		}

		vkUpdateDescriptorSets(Pool.Device.Device(), static_cast<uint32>(Writes.size()), Writes.data(), 0, nullptr);
	}

}