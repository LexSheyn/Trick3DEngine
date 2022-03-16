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

		FDescriptorWriter& T3D_CALL WriteBuffer    (uint32 Binding, VkDescriptorBufferInfo* BufferInfo);
		FDescriptorWriter& T3D_CALL WriteImage     (uint32 Binding, VkDescriptorImageInfo* ImageInfo);

		bool8 T3D_CALL Build        (VkDescriptorSet& Set);
		void  T3D_CALL Overwrite    (VkDescriptorSet& Set);

	private:

	// Variables:

		FDescriptorSetLayout& SetLayout;

		FDescriptorPool& Pool;

		std::vector<VkWriteDescriptorSet> Writes;
	};
}