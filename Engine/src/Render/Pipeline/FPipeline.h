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

		 FPipeline (FDevice& Device, const FPipelineConfigInfo& ConfigInfo, const std::string& VertexShaderPath, const std::string& FragmentShaderPath);
		~FPipeline ();

		T3D_NO_COPY(FPipeline);
		T3D_NO_MOVE(FPipeline);

	// Functions:

		void T3D_CALL Bind(VkCommandBuffer CommandBuffer);

		static void T3D_CALL CreateDefaultPipelineConfigInfo(FPipelineConfigInfo& ConfigInfo);

	private:

	// PrivateFunctions:

		static std::vector<char8> T3D_CALL ReadFile(const std::string& FilePath);

		void T3D_CALL CreateGraphicsPipeline    (const FPipelineConfigInfo& ConfigInfo, const std::string& VertexShaderPath, const std::string& FragmentShaderPath);
		void T3D_CALL CreateShaderModule        (const std::vector<char8>& ShaderCode, VkShaderModule* ShaderModule);

	// Variables:

		FDevice& Device;

		VkPipeline GraphicsPipeline;

		VkShaderModule VertexShaderModule;
		VkShaderModule FragmentShaderModule;
	};
}