#pragma once

#include "FCamera.h"

namespace t3d
{
	class FFrameInfo
	{
	public:

		uint32  FrameIndex;
		float32 FrameTime;

		VkCommandBuffer CommandBuffer;

		FCamera& Camera;

		VkDescriptorSet GlobalDescriptorSet;

		std::unordered_map<uint32, class OGameObject>& GameObjects;
	};
}