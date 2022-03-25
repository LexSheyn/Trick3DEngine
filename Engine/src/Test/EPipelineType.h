#pragma once

namespace t3d
{
	enum class EPipelineType
	{
		Graphics       = VK_PIPELINE_BIND_POINT_GRAPHICS,
		Compute        = VK_PIPELINE_BIND_POINT_COMPUTE,
		RayTracing     = VK_PIPELINE_BIND_POINT_RAY_TRACING_KHR,
		SubpassShading = VK_PIPELINE_BIND_POINT_SUBPASS_SHADING_HUAWEI
	};
}