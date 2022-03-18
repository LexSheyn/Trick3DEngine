#pragma once

#include "FDescriptorSetLayout.h"
#include "FDescriptorPool.h"

namespace t3d
{
	class FDescriptorWriter
	{
	public:

	// Constructor:

		 FDescriptorWriter (FDescriptorSetLayout& SetLayout, FDescriptorPool& Pool);
		~FDescriptorWriter ();

	// Functions:

		FDescriptorWriter& WriteBuffer    (uint32 Binding, VkDescriptorBufferInfo* BufferInfo);
		FDescriptorWriter& WriteImage     (uint32 Binding, VkDescriptorImageInfo* ImageInfo);

		bool8 Build        (VkDescriptorSet& Set);
		void  Overwrite    (VkDescriptorSet& Set);

	private:

	// Variables:

		FDescriptorSetLayout& SetLayout;

		FDescriptorPool& Pool;

		std::vector<VkWriteDescriptorSet> Writes;
	};
}