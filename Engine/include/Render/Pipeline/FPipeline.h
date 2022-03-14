#pragma once

#include "FPipelineConfigInfo.h"
#include "FDescriptorWriter.h"
#include "../Core/FSwapchain.h"

namespace t3d
{
	class FPipeline
	{
	public:

	// Constructors and Destructor:

		FPipeline(FDevice& Device, const FPipelineConfigInfo& ConfigInfo, const std::string& VertexShaderPath, const std::string& FragmentShaderPath);

		~FPipeline();

		T3D_NO_COPY(FPipeline);
		T3D_NO_MOVE(FPipeline);

	// Functions:

		void Bind(VkCommandBuffer CommandBuffer);

		static void CreateDefaultPipelineConfigInfo(FPipelineConfigInfo& ConfigInfo);

	private:

	// PrivateFunctions:

		static std::vector<char8> ReadFile(const std::string& FilePath);

		void CreateGraphicsPipeline(const FPipelineConfigInfo& ConfigInfo, const std::string& VertexShaderPath, const std::string& FragmentShaderPath);

		void CreateShaderModule(const std::vector<char8>& ShaderCode, VkShaderModule* ShaderModule);

	// Variables:

		FDevice& Device;

		VkPipeline GraphicsPipeline;

		VkShaderModule VertexShaderModule;
		VkShaderModule FragmentShaderModule;
	};
}